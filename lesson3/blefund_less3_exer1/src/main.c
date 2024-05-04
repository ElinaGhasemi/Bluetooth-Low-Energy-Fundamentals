#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>

#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Lesson3_Exercise1, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) -1)

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

struct bt_conn *my_conn = NULL;

// Create the advertising parameter for connectable advertising
static struct bt_le_adv_param *adv_param = 
    BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_IDENTITY, /* Connectable advertising and use identity address */
    800,  /* Min Advertising Interval 500ms (800*0.625ms) */
    801,  /* Max Advertising Interval 500.625ms (801*0.625ms) */
    NULL); /* Set to NULL for undirected advertising */
struct bt_conn *my_conn = NULL;

/*Declare the advertising packet */
    static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};


static const struct bt_data sd[] = {
    /* Include the 16-bytes (128-Bits) UUID of the LBS service in the scan response packet*/
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)),
};

/*Implement the callback functions */
void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err)
    {
        LOG_ERR("Connection error %d",err);
    }
    LOG_INF("Connected");
    my_conn = bt_conn_ref(conn);
    
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected. Reason %d", reason);
    bt_conn_unref(my_conn);
}

/*Declare the connection_callback structure */
struct bt_conn_cb connection_callbacks = {
    .connected = on_connected,
    .disconnected = on_disconnected, 
};


void main(void){

    int blink_status = 0;
    int err;

    LOG_INF("Starting Lesson 2 - Exercise 3 \n");

    err = dk_leds_init();
    if (err)
    {
        LOG_ERR("LEDs init failed (err %d)\n", err);
        return;
    }
    //Change the random static address */
    bt_addr_le_t addr;
    err = bt_addr_le_from_str ("FF:EE:DD:CC:BB:AA", "random", &addr);
    if(err){
        printk("Invalid BT address (err %d)\n", err);
    }

    err = bt_id_create (&addr, NULL);
    if (err < 0)
    {
        printk("Creating new ID failed (err %d)\n", err);
    }
    
    //Register our custom callbacks 
    bt_conn_cb_register(&connection_callbacks);

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
