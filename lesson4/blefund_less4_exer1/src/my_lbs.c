/** @file
 *  @brief LED Button Service (LBS) sample
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include "my_lbs.h"

#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(Lesson4_Exercise1);

static bool button_state;
static struct my_lbs_cb lbs_cb;

/* Implement the write callback function of the LED characteristic */

/* Implement the read callback function of the Button characteristic */

/* LED Button Service Declaration */
/* Create and add the MY LBS service to the Bluetooth LE stack */
BT_GATT_SERVICE_DEFINE(my_lbs_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_LBS),
		       /* Create and add the Button characteristic */
		       BT_GATT_CHARACTERISTIC(BT_UUID_LBS_BUTTON, BT_GATT_CHRC_READ,
					      BT_GATT_PERM_READ, read_button, NULL, &button_state),

/* A function to register application callbacks for the LED and Button characteristics  */
int my_lbs_init(struct my_lbs_cb *callbacks)
{
	if (callbacks) {
		lbs_cb.led_cb = callbacks->led_cb;
		lbs_cb.button_cb = callbacks->button_cb;
	}

	return 0;
}
