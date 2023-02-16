#ifndef _DPOT_CTRL_H_
#define _DPOT_CTRL_H_
#pragma once

#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

class CDpotCtrl
{
public:
    CDpotCtrl();
    virtual ~CDpotCtrl();
    static CDpotCtrl* Instance();

public:
    bool initialize();
    bool set_pot_value(uint8_t value);
    bool set_resistance_wb(float res);

private:
    static CDpotCtrl* _instance;
    spi_device_handle_t m_handle;
    spi_transaction_t m_spi_transaction;
};

inline CDpotCtrl* GetDPotCtrl() {
    return CDpotCtrl::Instance();
}

#ifdef __cplusplus
};
#endif
#endif