Action()
{
	lr_think_time(5);
	
	lr_start_transaction("02_OpenFlights");
	
	web_url("Search Flights Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t56.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);
	
	web_url("nav.pl_3", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t57.inf", 
		"Mode=HTTP", 
		LAST);

	web_reg_save_param_ex(
	    "ParamName=CITIES", 
	    "LB/IC=\">",
	    "RB/IC=</option>",
	    "Ordinal=ALL",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
	
	web_reg_save_param_ex(
	    "ParamName=SEATPREF", 
	    "LB/IC=name=\"seatPref\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=ALL",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
	
	web_reg_save_param_ex(
	    "ParamName=SEATTYPE", 
	    "LB/IC=name=\"seatType\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=ALL",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
	
	web_url("reservations.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/reservations.pl?page=welcome", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t58.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("02_OpenFlights",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Search page opened"));
	
	lr_save_string(lr_paramarr_random("CITIES"),"CITIES_DEPART");
	lr_save_string(lr_paramarr_random("CITIES"),"CITIES_ARRIVE");
	
//	lr_think_time(5);
	
	if (strcmp(lr_eval_string("{CITIES_DEPART}"),lr_eval_string("{CITIES_ARRIVE}")) == 0){
//		lr_message(lr_eval_string("           ERROR : Sity depart : {CITIES_DEPART} Sity arrive : {CITIES_ARRIVE}"));            	//проверка совпадения двух городов
		while (strcmp(lr_eval_string("{CITIES_DEPART}"),lr_eval_string("{CITIES_ARRIVE}")) == 0){
			lr_save_string(lr_paramarr_random("CITIES"),"CITIES_ARRIVE");
//		lr_message(lr_eval_string("           ERROR FIXED : Sity depart : {CITIES_DEPART} Sity arrive : {CITIES_ARRIVE}"));			//подтверждение исправления одинаковых городов
		}
	}
	
	lr_save_string(lr_paramarr_random("SEATPREF"),"SEATPREF_RANDOM");
	lr_save_string(lr_paramarr_random("SEATTYPE"),"SEATTYPE_RANDOM");
	
	

	lr_think_time(15);

	lr_start_transaction("03_DoSearchRoundTripTicket");
	
	web_reg_save_param_ex(
	    "ParamName=OUTBOUNDFLIGHT", 
	    "LB/IC=name=\"outboundFlight\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=ALL",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
	
	web_reg_save_param_ex(
	    "ParamName=RETURNFLIGHT", 
	    "LB/IC=name=\"returnFlight\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=ALL",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t59.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={CITIES_DEPART}", ENDITEM, 		//Denver   {CITIES}
		"Name=departDate", "Value={DEPARTDATE}", ENDITEM,     //05/30/2023
		"Name=arrive", "Value={CITIES_ARRIVE}", ENDITEM, 		//Los Angeles  {CITIES}
		"Name=returnDate", "Value={RETURNDATE}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=on", ENDITEM, 
		"Name=seatPref", "Value={SEATPREF_RANDOM}", ENDITEM, 			//Aisle
		"Name=seatType", "Value={SEATTYPE_RANDOM}", ENDITEM, 				//Coach
		"Name=findFlights.x", "Value=54", ENDITEM, 
		"Name=findFlights.y", "Value=8", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("03_DoSearchRoundTripTicket",LR_AUTO);
	
	lr_save_string(lr_paramarr_random("OUTBOUNDFLIGHT"),"OUTBOUNDFLIGHT_RANDOM");
	lr_save_string(lr_paramarr_random("RETURNFLIGHT"),"RETURNFLIGHT_RANDOM");
	
	lr_message(lr_eval_string("    {CURRTIME} : Flights found : {OUTBOUNDFLIGHT_RANDOM} and {RETURNFLIGHT_RANDOM}"));
	lr_message(lr_eval_string("    {CURRTIME} : Sity depart : {CITIES_DEPART}, Sity arrive : {CITIES_ARRIVE}"));
	

	
	
	lr_think_time(10);

	lr_start_transaction("04_SelectionRandomRoundTripFlights");
	
	web_submit_data("reservations.pl_3", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Snapshot=t60.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={OUTBOUNDFLIGHT_RANDOM}", ENDITEM, 		//030;251;05/30/2023  
		"Name=returnFlight", "Value={RETURNFLIGHT_RANDOM}", ENDITEM, 			//300;251;05/31/2023  
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={SEATTYPE_RANDOM}", ENDITEM, 			//Coach
		"Name=seatPref", "Value={SEATPREF_RANDOM}", ENDITEM, 			//Aisle
		"Name=reserveFlights.x", "Value=69", ENDITEM, 
		"Name=reserveFlights.y", "Value=8", ENDITEM, 
		LAST);

	lr_end_transaction("04_SelectionRandomRoundTripFlights",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Found Seat Type : {SEATTYPE_RANDOM}, Seat Pref : {SEATPREF_RANDOM}"));
	
	

	lr_think_time(15);

	lr_start_transaction("05_CompletionBooking");
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=<!-- Flight reserved -->",
		LAST);

	web_submit_data("reservations.pl_4", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Snapshot=t61.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=firstName", "Value={USERNAME}", ENDITEM, 
		"Name=lastName", "Value={PASSWORD}", ENDITEM, 
		"Name=address1", "Value={ADDRESS1}", ENDITEM, 
		"Name=address2", "Value={ADDRESS2}", ENDITEM, 
		"Name=pass1", "Value={FULLNAME}", ENDITEM, 
		"Name=creditCard", "Value={CREDITCARD}", ENDITEM, 
		"Name=expDate", "Value={EXPDATE}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={SEATTYPE_RANDOM}", ENDITEM, 						//Coach
		"Name=seatPref", "Value={SEATPREF_RANDOM}", ENDITEM, 						//Aisle
		"Name=outboundFlight", "Value={OUTBOUNDFLIGHT_RANDOM}", ENDITEM, 			//030;251;05/30/2023  
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value={RETURNFLIGHT_RANDOM}", ENDITEM, 				//300;251;05/31/2023  
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=55", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);

	lr_end_transaction("05_CompletionBooking",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Booking is complect"));
	
	

	lr_think_time(5);

	lr_start_transaction("06_GoToHomePage");

	web_url("Home Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t62.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("login.pl_3", 
		"URL=http://{HOST}:{PORT}/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Snapshot=t63.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("nav.pl_4", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Snapshot=t64.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("06_GoToHomePage",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Go to Home Page is complete"));
	

	
	
	lr_think_time(5);

	lr_start_transaction("07_ OpeningBookingList");
	
	web_url("Itinerary Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t65.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_reg_save_param_ex(
	    "ParamName=FLIGHTID", 
	    "LB/IC=name=\"flightID\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=1",
	    SEARCH_FILTERS,
	        "Scope=body",
		LAST);
	
	web_url("itinerary.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t66.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("nav.pl_5", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t67.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);
	
	lr_end_transaction("07_ OpeningBookingList",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Booking is created : {FLIGHTID}"));
	
	

	lr_think_time(10);

	lr_start_transaction("08_ DeletingBooking");
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=No flights have been reserved",
		LAST);

	web_submit_data("itinerary.pl_2", 
		"Action=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Snapshot=t68.inf", 
		"Mode=HTTP", 
		ITEMDATA,
		"Name=1", "Value=on", ENDITEM,		
		"Name=flightID", "Value={FLIGHTID}", ENDITEM, 		//308890009-100038-JB  Проверка верификации:Value=fdsags ("Text=No flights have been reserved" not found for web_reg_find)
		"Name=removeAllFlights.x", "Value=45", ENDITEM, 
		"Name=removeAllFlights.y", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		LAST);
	
	
	lr_end_transaction("08_ DeletingBooking",LR_AUTO);
	
	lr_message(lr_eval_string("    {CURRTIME} : Booking ({FLIGHTID}) is deleted"));
	return 0;
}
