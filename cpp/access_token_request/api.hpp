#include <iostream>
#include <iomanip>
#include <fstream>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <string>
#include <cstring>
#include <fmt/format.h>

class api {
    public:
        api();
        ~api();

        void authentication(const bool &get_refresh = false);
        void get_account(std::string &account_number);
        void get_price_history(const std::string &symbol);
        void get_quotes(const std::string &symbol);

    private:
        // api variables
        std::string client_id;      // consumer key
        std::string access_token;   // 1083 chars
        std::string refresh_token;  // 935 chars

        // rapidjson variables
        std::string read_buffer;

        // curl variables
        CURL *curl;
        CURLcode res;
        // TODO: add headers to private variables?

        // internal functions
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
        // static size_t read_callback(void *contents, size_t size, size_t nmemb, void *userp);
};