#ifndef READER_HPP
#define READER_HPP
#include <string>
#include <vector>
#include <fstream>
#include <iosfwd>
#include <iomanip>
#include <sstream>
struct YahooDownload {
    std::tm Date;
    double Open;
    double High;
    double Low;
    double Close;
    double AdjClose;
    int64_t Volume;
};
void CreateCSV(std::string_view downloaded_data,const std::string& symbol);
std::vector<YahooDownload> ReadCSV(std::string_view downloaded_data,const char * symbol);
#endif