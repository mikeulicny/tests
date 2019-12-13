#pragma once

#include <string>
#include <curl/curl.h>
 
class Url {
    public:
        Url();
        ~Url();
        Url(const Url&) = delete;
        Url &operator=(const Url&) = delete;

        

        // set member functions 
        void set_url(const std::string &new_url);
        void set_scheme(const std::string &new_scheme);
        void set_user(const std::string &new_user);
        void set_password(const std::string &new_password);
        void set_options(const std::string &new_options);
        void set_host(const std::string &new_host);
        void set_zoneid(const std::string &new_zoneid);
        void set_port(const std::string &new_port);
        void set_path(const std::string &new_path);
        void set_query(const std::string &new_query);
        void set_fragment(const std::string &new_fragment);

        // get member functions
        const std::string get_url();
        const std::string get_scheme();
        const std::string get_user();
        const std::string get_password();
        const std::string get_options();
        const std::string get_host();
        const std::string get_zoneid();
        const std::string get_port();
        const std::string get_path();
        const std::string get_query();
        const std::string get_fragment();
    private:
        CURLU *m_url;
        CURLUcode m_curlcode;
        
        std::string temp_str;
        char *m_data;
};
