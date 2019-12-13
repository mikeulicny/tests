#include "url.hpp"

Url::Url()
{
    m_url = curl_url();
}

Url::~Url()
{
    curl_url_cleanup(m_url);
}

// set member functions
void Url::set_url(const std::string &new_url)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_URL, new_url.c_str(), 0);
}

void Url::set_scheme(const std::string &new_scheme)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_SCHEME, new_scheme.c_str(), 0);
}

void Url::set_user(const std::string &new_user)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_USER, new_user.c_str(), 0);
}

void Url::set_password(const std::string &new_password)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_USER, new_password.c_str(), 0);
}

void Url::set_options(const std::string &new_options)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_OPTIONS, new_options.c_str(), 0);
}

void Url::set_host(const std::string &new_host)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_HOST, new_host.c_str(), 0);
}

void Url::set_zoneid(const std::string &new_zoneid)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_ZONEID, new_zoneid.c_str(), 0);
}

void Url::set_port(const std::string &new_port)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_PORT, new_port.c_str(), 0);
}

void Url::set_path(const std::string &new_path)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_PATH, new_path.c_str(), 0);
}

void Url::set_query(const std::string &new_query)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_QUERY, new_query.c_str(), 0);
}

void Url::set_fragment(const std::string &new_fragment)
{
    m_curlcode = curl_url_set(m_url, CURLUPART_FRAGMENT, new_fragment.c_str(), 0);
}

// get member functions
const std::string Url::get_url()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_URL, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_scheme()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_SCHEME, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_user()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_USER, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_password()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_PASSWORD, &m_data, 0);
    return temp_str = m_data; 
}

const std::string Url::get_options()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_OPTIONS, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_host()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_HOST, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_zoneid()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_ZONEID, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_port()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_PORT, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_path()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_PATH, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_query()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_QUERY, &m_data, 0);
    return temp_str = m_data;
}

const std::string Url::get_fragment()
{
    m_curlcode = curl_url_get(m_url, CURLUPART_QUERY, &m_data, 0);
    return temp_str = m_data;
}
