/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: sensor_control.c
 * @Description: 
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-1-5 16:21:15
 * @LastEditTime: 2021-1-5 16:21:15
 */

#include "sensor_control.h"
#include "tuya_gpio.h"
#include "soc_adc.h"
/***********************************************************
*************************types define***********************
***********************************************************/
typedef enum
{
    LOW = 0,
    HIGH,
}default_level;



DEVICE_DATA_T device_data = {0};


#define MAX_DEPTH                        (40)  // unit: mm

/***********************************************************
*************************IO control device define***********
***********************************************************/
#define IIC_SDA_PORT                     (6)
#define IIC_SCL_PORT                     (7)



/***********************************************************
*************************about adc init*********************
***********************************************************/
#define TEMP_ADC_DATA_LEN           (4)

tuya_adc_dev_t tuya_adc;

/***********************************************************
*************************about iic init*********************
***********************************************************/



/***********************************************************
*************************function***************************
***********************************************************/

STATIC VOID __ctrl_gpio_init(CONST TY_GPIO_PORT_E port, CONST BOOL_T high)
{
    tuya_gpio_inout_set(port, FALSE);
    tuya_gpio_write(port, high);
}

VOID app_device_init(VOID)
{
    INT_T op_ret = 0;
    
    // adc driver init
    tuya_adc.priv.pData = Malloc(TEMP_ADC_DATA_LEN * sizeof(USHORT_T));
    memset(tuya_adc.priv.pData, 0, TEMP_ADC_DATA_LEN*sizeof(USHORT_T));
    tuya_adc.priv.data_buff_size = TEMP_ADC_DATA_LEN; //设置数据缓存个数

}



OPERATE_RET app_get_all_sensor_data(VOID)
{
    OPERATE_RET ret = 0;

    tuya_hal_adc_init(&tuya_adc);
    tuya_hal_adc_value_get(TEMP_ADC_DATA_LEN, &device_data.sensor_value);
    PR_NOTICE("sensor_value = %d",device_data.sensor_value);
    tuya_hal_adc_finalize(&tuya_adc);
    if(device_data.sensor_value < 2000) {
        device_data.soil_state = wet;
    }else {
        device_data.soil_state = dry;
    }
    
    return ret;
}



VOID app_ctrl_handle(VOID)
{   
    PR_DEBUG("ctrl handle");

}

VOID app_ctrl_all_off(VOID)
{   
    ;
}