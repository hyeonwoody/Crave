// #include <iostream>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <string>
// #include "Crave.h"
// #include <curl/curl.h>
// #include <libxml/HTMLparser.h>

// #ifdef _MSC_VER
// #define COMPARE(a, b) (!_stricmp((a), (b)))
// #else
// #define COMPARE(a, b) (!strcasecmp((a), (b)))
// #endif

// struct Context
// {
//   Context(): addTitle(false) { }
 
//   bool addTitle;
//   std::string title;
// };

// static void StartElement(void *voidContext,
//                          const xmlChar *name,
//                          const xmlChar **attributes)
// {
//   Context *context = static_cast<Context *>(voidContext);
  
//   if (COMPARE(const_cast<const char*>(reinterpret_cast<const char*>(name)), "TITLE")) {
//     context->title = "";
//     context->addTitle = true;
//   }
//   (void) attributes;
// }
 
// //
// //  libxml end element callback function
// //

// static void EndElement(void *voidContext,
//                        const xmlChar *name)
// {
//   Context *context = static_cast<Context *>(voidContext);
 
//   if (COMPARE(reinterpret_cast<const char*>(name), "TITLE") == 0)
//     context->addTitle = false;
// }
 
// //
// //  Text handling helper function
// //

// static void handleCharacters(Context *context,
//                              const xmlChar *chars,
//                              int length)
// {
//   if(context->addTitle)
//     context->title.append(reinterpret_cast<const char *>(chars), length);
// }
 
// //
// //  libxml PCDATA callback function
// //

// static void Characters(void *voidContext,
//                        const xmlChar *chars,
//                        int length)
// {
//   Context *context = static_cast<Context *>(voidContext);
 
//   handleCharacters(context, chars, length);
// }
 
// //
// //  libxml CDATA callback function
// //

// static void cdata(void *voidContext,
//                   const xmlChar *chars,
//                   int length)
// {
//   Context *context = static_cast<Context *>(voidContext);
 
//   handleCharacters(context, chars, length);
// }
 
// //
// //  libxml SAX callback structure
// //

// //  libcurl variables for error strings and returned data
// static char errorBuffer[CURL_ERROR_SIZE];
// static std::string buffer;

// //  libcurl write callback function
// static int writer(char *data, size_t size, size_t nmemb,
//                   std::string *writerData)
// {
//   if(writerData == NULL)
//     return 0;
 
//   writerData->append(data, size*nmemb);
 
//   return size * nmemb;
// }

// void processElement (xmlNodePtr node){
//   if (node == nullptr){
//     std::cerr << "Failed to get root element." << std::endl;
//     return;
//   }

//   if (node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, reinterpret_cast<const xmlChar*>("a")) == 0) {
//         xmlChar* text = xmlNodeGetContent(node);
//         if (text != nullptr) {
//             std::cout << "Tag Text: " << text << std::endl;
//             xmlFree(text);
//         }
//     }

//   for (xmlNodePtr child = node->children; child; child = child->next) {
//         processElement(child);
//   }
  
// }

// static void parseHtml(const std::string &html,
//                       std::string &title)
// {
//   htmlParserCtxtPtr ctxt;
//   Context context;

//   htmlDocPtr doc = htmlReadDoc(reinterpret_cast<const xmlChar*>(html.c_str()), nullptr, nullptr, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
//   if (doc == nullptr){
//     std::cerr << "Failed to parse HTML" <<std::endl;
//     return;
//   }

//   xmlNodePtr root =  xmlDocGetRootElement(doc);
  
//   processElement (root);

//   xmlFreeDoc(doc);
//   xmlCleanupParser();

  

//   // ctxt = htmlCreatePushParserCtxt(&saxHandler, &context, "", 0, "",
//   //                                 XML_CHAR_ENCODING_NONE);
 
//   // htmlParseChunk(ctxt, html.c_str(), html.size(), 0);
//   // htmlParseChunk(ctxt, "", 0, 1);
 
//   // htmlFreeParserCtxt(ctxt);
 
//   title = context.title;
// }


// static bool init(CURL *&pCurl, char *url)
// {
//   CURLcode curlCode;
 
//   pCurl = curl_easy_init();
 
//   if(pCurl == NULL) {
//     fprintf(stderr, "Failed to create CURL connection\n");
//     exit(EXIT_FAILURE);
//   }
 
//   curlCode = curl_easy_setopt(pCurl, CURLOPT_ERRORBUFFER, errorBuffer);
//   if(curlCode != CURLE_OK) {
//     fprintf(stderr, "Failed to set error buffer [%d]\n", curlCode);
//     return false;
//   }
 
