<?php

function nexmo_config_form($form, &$form_state){

	$form['authentication'] = array(
			'#type' => 'fieldset',
			'#title' => t('Nexmo user account configuration'),
			'#collapsible' => TRUE,
		);

	$form['authentication']['nexmo_configuration_key'] = array(
			'#type' => 'textfield',
			'#title' => t('API Key'),
			'#default_value' => variable_get('nexmo_configuration_key'),
			'#description' => t('Your Nexmo account api key'),
		);

	$form['authentication']['nexmo_configuration_secret'] = array(
			'#type' => 'textfield',
			'#title' => t('API Secret'),
			'#default_value' => variable_get('nexmo_configuration_secret'),
			'#description' => t('Your Nexmo account api Secret'),
		);

	//use vertical tabs to group related configurations together for easier navigation.

	$form['vertical_tabs'] = array(
			'#type' => 'vertical_tabs',
			'#default_tab' => 'tab-1',
		);

	$form['api_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Nexmo API configuration'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['api_configuration']['nexmo_configuration_base_url'] = array(      
			'#type' => 'textfield',
			'#title' => t('Nexmo Gateway base url'),
			'#default_value' => variable_get('nexmo_configuration_base_url', 'https://rest.nexmo.com'),// give a default value if no configuration has been set yet.
			'#description' => t('Nexmo Gateway base url'),
		);

	$form['api_configuration']['nexmo_configuration_base_rest_uri'] = array(      //prefer JSON for sending SMS
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_base_rest_uri', 'https://rest.nexmo.com/sms/json'),
			'#description' => t('Nexmo server JSON end point '),
		);

	//Nexmo gateway getBalance JSON URL

	$form['account_balance_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Nexmo Account Balance'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_balance_configuration']['nexmo_configuration_get_balance_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_get_balance_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/account/get-balance/'),
			'#description' => t('Nexmo account balance JSON end point.'),
		);

	$form['account_balance_configuration']['nexmo_configuration_get_balance_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('GET')),
			'#default_value' => 0,
		);

	//Nexmo gateway getPricing JSON URL

	$form['account_pricing_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Nexmo Account Pricing'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_pricing_configuration']['nexmo_configuration_get_pricing_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_pricing_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/account/get-pricing/outbound'),
			'#description' => t('Nexmo account pricing JSON end point.'),
		);

	$form['account_pricing_configuration']['nexmo_configuration_get_balance_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('GET')),
			'#default_value' => 0,
		);

	//Nexmo gateway getOwnNumbers JSON URL

	$form['account_numbers_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Get Own Numbers'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_numbers_configuration']['nexmo_configuration_get_numbers_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_numbers_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/account/numbers/'),
			'#description' => t('Get own numbers JSON end point.'),
		);

	$form['account_numbers_configuration']['nexmo_configuration_get_numbers_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('GET')),
			'#default_value' => 0,
		);

	//Nexmo gateway searchNumbers JSON URL

	$form['account_number_search_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Search Numbers'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_number_search_configuration']['nexmo_configuration_search_numbers_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_search_numbers_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/number/search/'),
			'#description' => t('Search Numbers JSON end point'),
		);

	$form['account_number_search_configuration']['nexmo_configuration_search_numbers_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('GET')),
			'#default_value' => 0,
		);

	//Nexmo gateway buyNumber JSON URL

	$form['account_number_buy_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Buy Number'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_number_buy_configuration']['nexmo_configuration_buy_number_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_buy_number_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/number/buy/'),
			'#description' => t('Buy Number JSON end point'),
		);

	$form['account_number_buy_configuration']['nexmo_configuration_buy_number_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('POST')),
			'#default_value' => 0,
		);

	//Nexmo gateway cancelNumber JSON URL

	$form['account_number_cancel_configuration'] = array(
			'#type' => 'fieldset',
			'#title' => t('Cancel Number'),
			'#group' => 'vertical_tabs',
			'#collapsible' => TRUE,
			
		);

	$form['account_number_cancel_configuration']['nexmo_configuration_cancel_number_rest_uri'] = array(      
			'#type' => 'textfield',
			'#title' => t('JSON URI'),
			'#default_value' => variable_get('nexmo_configuration_cancel_number_rest_uri', $default = variable_get('nexmo_configuration_base_rest_uri') .'/number/cancel/'),
			'#description' => t('Cancel Number JSON end point'),
		);

	$form['account_number_cancel_configuration']['nexmo_configuration_cancel_number_rest_uri_method'] = array(      
			'#type' => 'select',
			'#title' => t('Method'),
			'#options' => array(
				0 => t('POST')),
			'#default_value' => 0,
		);

	return(system_settings_form($form));
}