#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <libpq-fe.h>

enum class asset_type {
    EQUITY,
    ETF,
    FOREX,
    FUTURE,
    FUTURE_OPTION,
    INDEX,
    INDICATOR,
    MUTUAL_FUND,
    OPTION,
    UNKNOWN
};

class database
{
    public:
        database(const std::string &conninfo);
        ~database();

        database(const database&) = delete;
        database &operator=(const database&) = delete;

        void exec(const std::string &query);
        void print_to_terminal();

        std::vector<std::string> symbols(const asset_type &asset);
        
    private:
        PGconn *m_conn;
        PGresult *m_res;
        
};
