#ifndef YAHOO_DOWNLOAD_H
#define YAHOO_DOWNLOAD_H
#include <curl/curl.h>
namespace program::download{
    class Download{
    public:
        Download();
        ~Download();
        void download(const char* url, const char* path);
    private:
        CURL* curl;
        CURLcode res;
    };
}
#endif