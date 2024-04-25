#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/uuid.h>

#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Lesson2_Exercise3, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) -1)

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

//Declare the Company identifier (Company ID)
#define COMPANY_ID_CODE 0x0059

#define USER_BUTTON DK_BTN1_MSK

// Creat an LE Advertising Parameters varible 
static struct bt_le_adv_param *adv_param = 
    BT_LE_ADV_PARAM(BT_LE_ADV_OPT_NONE, /* No options specified */
    800,  /* Min Advertising Interval 500ms (800*0.625ms) */
    801,  /* Max Advertising Interval 500.625ms (801*0.625ms) */
    NULL); /* Set to NULL for undirected advertising */

/*Declare the advertising packet */
    static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};


static const struct bt_data sd[] = {
    /* Include the 16-bytes (128-Bits) UUID of the LBS service in the scan response packet*/
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)),
};
/// Add the definition of callback function and update the advertising data dynamically
static void button_changed(uint32_t button_state, uint32_t has_changed){
    if (has_changed & button_state & USER_BUTTON)
    {
        adv_mfg_data.number_press += 1;
        bt_le_adv_update_data(ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    }
    

}

static int init_button(void){
    int err;
    err = dk_buttons_init(button_changed);
    if(err){
        printk("Cannot init buttons (err: %d)\n", err);
    }
    return err;
}


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
    //Setup buttons on your board
    err = init_button();
    if(err){
        printk("Button init failed (err %d)\n", err);
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
    err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err){
        LOG_ERR("Advertising failed to start (err %d)\n", err);
        return;
    }
    
    LOG_INF("Advertising successfully started\n");
    //LOG_INF("%d\n", ARRAY_SIZE(sd));
    //LOG_INF("%d\n", sizeof(sd));

    for (;;)
    {
        dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
        k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
    }
}
