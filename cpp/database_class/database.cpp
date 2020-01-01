#include "database.hpp"

Database::Database(const std::string &conninfo)
{
    // connect to database 
    m_conn = PQconnectdb(conninfo.c_str());
}

Database::~Database()
{
    PQclear(m_res);
    PQfinish(m_conn);
}

void Database::exec(const std::string &query)
{
    m_res = PQexec(m_conn, query.c_str());
}

void Database::print_to_terminal()
{
    int nFields;

    // print names
    nFields = PQnfields(m_res);
    for (int i = 0; i != nFields; ++i)
    {
        std::cout <<  PQfname(m_res, i) << " ";
    }
    std::cout << "\n";

    // next, print out the rows
    for (int i = 0; i != PQntuples(m_res); ++i)
    {
        for (int j = 0; j != nFields; ++j)
        {
            std::cout <<  PQgetvalue(m_res, i, j) << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::string> Database::symbols(const asset_type &asset)
{
    std::vector<std::string> temp_v;
    int n_fields;
    switch (asset)
    {
        case asset_type::EQUITY:    exec("SELECT symbol FROM equities ORDER BY symbol");
            break;
        case asset_type::ETF:       exec("SELECT symbol FROM etf ORDER BY symbol");
            break;
        case asset_type::FOREX:     exec("SELECT symbol FROM forex ORDER BY symbol");
            break;
        case asset_type::FUTURE:    exec("SELECT symbol FROM future ORDER BY symbol");
            break;
        case asset_type::INDEX:     exec("SELECT symbol FROM index ORDER BY symbol");
            break;
        case asset_type::MUTUAL_FUND: exec("SELECT symbol FROM mutual_fund ORDER BY symbol");
            break;
        default:
            break;
    }
    n_fields = PQnfields(m_res);

    for (int i = 0; i != PQntuples(m_res); ++i)
    {
        for (int j = 0; j != n_fields; ++j)
        {
            temp_v.push_back(PQgetvalue(m_res, i, j));
        }
    }
    return temp_v;
}
