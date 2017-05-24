<?php

/*
* function to send a text message
* Messages must be under 127 characters otherwise they will be sent as 2 messages
*/
function nexmo_sms_send($from,$message,$to)
{
	//make sure $from is valid
	/*$from = $form_state['values']['from'];
	$message = $form_state['values']['text'];
	$to = $form_state['values']['recipient'];*/
	$unicode = null;
	
	if($unicode === null) 
	{
		$containsUnicode = max(array_map('ord', str_split($message))) > 127;
	} 
	else 
	{
		$containsUnicode = (bool)$unicode;
	}

// URL Encode
	urlencode($from);
	urlencode($message);

// Send away!
	$post = array(
		'from' => $from,
		'to' => $to,
		'text' => $message,
		'type' => $containsUnicode ? 'unicode' : 'text'
	);

	if(sendRequest($post))
	{
		echo 'message sent successfully!';
	}
	else
	{
		echo'Ohh Noo000ooo!!!!';
	}
	return;

}

function count_digit($number) //Function to count how many digits the phone number contains
	{
		$digit = 0;
		do
		{
		$number /=10;
		$number = intval($number);
		$digit++;
		}
		while($number!=0);
		return($digit);
	}
function starts_with($s, $prefix) 
	{
	// Find if string starts with character
		return strpos($s, $prefix) === 0;
	}


function validateOriginator($inp)
{

	// Remove any invalid characters
		$ret = preg_replace('/[^a-zA-Z0-9]/', '', (string)$inp);

		if(preg_match('/[a-zA-Z]/', $inp))
		{
			// Alphanumeric format so make sure it's < 11 chars
			$ret = substr($ret, 0, 11);
		} 
		else 
		{

			// Numerical, remove any prepending '00'
			if(substr($ret, 0, 2) == '00')
			{
				$ret = substr($ret, 2);
				$ret = substr($ret, 0, 15);
			}
		}

		return (string)$ret;
}


/**
 * Prepare and send a new message.
 */

function sendRequest($data) 
{

	$ssl_verify = false; // Verify Nexmo SSL before sending any message

	//get the set api key and secret from nexmo configuration
	if(variable_get('nexmo_configuration_key'))
	{
		$username = variable_get('nexmo_configuration_key');
	} else drupal_set_message('nexmo key not set.');

	if(variable_get('nexmo_configuration_secret'))
	{
		$secret = variable_get('nexmo_configuration_secret');
	} else drupal_set_message('nexmo secret not set.');

	// Build the post data
	$data = array_merge($data, array('username' => $username, 'password' => $secret));
	$post = '';
	foreach($data as $k => $v)
	{
		$post .= "&$k=$v";
	}

	// If available, use CURL
	if (function_exists('curl_version')) 
	{
		if(variable_get('nexmo_configuration_base_rest_uri'))
		{
			$nx_uri = variable_get('nexmo_configuration_base_rest_uri');
		}
		else drupal_set_message('nexmo SMS gateway rest url not set');

		$to_nexmo = curl_init($nx_uri);

		curl_setopt( $to_nexmo, CURLOPT_POST, true );
		curl_setopt( $to_nexmo, CURLOPT_RETURNTRANSFER, true );
		curl_setopt( $to_nexmo, CURLOPT_POSTFIELDS, $post );

		if ($ssl_verify === false) 
		{
			curl_setopt( $to_nexmo, CURLOPT_SSL_VERIFYPEER, false);
		}

		$from_nexmo = curl_exec( $to_nexmo );
		curl_close ( $to_nexmo );

	} 
	elseif (ini_get('allow_url_fopen')) 
	{
		// No CURL available so try the awesome file_get_contents

		$opts = array('http' =>
			array(
				'method'  => 'POST',
				'header'  => 'Content-type: application/x-www-form-urlencoded',
				'content' => $post
			)
		);
		$context = stream_context_create($opts);
		$from_nexmo = file_get_contents($nx_uri, false, $context);

	} 
	else
	{
		// No way of sending a HTTP post :(
		return false;
	}


	 return nexmoParse($from_nexmo);

}


/**
 * Parse server response.
 */
function nexmoParse ($from_nexmo) 
{

	$nexmo_response = '';

	$response = json_decode($from_nexmo);

	// Copy the response data into an object, removing any '-' characters from the key
	$response_obj = normaliseKeys($response);

	if ($response_obj)
	{
		$nexmo_response = $response_obj;

		// Find the total cost of this message
		$response_obj->cost = $total_cost = 0;
		if (is_array($response_obj->messages))
		{
			foreach ($response_obj->messages as $msg)
			{
				$total_cost = $total_cost + (float)$msg->messageprice;
			}

			$response_obj->cost = $total_cost;
		}

		return $response_obj;

	} 
	else 
	{
		// A malformed response
		$nexmo_response = array();
		return false;
	}

}


	 
	 
	 





/**
 * Recursively normalise any key names in an object, removing unwanted characters
 */
function normaliseKeys($obj)
 {
	// Determine if working with a class or array
	if ($obj instanceof stdClass)
	{
		$new_obj = new stdClass();
		$is_obj = true;
	}
	else 
	{
		$new_obj = array();
		$is_obj = false;
	}


	foreach($obj as $key => $val)
	{
		// If we come across another class/array, normalise it
		if ($val instanceof stdClass || is_array($val)) 
		{
			$val = normaliseKeys($val);
		}

		// Replace any unwanted characters in they key name
		if ($is_obj)
		{
			$new_obj->{str_replace('-', '', $key)} = $val;
		} 
		else
		{
			$new_obj[str_replace('-', '', $key)] = $val;
		}
	}

	return $new_obj;
}