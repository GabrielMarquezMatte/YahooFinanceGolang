#include "reader.hpp"
void CreateCSV(std::string_view downloaded_data,const std::string& symbol){
    std::ofstream file;
    file.open(symbol+".csv");
    file << downloaded_data;
    file.close();
}
std::vector<YahooDownload> ReadCSV(std::string_view downloaded_data,const char * symbol){
    std::vector<YahooDownload> data;
    std::stringstream ss(downloaded_data.data());
    std::string line;
    std::getline(ss,line);
    while(std::getline(ss,line)){
        std::stringstream lineStream(line);
        std::string cell;
        YahooDownload row;
        std::getline(lineStream,cell,',');
        std::istringstream date(cell);
        date >> std::get_time(&row.Date,"%Y-%m-%d");
        std::getline(lineStream,cell,',');
        row.Open = std::stod(cell);
        std::getline(lineStream,cell,',');
        row.High = std::stod(cell);
        std::getline(lineStream,cell,',');
        row.Low = std::stod(cell);
        std::getline(lineStream,cell,',');
        row.Close = std::stod(cell);
        std::getline(lineStream,cell,',');
        row.AdjClose = std::stod(cell);
        std::getline(lineStream,cell,',');
        row.Volume = std::stoll(cell);
        data.push_back(row);
    }
    return data;
}