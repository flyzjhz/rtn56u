/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * MTD utility functions
 *
 * Copyright 2006, ASUSTeK Inc.
 * All Rights Reserved.
 * 
 * THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
 * KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
 * SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
 *
 * $Id: mtd.c,v 1.2 2007/03/19 09:37:23 shinjung Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>

//#include <linux/mtd/mtd.h>
#include <mtd/mtd-user.h>

#include <trxhdr.h>
#include <rts/crc.h>
#include <nvram/bcmutils.h>
#include <shutils.h>

/*
 * Open an MTD device
 * @param	mtd	path to or partition name of MTD device
 * @param	flags	open() flags
 * @return	return value of open()
 */
int
mtd_open(const char *mtd, int flags)
{
	FILE *fp;
	char dev[PATH_MAX];
	int i;

	if ((fp = fopen("/proc/mtd", "r"))) {
		while (fgets(dev, sizeof(dev), fp)) {
			if (sscanf(dev, "mtd%d:", &i) && strstr(dev, mtd)) {
				snprintf(dev, sizeof(dev), "/dev/mtd/%d", i);
				fclose(fp);
				return open(dev, flags);
			}
		}
		fclose(fp);
	}

	return open(mtd, flags);
}

/*
 * Erase an MTD device
 * @param	mtd	path to or partition name of MTD device
 * @return	0 on success and errno on failure
 */
int
mtd_erase(const char *mtd)
{
	int mtd_fd;
	mtd_info_t mtd_info;
	erase_info_t erase_info;

	/* Open MTD device */
	if ((mtd_fd = mtd_open(mtd, O_RDWR)) < 0) {
		perror(mtd);
		return errno;
	}

	/* Get sector size */
	if (ioctl(mtd_fd, MEMGETINFO, &mtd_info) != 0) {
		perror(mtd);
		close(mtd_fd);
		return errno;
	}

	erase_info.length = mtd_info.erasesize;

	for (erase_info.start = 0;
	     erase_info.start < mtd_info.size;
	     erase_info.start += mtd_info.erasesize) {
		(void) ioctl(mtd_fd, MEMUNLOCK, &erase_info);
		if (ioctl(mtd_fd, MEMERASE, &erase_info) != 0) {
			perror(mtd);
			close(mtd_fd);
			return errno;
		}
	}

	close(mtd_fd);
	return 0;
}

extern int http_get(const char *server, char *buf, size_t count, off_t offset);

/*
 * Write a file to an MTD device
 * @param	path	file to write or a URL
 * @param	mtd	path to or partition name of MTD device
 * @return	0 on success and errno on failure
 */
int
mtd_write(const char *path, const char *mtd)
{
	int mtd_fd = -1;
	mtd_info_t mtd_info;
	erase_info_t erase_info;

	struct sysinfo info;
	struct trx_header trx;
	unsigned long crc;

	FILE *fp;
	char *buf = NULL;
	long count, len, off;
	int ret = -1;
	long filelen;

	/* Examine TRX header */
	if ((fp = fopen(path, "r")))
	{
		fseek(fp, 0, SEEK_END);
		filelen = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		count = safe_fread(&trx, 1, sizeof(struct trx_header), fp);
	}
	else
		count = http_get(path, (char *) &trx, sizeof(struct trx_header), 0);
	if (count < sizeof(struct trx_header)) {
		dbg("%s: File is too small (%ld bytes)\n", path, count);
		goto fail;
	}
	if (trx.magic != TRX_MAGIC ||
	    trx.len > TRX_MAX_LEN ||
	    trx.len < sizeof(struct trx_header)) {
		dbg("%s: Bad trx header\n", path);
		goto fail;
	}

	/* Open MTD device and get sector size */
	if ((mtd_fd = mtd_open(mtd, O_RDWR)) < 0 ||
	    ioctl(mtd_fd, MEMGETINFO, &mtd_info) != 0 ||
	    mtd_info.erasesize < sizeof(struct trx_header)) {
		perror(mtd);
		goto fail;
	}

	/* Allocate temporary buffer */
	/* See if we have enough memory to store the whole file */
	sysinfo(&info);
	if (info.freeram >= trx.len) {
		erase_info.length = ROUNDUP(trx.len, mtd_info.erasesize);
		if (!(buf = malloc(erase_info.length)))
			erase_info.length = mtd_info.erasesize;
	}
	/* fallback to smaller buffer */
	else {
		erase_info.length = mtd_info.erasesize;
		buf = NULL;
	}
	if (!buf && (!(buf = malloc(erase_info.length)))) {
		perror("malloc");
		goto fail;
	}

	/* Calculate CRC over header */
	crc = crc32((uint8 *) &trx.flag_version,
		sizeof(struct trx_header) - OFFSETOF(struct trx_header,
		flag_version), CRC32_INIT_VALUE);

	if (trx.flag_version & TRX_NO_HEADER)
		trx.len -= sizeof(struct trx_header);

	/* Write file or URL to MTD device */
	for (erase_info.start = 0; erase_info.start < trx.len; erase_info.start += count) {
//	for (erase_info.start = 0; erase_info.start < filelen; erase_info.start += count) {	// change for WL-330gE ODM profile
		len = MIN(erase_info.length, trx.len - erase_info.start);
//		len = MIN(erase_info.length, filelen - erase_info.start);			// change for WL-330gE ODM profile
		if ((trx.flag_version & TRX_NO_HEADER) || erase_info.start)
			count = off = 0;
		else {
			count = off = sizeof(struct trx_header);
			memcpy(buf, &trx, sizeof(struct trx_header));
		}
		if (fp)
			count += safe_fread(&buf[off], 1, len - off, fp);
		else
			count += http_get(path, &buf[off], len - off, erase_info.start + off);
		if (count < len) {
			dbg("%s: Truncated file (actual %ld expect %ld)\n", path,
				count - off, len - off);
			goto fail;
		}
		/* Update CRC */
		crc = crc32(&buf[off], count - off, crc);
		/* Check CRC before writing if possible */
		if (count == trx.len) {
			if (crc != trx.crc32) {
				dbg("%s: Bad CRC\n", path);
				goto fail;
			}
		}
		/* Do it */
		(void) ioctl(mtd_fd, MEMUNLOCK, &erase_info);
		if (ioctl(mtd_fd, MEMERASE, &erase_info) != 0 ||
		    write(mtd_fd, buf, count) != count) {		   
			perror(mtd);
			goto fail;
		}
	}

	printf("%s: CRC OK\n", mtd);
	ret = 0;

fail:
	if (buf) {
		/* Dummy read to ensure chip(s) are out of lock/suspend state */
		(void) read(mtd_fd, buf, 2);
		free(buf);
	}

	if (mtd_fd >= 0)
		close(mtd_fd);
	if (fp)
		fclose(fp);
	return ret;
}
