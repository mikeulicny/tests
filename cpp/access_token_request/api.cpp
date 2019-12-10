#include "api.hpp"

api::api()
{
    // read token data into memory
    FILE* fp = fopen("tokens.json","r");
    if (fp)
    {
        char r_buffer[65536];
        rapidjson::FileReadStream is(fp, r_buffer,sizeof(r_buffer));
        rapidjson::Document doc;
        doc.ParseStream(is);
        client_id = doc["consumer_key"].GetString();
        refresh_token = doc["refresh_token"].GetString();
    }
    fclose(fp);
    
    // initialize curl handle
    curl = curl_easy_init();
}

api::~api()
{
    curl_easy_cleanup(curl);
}

void api::authentication(const bool &get_refresh)
{   
    std::string post_data = "access_type=";
    if (get_refresh)
    {
        post_data += "offline";
    }
    post_data += "&grant_type=refresh_token";
    post_data += "&code=&redirect_uri=&client_id=";
    post_data += client_id;
    post_data += "&refresh_token=";
    post_data += refresh_token;

    // set data for post
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.tdameritrade.com/v1/oauth2/token");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        std::cout << "Error: Authorization POST request failed\n";
    }
    else
    {
        rapidjson::Document document;
        document.Parse(read_buffer.c_str());

        // save access token to memory
        access_token = "Authorization: Bearer ";
        if (document.HasMember("access_token"))
        {
            access_token.append(document["access_token"].GetString());
            std::cout << "access token received\n";
        }
        if (document.HasMember("refresh_token"))
        {
            refresh_token = document["refresh_token"].GetString();
            std::cout << "refresh token received\n";
        }
    }
    read_buffer.clear();
    curl_easy_reset(curl);
}   // authentication


void api::get_account(std::string &account_number)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/accounts/";
    resource_url.append(account_number);

    struct curl_slist *header = NULL;
    header = curl_slist_append(header, access_token.c_str());
    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_account\n";
    }
    else
    {
        std::cout << read_buffer << std::endl;
    }
    read_buffer.clear();
    curl_slist_free_all(header);
    curl_easy_reset(curl);
}   // get_account

void api::get_price_history(const std::string &symbol)
{
    std::string resource_url = "https://api.tdameritrade.com/v1/marketdata/";
    resource_url.append(symbol).append("/pricehistory");

    // periodType = day, month, year, ytd
    // period = 
    //      day: 1, 2, 3, 4, 5, 10*
    //      month: 1*, 2, 3, 6
    //      year: 1*, 2, 3, 5, 10, 15, 20
    //      ytd: 1*
    // frequencyType = 
    //      day: minute*
    //      month: daily, weekly*
    //      year: daily, weekly, monthly*
    //      ytd: daily, weekly*
    // frequency = 
    //      minute: 1*, 5, 10, 15, 30
    //      daily: 1*
    //      weekly: 1*
    //      monthly: 1*
    resource_url.append("?periodType=day&period=1&frequencyType=minute&frequency=1");

    struct curl_slist *header = NULL;
    header = curl_slist_append(header, access_token.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_price_history\n";
    }
    else
    {
        std::cout << read_buffer << std::endl;
    }
    read_buffer.clear();
    curl_slist_free_all(header);
    curl_easy_reset(curl);
    
}   // get_price_history

void api::get_quotes(const std::string &symbol)
{    
    std::string resource_url = "https://api.tdameritrade.com/v1/marketdata/";
    resource_url.append(symbol).append("/quotes");    

    struct curl_slist *header = NULL;
    header = curl_slist_append(header, access_token.c_str());
    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, resource_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cout << "ERROR: curl easy perform failed on get_quote\n";
    }
    else
    {
        // parse document/response
        rapidjson::Document document;
        document.Parse(read_buffer.c_str());
        
        // iterate over retrieved symbols
        for (rapidjson::Value::ConstMemberIterator symbol_itr = document.MemberBegin(); symbol_itr != document.MemberEnd(); ++symbol_itr)
        {
            // get symbol (this is unknown when retrieved from HTTP request)
            const rapidjson::Value &symbol = document[symbol_itr->name.GetString()];
            
            rapidjson::Value::ConstMemberIterator data_itr;
            
            data_itr = symbol.FindMember("bidPrice");
            double bid_price = data_itr->value.GetDouble();
            
            data_itr = symbol.FindMember("askPrice");
            double ask_price = data_itr->value.GetDouble();

            data_itr = symbol.FindMember("lastPrice");
            double last_price = data_itr->value.GetDouble();

            data_itr = symbol.FindMember("netChange");
            double net_change = data_itr->value.GetDouble();

            int width = 12;
            std::cout << "Symbol" << std::setw(width)  << "Bid" << std::setw(width) << "Ask" << std::setw(width) << "Last" << std::setw(width) << "Net" << "\n";
            std::cout << std::setw(6) << std::right << symbol_itr->name.GetString() << std::setw(width) << bid_price << std::setw(width) << ask_price << std::setw(width) << last_price << std::setw(width) << net_change << "\n";
            
        }
    } 
    read_buffer.clear();
    curl_slist_free_all(header);
    curl_easy_reset(curl);

}   // get_quote

// --Private Functions--
size_t api::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}   // write_callback
