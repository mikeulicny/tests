/* test program for url class */

#include <iostream>
#include <string>
#include "url.hpp"

int main()
{
    // create empty url
    Url test_url; 
    test_url.set(CURLUPART_URL, "https://google.com/pathA/pathB?query1=abc&query2=xyz");

    std::string temp;
    temp = test_url.get(CURLUPART_URL);
    std::cout << "Url: " << temp << "\n";

    temp = test_url.get(CURLUPART_SCHEME);
    std::cout << "Scheme: " << temp << "\n";

    temp = test_url.get(CURLUPART_QUERY);
    std::cout << "Query: " << temp << "\n";

    return 0;
}
