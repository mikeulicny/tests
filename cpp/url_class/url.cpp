#include "url.hpp"

url::url()
{
    m_url = curl_url();
}

url::url(const char &url_input)
{
    m_url = curl_url();
    m_curlcode = curl_url_set(m_url, CURLUPART_URL, url_input, 0);
}

url::~url()
{
    curl_url_cleanup(m_url);
}