//   curlCode = curl_easy_setopt(pCurl, CURLOPT_URL, url);
//   if(curlCode != CURLE_OK) {
//     fprintf(stderr, "Failed to set URL [%s]\n", errorBuffer);
//     return false;
//   }
 
//   curlCode = curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1L);
//   if(curlCode != CURLE_OK) {
//     fprintf(stderr, "Failed to set redirect option [%s]\n", errorBuffer);
//     return false;
//   }
 
//   curlCode = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, writer);
//   if(curlCode != CURLE_OK) {
//     fprintf(stderr, "Failed to set writer [%s]\n", errorBuffer);
//     return false;
//   }
 
//   curlCode = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &buffer);
//   if(curlCode != CURLE_OK) {
//     fprintf(stderr, "Failed to set write data [%s]\n", errorBuffer);
//     return false;
//   }
 
//   return true;
// }
// int CMain::Main (char* url) {
//     std::cout << url<<std::endl;
//     CURL * pCurl;

//     CURLcode code;
//     std::string title;
    
//     curl_global_init(CURL_GLOBAL_DEFAULT);

//     // Initialize CURL connection

//     if(!init(pCurl, url)) {
//         fprintf(stderr, "Connection initialization failed\n");
//         exit(EXIT_FAILURE);
//     }

//     code = curl_easy_perform(pCurl);

//     printf("BUfefr : %s\n", buffer);
//     // Parse the (assumed) HTML code
//     parseHtml(buffer, title);

    
 
//   // Display the extracted title
//     printf("Title: %s\n", title.c_str());

//     curl_easy_cleanup(pCurl);
//     curl_global_cleanup();

//     return 0;
// }

// void Usage(){
//     printf ("Usage : Crave -[Option Parameter] -[Flag Parameter]");
// }

// int main (int argc, char* argv[]){
//     CMain app;
//     if (argc == 1){
//         argv[1] = "https://namu.wiki/w/%ED%9A%A8%EC%97%B0";
//         //Usage();
//         app.Main(argv[1]);
//         //return 1;
//     }
//     else {
        
//         app.Main(argv[1]);
//         return 0;
//     }
// }


#include <iostream>
#include <string>

#include "NamuCenter.h"

// static size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
//     size_t totalSize = size * nmemb;
//     output->append(static_cast<char*>(contents), totalSize);
//     return totalSize;
// }

// static int CurlDebugCallback (CURL *handle, curl_infotype type, char *data, size_t size, void *clinetp){
//     std::string text;
//     std::string info;
//     switch (type) {
//         case CURLINFO_TEXT:
//             text = "== Info:";
//             info = std::string(data, size);
//         case CURLINFO_HEADER_OUT:
//             text = "=> Send header:";
//             info = std::string(data, size);
//             break;
//         case CURLINFO_DATA_OUT:
//             text = "=> Send data: " + std::to_string(size);
//             break;
//         case CURLINFO_SSL_DATA_OUT:
//             text = "=> Send SSL data: " + std::to_string(size);
//             break;
//         case CURLINFO_HEADER_IN:
//             text = "<= Recv header:";
//             info = std::string(data, size);
//             break;
//         case CURLINFO_DATA_IN:
//             text = "<= Recv data: " + std::to_string(size);
//             break;
//         case CURLINFO_SSL_DATA_IN:
//             text = "<= Recv SSL data: " + std::to_string(size);
//             break;
//         default: /* in case a new one is introduced to shock us */
//             return 0;
//     }
//     std::cout << "CURL : "<<text.c_str();
//     if (info.size() > 0)
//         std::cout << info.c_str();
//     std::cout << std::endl;
//     return 0;

// }

std::string getHtml(const std::string& url) {
    std::string html;

    CURL* curl = curl_easy_init();
    if (curl) {
        // curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
        // curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);        

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch URL: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize libcurl." << std::endl;
    }

    curl_global_cleanup();
    return html;
}









int main(int argc, char* argv[]) {

    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2>" << std::endl;
        return 1;
    }

    CNamuCenter* namu = new CNamuCenter(argv[1], argv[2]);
    namu->m_threadStatus = THREAD_ACTIVE;
    namu->Start();
    
    // std::string url = "https://namu.wiki/w/%ED%9A%A8%EC%97%B0";
    // std::string html = getHtml(url);
    // std::cout <<html<<std::endl;
    //crawlHtml(html);
    while (namu->m_threadStatus != THREAD_INACTIVE)
    {
        
    }
    namu->Stop();
    if (namu)
    {
        delete (namu);
        namu = nullptr;
    }
    return 0;
}