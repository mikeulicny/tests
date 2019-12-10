#include "authentication.hpp"

api::authentication::authentication()
{
    // read token data into memory
    FILE* fp = fopen("tokens.json", "r");
    if (fp)
    {
        char r_buffer[65536];
        rapidjson::FileReadStream is(fp, r_buffer, sizeof(r_buffer));
        rapidjson::Document doc;
        doc.ParseStream(is);
        m_client_id = doc["consumer_key"].GetString();
        m_refresh_token = doc["refresh_token"].GetString();
    }
    fclose(fp);
    
}

api::authentication::~authentication()
{
    // destructor
}

void api::authentication::post()
{
    std::string post_data = fmt::format
    (
        "access_type={0}&grant_type={1}&code={2}&redirect_uri={3}&client_id={4}&refresh_token={5}",
        "",                 //access_type
        "refresh_token",    // grant_type
        "",                 // code
        "",                 // redirect_uri
        m_client_id,        // client_id
        m_refresh_token     // refresh_token
    );

    curl_easy_setopt(curl, CURLOPT_URL, m_url);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(post_data.c_str()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    res = curl_easy_perform(curl);
}

// --Private Functions--
size_t api::authentication::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}   // write_callback