#ifndef VNEHC_List_Error_H__
#define VNEHC_List_Error_H__

enum VNEHC_List_Error
{
    VNEHC_List_Error_VERSION = 100,
    VNEHC_List_Error_None = 1,
    VNEHC_List_Error_I2C,
    VNEHC_List_Error_UART,
    VNEHC_List_Error_SIG_NOT_3V3,
    VNEHC_List_Error_SIG_OVER_3V3,
    VNEHC_List_Error_SIG_LOWER_3V3,
    VNEHC_List_Error_PWR_OVER_CURRENT,
    VNEHC_List_Error_PWR_VOLT_LOWER,
    VNEHC_List_Error_PWR_VOLT_HIGHER,
    VNEHC_List_Error_PORT3_R_PULLDOWN_FAIL,
    VNEHC_List_Error_PORT3_R_PULLUP_FAIL,
    VNEHC_List_Error_PORT3_CURRENT_LOWER,
    VNEHC_List_Error_PORT3_CURRENT_HIGHER,
    VNEHC_List_Error_SIG_PIN3_SHORTED_PIN4,
};

#endif