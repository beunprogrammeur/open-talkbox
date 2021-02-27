/*
 * usbd_midi_if.c
 *
 *  Created on: Dec 28, 2020
 *      Author: vincent
 */


#include "usbd_midi_if.h"
#include "usbd_midi.h"


__weak void MIDI_Message_Received(uint8_t status, uint8_t data1, uint8_t data2);

int8_t MIDI_Transmit(uint8_t* buff, uint8_t length);
int8_t MIDI_Receive(uint8_t* buff, uint8_t length);

USBD_MIDI_ItfTypeDef USBD_MIDI_Interface_fops_FS =
{
		MIDI_Transmit,
		MIDI_Receive,
};

int8_t MIDI_Receive(uint8_t* buff, uint8_t length)
{
	if(length != 4) return 0;
	MIDI_Message_Received(buff[1], buff[2], buff[3]);

	return 0;
}

int8_t MIDI_Transmit(uint8_t* buff, uint8_t length)
{
	// TODO: add your outgoing message handling here
	return 0;
}
