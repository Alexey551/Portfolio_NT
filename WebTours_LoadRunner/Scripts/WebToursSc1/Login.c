Login()
{
	lr_message(lr_eval_string("  {CURRTIME} : IterationNum={ITERNUM}"));
	
	lr_message(lr_eval_string("   USER {ITERNUM} = {USERNAME}:{PASSWORD}"));
	
	lr_start_transaction("00_OpenStartPage");
	
	web_url("WebTours", 
		"URL=http://{HOST}:{PORT}/WebTours", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t48.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("header.html", 
		"URL=http://{HOST}:{PORT}/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://{HOST}:{PORT}/WebTours/", 
		"Snapshot=t49.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("welcome.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/WebTours/", 
		"Snapshot=t50.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("home.html", 
		"URL=http://{HOST}:{PORT}/WebTours/home.html", 
		"Resource=0", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t51.inf", 
		"Mode=HTTP", 
		LAST);

	web_reg_save_param_ex(
	    "ParamName=USERSESSION", 
	    "LB/IC=\"userSession\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=1",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
		
	web_url("nav.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t52.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("home.html_2", 
		"URL=http://{HOST}:{PORT}/WebTours/home.html", 
		"Resource=0", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t71.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_set_sockets_option("SSL_VERSION", "2&3");
	
	lr_end_transaction("00_OpenStartPage",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Start page is opened"));
	
	
	

	lr_think_time(5);
	
	lr_start_transaction("01_DoLogin");
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=User password was correct",
		LAST);

	web_submit_data("login.pl", 
		"Action=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t53.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=userSession", "Value={USERSESSION}", ENDITEM,    //136522.403483192HAccDHVpVcQVzzzHtcVDtpcczHHf
		"Name=username", "Value={USERNAME}", ENDITEM,    //Проверка верификации:Value=654654dsc (Error -26366: "Text=User password was correct" not found for web_reg_find)
		"Name=password", "Value={PASSWORD}", ENDITEM, 
		"Name=login.x", "Value=31", ENDITEM, 
		"Name=login.y", "Value=12", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_2", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Snapshot=t54.inf", 
		"Mode=HTTP", 
		LAST);

	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=Welcome to Web Tours",
		LAST);

	web_url("login.pl_2", 
		"URL=http://{HOST}:{PORT}/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Snapshot=t55.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("01_DoLogin",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : User is logged in with session {USERSESSION}"));
	
	return 0;
}
