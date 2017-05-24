<?php

/*
This function "inbound_sms()" will take all incomming text messages and filter then for the work "okay"
After it sees the word "ok" It will then reply with a conformation message and then it will do whatever you program it to do *_*  

**It works with phone numbers from any country     
*/

function inbound_sms(){	
	
	 if (!isset($_GET['text'], $_GET['msisdn'], $_GET['to'])){
	 }
  
  else{

	// Get the relevant data
	
	$to = $_GET['to'];
	$from = $_GET['msisdn']; //The phone number that sent you the message
	$text = $_GET['text'];   //The message that the phone has texted you In this case our server will only respond to a text with the message ok
            	
	print "response 200 OK"; // Message was recieved
		
		if($text == 'ok' || $text == 'Ok' || $text == 'OK' || $text == 'okay' || $text == 'Okay' || $text == '"ok"' || $text == '"Ok"' )
		{	
			/* Send SMS to user
			 *   Load Send-sms.inc from the SMS module.
			 *   Example URL: http://rest.nexmo.com/sms/xml?api_key=xxxxx&api_secret=xxxxxx&from=senderID&to=destination_number&text=messagebody 
			 * $t = To (Phone# with country code no spaces or symbols)
			 * $f = From (Sender ID or phone #)
			 * $m = Message you want to sent
			*/
				   module_load_include('inc', 'SMS', 'Send-sms');
					$f = '###';  //  US Nexmo phone number
					$I ='####';  // International Nexmo Phone number
					$t = $from; 		
					$m = 'You+have+Sent+us+a+message+with+the+word+okay'; 	
			        $m2 = 'message+2';
						

			if(starts_with($t, "1"))
					{  /*If phone number starts with a 1 then send sms from US # otherwise Use the International phone number.
					      ** wait 1 sec before sending another message 1 SMS/sec throughput for US & 5 SMS/sec for International**    */
						nexmo_sms_send($f,$m,$t);  //Send message from US number
						sleep(1);   			   // Wait 1 second
						nexmo_sms_send($f,$m2,$t);
						print "  message sent-from-US";
						echo 'true';
					}
					else	
					{
						echo 'false';						
						nexmo_sms_send($I,$m,$t);  //Send message from internation number
						usleep(250000);   // Sleep for .25 seconds because nexmo international SMS is throttled
						nexmo_sms_send($I,$m2,$t);
						print "  message sent -from- Int.";
					}
										
			 
			}
			
   }
	 
}