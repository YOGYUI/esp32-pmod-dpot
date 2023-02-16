#include "webserver.h"
#include "logger.h"
#include "definition.h"
#include "dpotctrl.h"

CWebServer* CWebServer::_instance = nullptr;

CWebServer::CWebServer()
{
    m_handle = nullptr;
}

CWebServer::~CWebServer()
{
}

CWebServer* CWebServer::Instance()
{
    if (!_instance) {
        _instance = new CWebServer();
    }

    return _instance;
}

bool CWebServer::start()
{
    stop();

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = WEB_SERVER_PORT;
    config.uri_match_fn = httpd_uri_match_wildcard;

    GetLogger(eLogType::Info)->Log("Starting HTTP Server (port %d)", config.server_port);
    esp_err_t result = httpd_start(&m_handle, &config);
    if (result != ESP_OK) {
        GetLogger(eLogType::Error)->Log("Failed to start HTTP Server (ret: %d)", result);
        stop();
        return false;
    }

    register_uri_handler();
    
    GetLogger(eLogType::Info)->Log("Started");
    return true;
}

bool CWebServer::stop()
{
    if (m_handle) {
        esp_err_t result = httpd_stop(m_handle);
        if (result != ESP_OK) {
            GetLogger(eLogType::Error)->Log("Failed to stop HTTP Server (ret: %d)", result);
            m_handle = nullptr;
            return false;
        }
        m_handle = nullptr;
        GetLogger(eLogType::Info)->Log("Stopped");
    }

    return true;
}

bool CWebServer::register_uri_handler()
{
    httpd_uri_t conf;
    conf.uri = "/";
    conf.method = HTTP_GET;
    conf.handler = CWebServer::uri_handler;
    conf.user_ctx = nullptr;

    if (!m_handle) {
        GetLogger(eLogType::Error)->Log("Server is not started");
        return false;
    }

    esp_err_t result = httpd_register_uri_handler(m_handle, &conf);
    if (result != ESP_OK) {
        GetLogger(eLogType::Error)->Log("Failed to register uri handler %s (ret: %d)", conf.uri, result);
        return false;
    }

    return true;
}

esp_err_t CWebServer::uri_handler(httpd_req_t *req)
{
    
    return ESP_OK;
}