#pragma once

#include <string>
#include <curl/curl.h>
 
class url {
    public:
        url();
        ~url();
        url(const url&) = delete;
        database &operator=(const database&) = delete;

        url(const std::string &url_input);

    private:
        CURLU *m_url;
        CURLUcode m_curlcode;

};
