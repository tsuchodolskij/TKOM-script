#include <string>
#include <fstream>

#ifndef SOURCE_H
#define SOURCE_H

using namespace std;

class Source
{

private:
    ifstream f;
    char current_char{};
    unsigned int line{};
    unsigned int column{};

public:
    Source(const string& filename);
    ~Source();
    char get_current_char();
    unsigned int get_line();
    unsigned int get_column();
    void consume_char();

    // funkcja przewijania bialych znakow
    // funkcja budujaca alphanum ciag znakow z sourcea
    // if keyword, dawaj w tokenie string='', inaczej daj string nazwe cala bo to identifier
    // testy jednostkowe i inne srodowisko
};

#endif


// podzial na metody
