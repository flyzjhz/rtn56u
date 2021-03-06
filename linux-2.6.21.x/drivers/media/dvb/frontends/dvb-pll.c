/*
 * descriptions + helper functions for simple dvb plls.
 *
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/dvb/frontend.h>
#include <asm/types.h>

#include "dvb-pll.h"

/* ----------------------------------------------------------- */
/* descriptions                                                */

struct dvb_pll_desc dvb_pll_thomson_dtt7579 = {
	.name  = "Thomson dtt7579",
	.min   = 177000000,
	.max   = 858000000,
	.count = 5,
	.entries = {
		{          0, 36166667, 166666, 0xb4, 0x03 }, /* go sleep */
		{  443250000, 36166667, 166666, 0xb4, 0x02 },
		{  542000000, 36166667, 166666, 0xb4, 0x08 },
		{  771000000, 36166667, 166666, 0xbc, 0x08 },
		{  999999999, 36166667, 166666, 0xf4, 0x08 },
	},
};
EXPORT_SYMBOL(dvb_pll_thomson_dtt7579);

struct dvb_pll_desc dvb_pll_thomson_dtt7610 = {
	.name  = "Thomson dtt7610",
	.min   =  44000000,
	.max   = 958000000,
	.count = 3,
	.entries = {
		{ 157250000, 44000000, 62500, 0x8e, 0x39 },
		{ 454000000, 44000000, 62500, 0x8e, 0x3a },
		{ 999999999, 44000000, 62500, 0x8e, 0x3c },
	},
};
EXPORT_SYMBOL(dvb_pll_thomson_dtt7610);

static void thomson_dtt759x_bw(u8 *buf, u32 freq, int bandwidth)
{
	if (BANDWIDTH_7_MHZ == bandwidth)
		buf[3] |= 0x10;
}

struct dvb_pll_desc dvb_pll_thomson_dtt759x = {
	.name  = "Thomson dtt759x",
	.min   = 177000000,
	.max   = 896000000,
	.setbw = thomson_dtt759x_bw,
	.count = 6,
	.entries = {
		{          0, 36166667, 166666, 0x84, 0x03 },
		{  264000000, 36166667, 166666, 0xb4, 0x02 },
		{  470000000, 36166667, 166666, 0xbc, 0x02 },
		{  735000000, 36166667, 166666, 0xbc, 0x08 },
		{  835000000, 36166667, 166666, 0xf4, 0x08 },
		{  999999999, 36166667, 166666, 0xfc, 0x08 },
	},
};
EXPORT_SYMBOL(dvb_pll_thomson_dtt759x);

struct dvb_pll_desc dvb_pll_lg_z201 = {
	.name  = "LG z201",
	.min   = 174000000,
	.max   = 862000000,
	.count = 6,
	.entries = {
		{          0, 36166667, 166666, 0xbc, 0x03 },
		{  157500000, 36166667, 166666, 0xbc, 0x01 },
		{  443250000, 36166667, 166666, 0xbc, 0x02 },
		{  542000000, 36166667, 166666, 0xbc, 0x04 },
		{  830000000, 36166667, 166666, 0xf4, 0x04 },
		{  999999999, 36166667, 166666, 0xfc, 0x04 },
	},
};
EXPORT_SYMBOL(dvb_pll_lg_z201);

struct dvb_pll_desc dvb_pll_microtune_4042 = {
	.name  = "Microtune 4042 FI5",
	.min   =  57000000,
	.max   = 858000000,
	.count = 3,
	.entries = {
		{ 162000000, 44000000, 62500, 0x8e, 0xa1 },
		{ 457000000, 44000000, 62500, 0x8e, 0x91 },
		{ 999999999, 44000000, 62500, 0x8e, 0x31 },
	},
};
EXPORT_SYMBOL(dvb_pll_microtune_4042);

