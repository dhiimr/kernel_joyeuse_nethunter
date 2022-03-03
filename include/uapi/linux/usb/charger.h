/*
 * This file defines the USB charger type and state that are needed for
 * USB device APIs.
 */

#ifndef _UAPI__LINUX_USB_CHARGER_H
#define _UAPI__LINUX_USB_CHARGER_H

/*
 * USB charger type:
 * SDP (Standard Downstream Port)
 * DCP (Dedicated Charging Port)
 * CDP (Charging Downstream Port)
 * ACA (Accessory Charger Adapters)
 */
enum usb_charger_type {
<<<<<<< HEAD
	UNKNOWN_TYPE,
	SDP_TYPE,
	DCP_TYPE,
	CDP_TYPE,
	ACA_TYPE,
=======
	UNKNOWN_TYPE = 0,
	SDP_TYPE = 1,
	DCP_TYPE = 2,
	CDP_TYPE = 3,
	ACA_TYPE = 4,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

/* USB charger state */
enum usb_charger_state {
<<<<<<< HEAD
	USB_CHARGER_DEFAULT,
	USB_CHARGER_PRESENT,
	USB_CHARGER_ABSENT,
=======
	USB_CHARGER_DEFAULT = 0,
	USB_CHARGER_PRESENT = 1,
	USB_CHARGER_ABSENT = 2,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

#endif /* _UAPI__LINUX_USB_CHARGER_H */
