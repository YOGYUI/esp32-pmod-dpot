#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_
#pragma once

#include "esp_http_server.h"

#ifdef __cplusplus
extern "C" {
#endif

class CWebServer
{
public:
    CWebServer();
    virtual ~CWebServer();
    static CWebServer* Instance();

public:
    bool start();
    bool stop();

private:
    static CWebServer* _instance;
    httpd_handle_t m_handle;

    bool register_uri_handler();
    static esp_err_t uri_handler(httpd_req_t *req);
};

inline CWebServer* GetWebServer() {
    return CWebServer::Instance();
}

#ifdef __cplusplus
};
#endif
#endif