struct dvb_pll_desc dvb_pll_thomson_dtt761x = {
	/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */
	.name  = "Thomson dtt761x",
	.min   =  57000000,
	.max   = 863000000,
	.count = 3,
	.entries = {
		{ 147000000, 44000000, 62500, 0x8e, 0x39 },
		{ 417000000, 44000000, 62500, 0x8e, 0x3a },
		{ 999999999, 44000000, 62500, 0x8e, 0x3c },
	},
};
EXPORT_SYMBOL(dvb_pll_thomson_dtt761x);

struct dvb_pll_desc dvb_pll_unknown_1 = {
	.name  = "unknown 1", /* used by dntv live dvb-t */
	.min   = 174000000,
	.max   = 862000000,
	.count = 9,
	.entries = {
		{  150000000, 36166667, 166666, 0xb4, 0x01 },
		{  173000000, 36166667, 166666, 0xbc, 0x01 },
		{  250000000, 36166667, 166666, 0xb4, 0x02 },
		{  400000000, 36166667, 166666, 0xbc, 0x02 },
		{  420000000, 36166667, 166666, 0xf4, 0x02 },
		{  470000000, 36166667, 166666, 0xfc, 0x02 },
		{  600000000, 36166667, 166666, 0xbc, 0x08 },
		{  730000000, 36166667, 166666, 0xf4, 0x08 },
		{  999999999, 36166667, 166666, 0xfc, 0x08 },
	},
};
EXPORT_SYMBOL(dvb_pll_unknown_1);

/* Infineon TUA6010XS
 * used in Thomson Cable Tuner
 */
struct dvb_pll_desc dvb_pll_tua6010xs = {
	.name  = "Infineon TUA6010XS",
	.min   =  44250000,
	.max   = 858000000,
	.count = 3,
	.entries = {
		{  115750000, 36125000, 62500, 0x8e, 0x03 },
		{  403250000, 36125000, 62500, 0x8e, 0x06 },
		{  999999999, 36125000, 62500, 0x8e, 0x85 },
	},
};
EXPORT_SYMBOL(dvb_pll_tua6010xs);

/* Panasonic env57h1xd5 (some Philips PLL ?) */
struct dvb_pll_desc dvb_pll_env57h1xd5 = {
	.name  = "Panasonic ENV57H1XD5",
	.min   =  44250000,
	.max   = 858000000,
	.count = 4,
	.entries = {
		{  153000000, 36291666, 166666, 0xc2, 0x41 },
		{  470000000, 36291666, 166666, 0xc2, 0x42 },
		{  526000000, 36291666, 166666, 0xc2, 0x84 },
		{  999999999, 36291666, 166666, 0xc2, 0xa4 },
	},
};
EXPORT_SYMBOL(dvb_pll_env57h1xd5);

/* Philips TDA6650/TDA6651
 * used in Panasonic ENV77H11D5
 */
static void tda665x_bw(u8 *buf, u32 freq, int bandwidth)
{
	if (bandwidth == BANDWIDTH_8_MHZ)
		buf[3] |= 0x08;
}

struct dvb_pll_desc dvb_pll_tda665x = {
	.name  = "Philips TDA6650/TDA6651",
	.min   =  44250000,
	.max   = 858000000,
	.setbw = tda665x_bw,
	.count = 12,
	.entries = {
		{   93834000, 36249333, 166667, 0xca, 0x61 /* 011 0 0 0  01 */ },
		{  123834000, 36249333, 166667, 0xca, 0xa1 /* 101 0 0 0  01 */ },
		{  161000000, 36249333, 166667, 0xca, 0xa1 /* 101 0 0 0  01 */ },
		{  163834000, 36249333, 166667, 0xca, 0xc2 /* 110 0 0 0  10 */ },
		{  253834000, 36249333, 166667, 0xca, 0x62 /* 011 0 0 0  10 */ },
		{  383834000, 36249333, 166667, 0xca, 0xa2 /* 101 0 0 0  10 */ },
		{  443834000, 36249333, 166667, 0xca, 0xc2 /* 110 0 0 0  10 */ },
		{  444000000, 36249333, 166667, 0xca, 0xc4 /* 110 0 0 1  00 */ },
		{  583834000, 36249333, 166667, 0xca, 0x64 /* 011 0 0 1  00 */ },
		{  793834000, 36249333, 166667, 0xca, 0xa4 /* 101 0 0 1  00 */ },
		{  444834000, 36249333, 166667, 0xca, 0xc4 /* 110 0 0 1  00 */ },
		{  861000000, 36249333, 166667, 0xca, 0xe4 /* 111 0 0 1  00 */ },
	}
};
EXPORT_SYMBOL(dvb_pll_tda665x);

