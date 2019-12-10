#pragma once

#include <string>
#include <curl/curl.h>
#include <fmt/format.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

namespace api
{

class authentication
{
    public:
        authentication();
        ~authentication();

        void post();

        const std::string &client_id() const {return m_client_id;}
        const std::string &access_token() const {return m_access_token;}
        const std::string &refresh_token() const {return m_refresh_token;}

    private:
        std::string m_client_id;
        std::string m_access_token;
        std::string m_refresh_token;

        const char *m_url = "https://api.tdameritrade.com/v1/oauth2/token";

        CURL *curl;
        CURLcode res;
        std::string read_buffer;
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

};  // authentication
}   // namespace api
