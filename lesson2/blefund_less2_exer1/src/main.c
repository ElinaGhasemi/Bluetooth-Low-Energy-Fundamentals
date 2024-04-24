#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Lesson2_Exercise1, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) -1)

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

/*Declare the advertising packet */
static const struct bt_data ad[] = {
    /*Set the advertising flags */
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    /*Set the advertising packet data*/
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),


};

/*Declare the URL data to include in the scan response */
static unsigned char url_data[] ={0x17,'/','/','a','c','a','d','e','m','y','.',
                                 'n','o','r','d','i','c','s','e','m','i','.',
                                 'c','o','m'};

static const struct bt_data sd[] = {
    /*Include the URL data in the scan response packet*/
    BT_DATA(BT_DATA_URI,url_data,sizeof(url_data)),
};

void main(void){

    int blink_status = 0;
    int err;

    LOG_INF("Starting Lesson 2 - Exercise 1 \n");

    err = dk_leds_init();
    if (err)
    {
        LOG_ERR("LEDs init failed (err %d)\n", err);
        return;
    }
    

    err = bt_enable(NULL);
    if (err)
    {
        LOG_ERR("Bluetooth init failed (err %d)\n", err);
        return;
    }

    LOG_INF("Bluetooth initialized\n");

    /*Start advertising*/
    err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err){
        LOG_ERR("Advertising failed to start (err %d)\n", err);
        return;
    }
    
    LOG_INF("Advertising successfully started\n");







}