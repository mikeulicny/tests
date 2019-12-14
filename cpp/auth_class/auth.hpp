#pragma once

#include <curl/curl.h>
#include <string>

class Auth
{
    public:
        Auth();
        ~Auth();

        void post(); 
    private:
        static std::string m_client_id;
        static std::string m_access_token;
        static std::string m_refresh_token;
};
