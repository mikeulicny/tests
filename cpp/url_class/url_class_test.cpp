/* test program for url class */

#include <iostream>
#include <string>
#include "url.hpp"

int main()
{
    // create empty url
    Url test_url; 
    test_url.set_url("https://google.com/pathA/pathB?query1=abc&query2=xyz");

    std::string temp;
    temp = test_url.get_url();
    std::cout << "get_url: " << temp << "\n";

    temp = test_url.get_scheme();
    std::cout << "get_scheme: " << temp << "\n";

    temp = test_url.get_host();
    std::cout << "get_host: " << temp << "\n";

    //temp = test_url.get_port();
    //std::cout << "get_port: " << temp << "\n";

    temp = test_url.get_path();
    std::cout << "get_path: " << temp << "\n";

    temp = test_url.get_query();
    std::cout << "get_query: " << temp << "\n";

    //temp = test_url.get_fragment();
    //std::cout << "get_fragment: " << temp << "\n";
    
    return 0;
}
