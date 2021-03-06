﻿<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta HTTP-EQUIV="Pragma" CONTENT="no-cache">
<meta HTTP-EQUIV="Expires" CONTENT="-1">
<link rel="shortcut icon" href="images/favicon.png">
<link rel="icon" href="images/favicon.png">
<script>
var action = '<% get_parameter("wanaction"); %>';
var restart_time;
var wan_proto = "<% nvram_get_x("",  "wan_proto"); %>";

function restart_needed_time(second){
	if(wan_proto == "3g" && "<% detect_if_wan(); %>" == "1")
		restart_time = 60;
	else
		restart_time = second;
}

function Callback(){
	parent.showLoading(restart_time);
	setTimeout("document.redirectForm.submit();", restart_time*1000);
	return;
}
</script>
</head>

<body onLoad="Callback();">
<% wan_action(); %>
<form method="post" name="redirectForm" action="/" target="_parent">
	<input type="hidden" name="flag" value="Internet">
</form>
</body>
</html>
