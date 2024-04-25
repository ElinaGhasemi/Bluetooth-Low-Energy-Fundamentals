#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Lesson2_Exercise2, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) -1)

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

//Declare the Company identifier (Company ID)
#define COMPPANY_ID_CODE 0x0059

//Declare the structure for your custom data 
typedef struct adv_mfg_data {
    uint16_t company_code; /* Company Identifier Code. */
    uint16_t number_press; /* Number of times Button 1 is pressed */

}adv_mfg_data_type;

// Creat an LE Advertising Parameters varible 
static struct bt_le_adv_param *adv_param = 
    BT_LE_ADV_PARAM(BT_LE_ADV_OPT_NONE, /* No options specified */
    800,  /* Min Advertising Interval 500ms (800*0.625ms) */
    801,  /* Max Advertising Interval 500.625ms (801*0.625ms) */
    NULL); /* Set to NULL for undirected advertising */

    static adv_mfg_data_type adv_mfg_data = {COMPPANY_ID_CODE, 0X00};

/*Declare the advertising packet */
    static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
    // Include the Manufacturer Specific Data in the advertising packet.
    BT_DATA(BT_DATA_MANUFACTURE, (unsigned char *) &adv_mfg_data, sizeof(adv_mfg_data)),
};

/*Declare the URL data to include in the scan response */
static unsigned char url_data[] ={0x17,'/','/','a','c','a','d','e','m','y','.',
                                 'n','o','r','d','i','c','s','e','m','i','.',
                                 'c','o','m'};

static const struct bt_data sd[] = {
    /*Include the URL data in the scan response packet*/
    BT_DATA(BT_DATA_URI,url_data,sizeof(url_data)),
};

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
        printk("Button init failed (err %d)\n", err)
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
    //LOG_INF("%d\n", ARRAY_SIZE(sd));
    //LOG_INF("%d\n", sizeof(sd));

    for (;;)
    {
        dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
        k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
    }
}
