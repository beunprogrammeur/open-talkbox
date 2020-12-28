/*
 * usbd_midi_if.c
 *
 *  Created on: Dec 28, 2020
 *      Author: vincent
 */


#include "usbd_midi_if.h"
#include "usbd_midi.h"

__weak void MIDI_CC_Received(uint8_t channel, uint8_t code, uint16_t value) {}
__weak void MIDI_Note_On_Received(uint8_t channel, uint8_t key, uint16_t velocity) {}
__weak void MIDI_Note_Off_received(uint8_t channel, uint8_t key) {}


int8_t MIDI_Transmit(uint8_t* buff, uint8_t length);
int8_t MIDI_Receive(uint8_t* buff, uint8_t length);

USBD_MIDI_ItfTypeDef USBD_MIDI_Interface_fops_FS =
{
		MIDI_Transmit,
		MIDI_Receive,
};

int8_t MIDI_Receive(uint8_t* buff, uint8_t length)
{
	uint8_t channel = buff[1] & 0x0f;

	switch(buff[0])
	{
		case 0b1001: MIDI_Note_On_Received(channel, buff[2], buff[3]); break;
		case 0b1000: MIDI_Note_Off_received(channel, buff[2]);         break;
		case 0b1011: MIDI_CC_Received(channel, buff[2], buff[3]);      break;
		default: /* Not implemented message type */                    break;
	}

	return 0;
}

int8_t MIDI_Transmit(uint8_t* buff, uint8_t length)
{
	// TODO: add your outgoing message handling here
	return 0;
}
