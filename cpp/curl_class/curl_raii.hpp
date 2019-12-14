#pragma once

#include <curl/curl.h>

class Curl_RAII
{
    public:
        Curl_RAII();
        ~Curl_RAII();
        
        // TODO: set correct types
        //void setopt(CURLoption option, parameter)

    private:
        CURL *easy_handle;
        CURLcode result;
};
