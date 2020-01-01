#include <iostream>
#include <string>
#include <cstring>

#include "database.hpp"

int main()
{
    // connect to database
    Database db_test("dbname = stockmarket_database");
   
    // pass in SQL syntax
    std::cout << "TEST OF SQL SYNTAX\n";

    //db_test.exec("SELECT * FROM forex");
    //db_test.exec("SELECT * FROM equities");
    db_test.exec("SELECT symbol FROM equities ORDER BY symbol");
    db_test.print_to_terminal();
    
    // test fetching all symbols
    std::cout << "TEST OF RETURN ALL SYMBOLS\n";

    std::vector<std::string> test_symbols;
    test_symbols = db_test.symbols(asset_type::EQUITY);
    for (int i = 0; i < test_symbols.size(); i++)
    {
        std::cout << test_symbols[i] << " ";
    }

    test_symbols = db_test.symbols(asset_type::FOREX);
    for (int i = 0; i < test_symbols.size(); i++)
    {
        std::cout << test_symbols[i] << " ";
    }


    return 0;
}
