# SPDX-License-Identifier: GPL-2.0
#
# Makefile for ALSA
#

snd-usb-audio-objs := 	card.o \
			clock.o \
			endpoint.o \
			format.o \
			helper.o \
			mixer.o \
			mixer_quirks.o \
			mixer_scarlett.o \
			mixer_us16x08.o \
			pcm.o \
			proc.o \
			quirks.o \
<<<<<<< HEAD
			stream.o \
			badd.o
=======
			stream.o
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f

snd-usbmidi-lib-objs := midi.o

# Toplevel Module Dependency
obj-$(CONFIG_SND_USB_AUDIO) += snd-usb-audio.o snd-usbmidi-lib.o

obj-$(CONFIG_SND_USB_UA101) += snd-usbmidi-lib.o
obj-$(CONFIG_SND_USB_USX2Y) += snd-usbmidi-lib.o
obj-$(CONFIG_SND_USB_US122L) += snd-usbmidi-lib.o

obj-$(CONFIG_SND) += misc/ usx2y/ caiaq/ 6fire/ hiface/ bcd2000/
obj-$(CONFIG_SND_USB_LINE6)	+= line6/
<<<<<<< HEAD
obj-$(CONFIG_SND_USB_AUDIO_QMI) += usb_audio_qmi_v01.o usb_audio_qmi_svc.o
=======
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
