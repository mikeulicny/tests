#pragma once

#include <string>
#include <curl/curl.h>
 
class Url {
    public:
        Url();
        ~Url();
        Url(const Url&) = delete;
        Url &operator=(const Url&) = delete;

        void set(CURLUPart part, const char *content);
        const std::string get(CURLUPart part);

    private:
        CURLU *m_url;
        CURLUcode m_curlcode;
        
        std::string m_str;
        char *m_data;
};