/* Infineon TUA6034
 * used in LG TDTP E102P
 */
static void tua6034_bw(u8 *buf, u32 freq, int bandwidth)
{
	if (BANDWIDTH_7_MHZ != bandwidth)
		buf[3] |= 0x08;
}

struct dvb_pll_desc dvb_pll_tua6034 = {
	.name  = "Infineon TUA6034",
	.min   =  44250000,
	.max   = 858000000,
	.count = 3,
	.setbw = tua6034_bw,
	.entries = {
		{  174500000, 36166667, 62500, 0xce, 0x01 },
		{  230000000, 36166667, 62500, 0xce, 0x02 },
		{  999999999, 36166667, 62500, 0xce, 0x04 },
	},
};
EXPORT_SYMBOL(dvb_pll_tua6034);

/* Infineon TUA6034
 * used in LG TDVS-H061F, LG TDVS-H062F and LG TDVS-H064F
 */
struct dvb_pll_desc dvb_pll_lg_tdvs_h06xf = {
	.name  = "LG TDVS-H06xF",
	.min   =  54000000,
	.max   = 863000000,
	.count = 3,
	.entries = {
		{  165000000, 44000000, 62500, 0xce, 0x01 },
		{  450000000, 44000000, 62500, 0xce, 0x02 },
		{  999999999, 44000000, 62500, 0xce, 0x04 },
	},
};
EXPORT_SYMBOL(dvb_pll_lg_tdvs_h06xf);

/* Philips FMD1216ME
 * used in Medion Hybrid PCMCIA card and USB Box
 */
static void fmd1216me_bw(u8 *buf, u32 freq, int bandwidth)
{
	if (bandwidth == BANDWIDTH_8_MHZ && freq >= 158870000)
		buf[3] |= 0x08;
}

struct dvb_pll_desc dvb_pll_fmd1216me = {
	.name = "Philips FMD1216ME",
	.min = 50870000,
	.max = 858000000,
	.setbw = fmd1216me_bw,
	.count = 7,
	.entries = {
		{ 143870000, 36213333, 166667, 0xbc, 0x41 },
		{ 158870000, 36213333, 166667, 0xf4, 0x41 },
		{ 329870000, 36213333, 166667, 0xbc, 0x42 },
		{ 441870000, 36213333, 166667, 0xf4, 0x42 },
		{ 625870000, 36213333, 166667, 0xbc, 0x44 },
		{ 803870000, 36213333, 166667, 0xf4, 0x44 },
		{ 999999999, 36213333, 166667, 0xfc, 0x44 },
	}
};
EXPORT_SYMBOL(dvb_pll_fmd1216me);

/* ALPS TDED4
 * used in Nebula-Cards and USB boxes
 */
static void tded4_bw(u8 *buf, u32 freq, int bandwidth)
{
	if (bandwidth == BANDWIDTH_8_MHZ)
		buf[3] |= 0x04;
}

