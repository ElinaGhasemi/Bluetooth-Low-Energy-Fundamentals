#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

/*Declare the advertising packet */
static const struct bt_data ad[] = {
    /*Set the advertising flags */
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    /*Set the advertising packet data*/
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),


};

static unsigned char url_data[] ={0x17,'/','/','a','c','a','d','e','m','y','.',
                                 'n','o','r','d','i','c','s','e','m','i','.',
                                 'c','o','m'};

static const struct bt_data sd[] = {
    /*Include the URL data in the scan response packet*/
    BT_DATA(BT_DATA_URI,url_data,sizeof(url_data)),
};

void main(void){

    int err;
    err = bt_enable(NULL);
    if (err)
    {
        LOG_ERR("Bluetooth init failed (err %d)\n", err);
        return;
    }

    LOG_INF("Bluetooth initialized\n");
    







}