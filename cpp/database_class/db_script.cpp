#include <iostream>

#include <libpq-fe.h>

static void exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}


int main()
{
    // variables
    const char *conninfo;
    PGconn *conn;
    PGresult *res;
    int nFields;
    int i, j;

    // default info
    conninfo = "dbname = stockmarket_database";

    // connect to database
    conn = PQconnectdb(conninfo);

    // check if connected to database
    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        exit_nicely(conn);
    }

    std::cout << "Connected to database\n";

    // set always-secure search path, so malicious users can't take control
    /*res = PQexec(conn, "SELECT pg_catalog.set_config('search_path', '', false)");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << "SET failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);
    */
    
    // start transaction block
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::cout << "BEGIN command failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }

    res = PQexec(conn, "DECLARE myportal CURSOR FOR SELECT * FROM equities");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::cout << "DECLARE CURSOR failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << "FETCH ALL failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }

    // print names
    nFields = PQnfields(res);
    for (i = 0; i < nFields; i++)
    {
        std::cout << PQfname(res, i) << " ";
    }
    std::cout << "\n\n";

    // next, print out the rows
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
        {
            std::cout << PQgetvalue(res, i, j) << " ";
        }
        std::cout << "\n";
    }
    
    PQclear(res);

    // close portal
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    // end transaction block
    res = PQexec(conn, "END");
    PQclear(res);
    
    // close connection to database
    PQfinish(conn);

    return 0;

    // check if all tables exist
    // if (false) create table

    // input symbol
    // check if price history table exists
    // if false build table
    // insert values into table

}