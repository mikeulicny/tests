#include "curl_raii.hpp"

Curl_RAII::Curl_RAII()
{
    easy_handle = curl_easy_init();
}

Curl_RAII::~Curl_RAII()
{
    curl_easy_cleanup(easy_handle);
}


