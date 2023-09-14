Logout()
{
	lr_think_time(5);

	lr_start_transaction("09_ DoLogout");

	web_url("SignOff Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t69.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("nav.pl_6", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t70.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("09_ DoLogout",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : User is logged out of session"));

	return 0;
}
