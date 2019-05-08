#include "source.h"

Source::Source(const string& filename)
{
    f.open(filename, std::fstream::in);
    this->line = 1;
    this->column = 0;
    this->consume_char();
}

Source::~Source()
{
    f.close();
}

char Source::get_current_char()
{
    return this->current_char;
}

unsigned int Source::get_line()
{
    return this->line;
}

unsigned int Source::get_column()
{
    return this->column;
}

void Source::consume_char()
{
    f.get(this->current_char);
    this->column++;
    if (this->current_char == '\n') {
        this->line++;
        this->column = 0;
    }
}