struct dvb_pll_desc dvb_pll_tded4 = {
	.name = "ALPS TDED4",
	.min = 47000000,
	.max = 863000000,
	.setbw = tded4_bw,
	.count = 4,
	.entries = {
		{ 153000000, 36166667, 166667, 0x85, 0x01 },
		{ 470000000, 36166667, 166667, 0x85, 0x02 },
		{ 823000000, 36166667, 166667, 0x85, 0x08 },
		{ 999999999, 36166667, 166667, 0x85, 0x88 },
	}
};
EXPORT_SYMBOL(dvb_pll_tded4);

/* ALPS TDHU2
 * used in AverTVHD MCE A180
 */
struct dvb_pll_desc dvb_pll_tdhu2 = {
	.name = "ALPS TDHU2",
	.min = 54000000,
	.max = 864000000,
	.count = 4,
	.entries = {
		{ 162000000, 44000000, 62500, 0x85, 0x01 },
		{ 426000000, 44000000, 62500, 0x85, 0x02 },
		{ 782000000, 44000000, 62500, 0x85, 0x08 },
		{ 999999999, 44000000, 62500, 0x85, 0x88 },
	}
};
EXPORT_SYMBOL(dvb_pll_tdhu2);

/* Philips TUV1236D
 * used in ATI HDTV Wonder
 */
struct dvb_pll_desc dvb_pll_tuv1236d = {
	.name  = "Philips TUV1236D",
	.min   =  54000000,
	.max   = 864000000,
	.count = 3,
	.entries = {
		{ 157250000, 44000000, 62500, 0xc6, 0x41 },
		{ 454000000, 44000000, 62500, 0xc6, 0x42 },
		{ 999999999, 44000000, 62500, 0xc6, 0x44 },
	},
};
EXPORT_SYMBOL(dvb_pll_tuv1236d);

/* Samsung TBMV30111IN / TBMV30712IN1
 * used in Air2PC ATSC - 2nd generation (nxt2002)
 */
struct dvb_pll_desc dvb_pll_samsung_tbmv = {
	.name = "Samsung TBMV30111IN / TBMV30712IN1",
	.min = 54000000,
	.max = 860000000,
	.count = 6,
	.entries = {
		{ 172000000, 44000000, 166666, 0xb4, 0x01 },
		{ 214000000, 44000000, 166666, 0xb4, 0x02 },
		{ 467000000, 44000000, 166666, 0xbc, 0x02 },
		{ 721000000, 44000000, 166666, 0xbc, 0x08 },
		{ 841000000, 44000000, 166666, 0xf4, 0x08 },
		{ 999999999, 44000000, 166666, 0xfc, 0x02 },
	}
};
EXPORT_SYMBOL(dvb_pll_samsung_tbmv);

/*
 * Philips SD1878 Tuner.
 */
struct dvb_pll_desc dvb_pll_philips_sd1878_tda8261 = {
	.name  = "Philips SD1878",
	.min   =  950000,
	.max   = 2150000,
	.count = 4,
	.entries = {
		{ 1250000, 499, 500, 0xc4, 0x00},
		{ 1550000, 499, 500, 0xc4, 0x40},
		{ 2050000, 499, 500, 0xc4, 0x80},
		{ 2150000, 499, 500, 0xc4, 0xc0},
	},
};
EXPORT_SYMBOL(dvb_pll_philips_sd1878_tda8261);

/*
 * Philips TD1316 Tuner.
 */
static void td1316_bw(u8 *buf, u32 freq, int bandwidth)
{
	u8 band;

	/* determine band */
	if (freq < 161000000)
		band = 1;
	else if (freq < 444000000)
		band = 2;
	else
		band = 4;

	buf[3] |= band;

	/* setup PLL filter */
	if (bandwidth == BANDWIDTH_8_MHZ)
		buf[3] |= 1 << 3;
}

