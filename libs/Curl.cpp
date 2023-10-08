#include <string>
#include <iostream>
#include <curl/curl.h>

static size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

static int CurlDebugCallback (CURL *handle, curl_infotype type, char *data, size_t size, void *clinetp){
    std::string text;
    std::string info;
    switch (type) {
        case CURLINFO_TEXT:
            text = "== Info:";
            info = std::string(data, size);
        case CURLINFO_HEADER_OUT:
            text = "=> Send header:";
            info = std::string(data, size);
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data: " + std::to_string(size);
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data: " + std::to_string(size);
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header:";
            info = std::string(data, size);
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data: " + std::to_string(size);
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data: " + std::to_string(size);
            break;
        default: /* in case a new one is introduced to shock us */
            return 0;
    }
    std::cout << "CURL : "<<text.c_str();
    if (info.size() > 0)
        std::cout << info.c_str();
    std::cout << std::endl;
    return 0;

}