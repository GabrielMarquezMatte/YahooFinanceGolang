#include <iostream>
#include <boost/program_options.hpp>
#include <future>
#include <chrono>
#include "Download/download.hpp"
#include "ExcelReader/reader.hpp"
namespace po = boost::program_options;
int64_t NumberOfLines(const std::string &downloaded_data)
{
    return std::count(downloaded_data.begin(), downloaded_data.end(), '\n');
}
void CreateFileYahoo(const std::string& downloaded_data,const std::string& symbol)
{
    int64_t lines = NumberOfLines(downloaded_data);
    CreateCSV(downloaded_data, symbol);
    std::cout << "Downloaded " << lines << " lines of data for " << symbol << "\n";
}
std::vector<YahooDownload> ReadFileYahoo(const std::string& downloaded_data,const std::string& symbol)
{
    int64_t lines = NumberOfLines(downloaded_data);
    std::vector<YahooDownload> data = ReadCSV(downloaded_data, symbol.c_str());
    std::cout << "Downloaded " << lines << " lines of data for " << symbol << "\n";
    return data;
}
std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
int main(int argc, char **argv)
{
    std::string symbols_str;
    std::string start_str;
    std::string end_str;
    std::vector<std::string> symbols;
    std::tm start{0};
    std::tm end{0};
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message")
    ("symbol,s", po::value<std::string>(&symbols_str)->default_value("AAPL"), "symbol to download (Separate multiple symbols with a comma)")
    ("start-date,d", po::value<std::string>(&start_str)->default_value("2022-01-01"), "start date (YYYY-MM-DD)")
    ("end-date,e", po::value<std::string>(&end_str)->default_value("2022-12-31"), "end date (YYYY-MM-DD)")
    ("create,c", "create csv file")
    ("read,r", "read csv file");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }
    std::istringstream start_date(start_str);
    start_date >> std::get_time(&start, "%Y-%m-%d");
    std::istringstream end_date(end_str);
    end_date >> std::get_time(&end, "%Y-%m-%d");
    symbols = split(symbols_str, ',');
    std::vector<std::future<std::string>> futures(symbols.size());
    for (int i = 0; i < symbols.size(); i++)
    {
        futures[i] = std::async(std::launch::async, DownloadStock, symbols[i], start, end);
    }
    std::vector<std::string> downloaded_data(symbols.size());
    for (int i = 0; i < symbols.size(); i++)
    {
        futures[i].wait();
        downloaded_data[i] = futures[i].get();
    }
    if (vm.count("create"))
    {
        for (int i = 0; i < symbols.size(); i++)
        {
            CreateFileYahoo(downloaded_data[i], symbols[i]);
        }
    }
    if (vm.count("read"))
    {
        std::vector<std::vector<YahooDownload>> data(symbols.size());
        for (int i = 0; i < symbols.size(); i++)
        {
            data[i] = ReadFileYahoo(downloaded_data[i], symbols[i]);
        }
    }
    return 0;
}