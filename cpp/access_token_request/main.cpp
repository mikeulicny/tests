#include <iostream>

#include "api.hpp"

int main()
{

	std::string USER_INPUT;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	std::cout << "Quote Program Version 1.0.0\n";
    std::cout << "Enter a symbol or account number\n";
    std::cout << "ctrl + c to quit\n";
	
    // Initialization of variables and classes
	api client;
	std::string input;

    // authenticate API
	client.authentication();
    while(true)
    {
        std::cout << ">";
	    getline(std::cin, input);

        if (input.length() == 9)
        {
            client.get_account(input);
        }
        else
        {
            client.get_quotes(input);
        }
    }

	
	std::cin.get();

	curl_global_cleanup();

    return 0;
}