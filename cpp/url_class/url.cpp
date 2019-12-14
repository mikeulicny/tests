#include "url.hpp"

Url::Url()
{
    m_url = curl_url();
}

Url::~Url()
{
    curl_url_cleanup(m_url);
}

void Url::set(CURLUPart part, const char *content)
{
    m_curlcode = curl_url_set(m_url, part, content, 0);
}

const std::string Url::get(CURLUPart part)
{
    m_curlcode = curl_url_get(m_url, part, &m_data, 0);
    return temp_str = m_data;
}