struct dvb_pll_desc dvb_pll_philips_td1316 = {
	.name  = "Philips TD1316",
	.min   =  87000000,
	.max   = 895000000,
	.setbw = td1316_bw,
	.count = 9,
	.entries = {
		{  93834000, 36166000, 166666, 0xca, 0x60},
		{ 123834000, 36166000, 166666, 0xca, 0xa0},
		{ 163834000, 36166000, 166666, 0xca, 0xc0},
		{ 253834000, 36166000, 166666, 0xca, 0x60},
		{ 383834000, 36166000, 166666, 0xca, 0xa0},
		{ 443834000, 36166000, 166666, 0xca, 0xc0},
		{ 583834000, 36166000, 166666, 0xca, 0x60},
		{ 793834000, 36166000, 166666, 0xca, 0xa0},
		{ 858834000, 36166000, 166666, 0xca, 0xe0},
	},
};
EXPORT_SYMBOL(dvb_pll_philips_td1316);

/* FE6600 used on DViCO Hybrid */
struct dvb_pll_desc dvb_pll_thomson_fe6600 = {
	.name = "Thomson FE6600",
	.min =  44250000,
	.max = 858000000,
	.count = 4,
	.entries = {
		{ 250000000, 36213333, 166667, 0xb4, 0x12 },
		{ 455000000, 36213333, 166667, 0xfe, 0x11 },
		{ 775500000, 36213333, 166667, 0xbc, 0x18 },
		{ 999999999, 36213333, 166667, 0xf4, 0x18 },
	}
};
EXPORT_SYMBOL(dvb_pll_thomson_fe6600);

struct dvb_pll_priv {
	/* i2c details */
	int pll_i2c_address;
	struct i2c_adapter *i2c;

	/* the PLL descriptor */
	struct dvb_pll_desc *pll_desc;

	/* cached frequency/bandwidth */
	u32 frequency;
	u32 bandwidth;
};

/* ----------------------------------------------------------- */
/* code                                                        */

static int debug = 0;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

int dvb_pll_configure(struct dvb_pll_desc *desc, u8 *buf,
		      u32 freq, int bandwidth)
{
	u32 div;
	int i;

	if (freq != 0 && (freq < desc->min || freq > desc->max))
	    return -EINVAL;

	for (i = 0; i < desc->count; i++) {
		if (freq > desc->entries[i].limit)
			continue;
		break;
	}
	if (debug)
		printk("pll: %s: freq=%d bw=%d | i=%d/%d\n",
		       desc->name, freq, bandwidth, i, desc->count);
	if (i == desc->count)
		return -EINVAL;

	div = (freq + desc->entries[i].offset) / desc->entries[i].stepsize;
	buf[0] = div >> 8;
	buf[1] = div & 0xff;
	buf[2] = desc->entries[i].config;
	buf[3] = desc->entries[i].cb;

	if (desc->setbw)
		desc->setbw(buf, freq, bandwidth);

	if (debug)
		printk("pll: %s: div=%d | buf=0x%02x,0x%02x,0x%02x,0x%02x\n",
		       desc->name, div, buf[0], buf[1], buf[2], buf[3]);

	// calculate the frequency we set it to
	return (div * desc->entries[i].stepsize) - desc->entries[i].offset;
}
EXPORT_SYMBOL(dvb_pll_configure);

static int dvb_pll_release(struct dvb_frontend *fe)
{
	kfree(fe->tuner_priv);
	fe->tuner_priv = NULL;
	return 0;
}

static int dvb_pll_sleep(struct dvb_frontend *fe)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	u8 buf[4];
	struct i2c_msg msg =
		{ .addr = priv->pll_i2c_address, .flags = 0,
		  .buf = buf, .len = sizeof(buf) };
	int i;
	int result;

	if (priv->i2c == NULL)
		return -EINVAL;

	for (i = 0; i < priv->pll_desc->count; i++) {
		if (priv->pll_desc->entries[i].limit == 0)
			break;
	}
	if (i == priv->pll_desc->count)
		return 0;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = priv->pll_desc->entries[i].config;
	buf[3] = priv->pll_desc->entries[i].cb;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if ((result = i2c_transfer(priv->i2c, &msg, 1)) != 1) {
		return result;
	}

	return 0;
}

