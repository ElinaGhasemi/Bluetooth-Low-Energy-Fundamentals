#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

/*Declare the advertising packet */
static const struct bt_data ad[] = {
    /*Set the advertising flags */
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    /*Set the advertising packet data*/
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),


};