static int dvb_pll_set_params(struct dvb_frontend *fe,
			      struct dvb_frontend_parameters *params)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	u8 buf[4];
	struct i2c_msg msg =
		{ .addr = priv->pll_i2c_address, .flags = 0,
		  .buf = buf, .len = sizeof(buf) };
	int result;
	u32 bandwidth = 0, frequency = 0;

	if (priv->i2c == NULL)
		return -EINVAL;

	// DVBT bandwidth only just now
	if (fe->ops.info.type == FE_OFDM) {
		bandwidth = params->u.ofdm.bandwidth;
	}

	if ((result = dvb_pll_configure(priv->pll_desc, buf,
					params->frequency, bandwidth)) < 0)
		return result;
	else
		frequency = result;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if ((result = i2c_transfer(priv->i2c, &msg, 1)) != 1) {
		return result;
	}

	priv->frequency = frequency;
	priv->bandwidth = bandwidth;

	return 0;
}

static int dvb_pll_calc_regs(struct dvb_frontend *fe,
			     struct dvb_frontend_parameters *params,
			     u8 *buf, int buf_len)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	int result;
	u32 bandwidth = 0, frequency = 0;

	if (buf_len < 5)
		return -EINVAL;

	// DVBT bandwidth only just now
	if (fe->ops.info.type == FE_OFDM) {
		bandwidth = params->u.ofdm.bandwidth;
	}

	if ((result = dvb_pll_configure(priv->pll_desc, buf+1,
					params->frequency, bandwidth)) < 0)
		return result;
	else
		frequency = result;

	buf[0] = priv->pll_i2c_address;

	priv->frequency = frequency;
	priv->bandwidth = bandwidth;

	return 5;
}

static int dvb_pll_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	return 0;
}

static int dvb_pll_get_bandwidth(struct dvb_frontend *fe, u32 *bandwidth)
{
	struct dvb_pll_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	return 0;
}

static struct dvb_tuner_ops dvb_pll_tuner_ops = {
	.release = dvb_pll_release,
	.sleep = dvb_pll_sleep,
	.set_params = dvb_pll_set_params,
	.calc_regs = dvb_pll_calc_regs,
	.get_frequency = dvb_pll_get_frequency,
	.get_bandwidth = dvb_pll_get_bandwidth,
};

struct dvb_frontend *dvb_pll_attach(struct dvb_frontend *fe, int pll_addr,
				    struct i2c_adapter *i2c,
				    struct dvb_pll_desc *desc)
{
	u8 b1 [] = { 0 };
	struct i2c_msg msg = { .addr = pll_addr, .flags = I2C_M_RD,
			       .buf = b1, .len = 1 };
	struct dvb_pll_priv *priv = NULL;
	int ret;

	if (i2c != NULL) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = i2c_transfer (i2c, &msg, 1);
		if (ret != 1)
			return NULL;
		if (fe->ops.i2c_gate_ctrl)
			     fe->ops.i2c_gate_ctrl(fe, 0);
	}

	priv = kzalloc(sizeof(struct dvb_pll_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	priv->pll_i2c_address = pll_addr;
	priv->i2c = i2c;
	priv->pll_desc = desc;

	memcpy(&fe->ops.tuner_ops, &dvb_pll_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	strncpy(fe->ops.tuner_ops.info.name, desc->name, 128);
	fe->ops.tuner_ops.info.frequency_min = desc->min;
	fe->ops.tuner_ops.info.frequency_min = desc->max;

	fe->tuner_priv = priv;
	return fe;
}
EXPORT_SYMBOL(dvb_pll_attach);

MODULE_DESCRIPTION("dvb pll library");
MODULE_AUTHOR("Gerd Knorr");
MODULE_LICENSE("GPL");
