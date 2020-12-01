#include <stdlib.h>
#include "system.h"
#include "usb.h"
#include "usb_host_midi.h"
#include "leds.h"



static void handleMIDIPackets(void);
static void clearBuffer(void);
static unsigned int bufferSize();
static void readyFromMIDIKeyboard();
static void handleMIDIPacket(uint8_t, uint8_t, uint8_t);
static void removeKeypress(uint8_t note);

// Application specific
#define MIDI_USB_BUFFER_SIZE                (uint8_t)4
#define NUM_MIDI_PKTS_IN_USB_PKT            (uint8_t)1

typedef enum _APP_STATE
{
    DEVICE_NOT_CONNECTED,
    DEVICE_READY,
    ERROR_REPORTED      /* need to add application states for data interface */
} APP_STATE;

typedef enum
{
    READY = 0,
    WAITING

} BUFFER_STATE;


typedef struct
{
    BUFFER_STATE             TransferState;      // The transfer state of the endpoint
    uint8_t                 numOfMIDIPackets;   // Each USB Packet sent from a device has the possibility of holding more than one MIDI packet,
    uint8_t                 endpointIndex;                           //  so this is to keep track of how many MIDI packets are within a USB packet (between 1 and 16, or 4 and 64 bytes)
    USB_AUDIO_MIDI_PACKET*  bufferStart;        // The 2D buffer for the endpoint. There are MIDI_USB_BUFFER_SIZE USB buffers that are filled with numOfMIDIPackets
                                                //  MIDI packets. This allows for MIDI_USB_BUFFER_SIZE USB packets to be saved, with a possibility of up to 
                                                //  numOfMIDIPackets MID packets within each USB packet.
    USB_AUDIO_MIDI_PACKET*  pBufReadLocation;   // Pointer to USB packet that is being read from
    USB_AUDIO_MIDI_PACKET*  pBufWriteLocation;  // Pointer to USB packet that is being written to
}ENDPOINT_BUFFER;

typedef struct KEYPRESS KEYPRESS;

struct KEYPRESS {
    uint8_t note;
    uint8_t velocity;
    
    KEYPRESS* nextKeypress;
    
};


volatile APP_STATE  midiState;

MIDI_DEVICE *deviceHandle;

ENDPOINT_BUFFER    endpointBuffer;   
KEYPRESS* keypressBuffer;


/*********************************************************************
* Function: void APP_HostMIDIBasicTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized via
*   the APP_HostMIDIBasicInitialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void KEYBOARD_tasks()
{
    USBHostTasks();
    
    if (midiState != DEVICE_READY) {
        return;
    }

    handleMIDIPackets();
    readyFromMIDIKeyboard();
}

bool KEYBOARD_isButtonPressed() {
    return keypressBuffer != NULL;
}

unsigned short KEYBOARD_getNotePressed(int noteNumber) {
    unsigned short note = 0;
    KEYPRESS* keypress = keypressBuffer;
    unsigned short currentNoteNumber = 0;
    
    while(keypress != NULL) {
        if (currentNoteNumber == noteNumber) {
            note = keypress->note;
            break;
        }
        keypress = keypress->nextKeypress;
        currentNoteNumber++;
    }
    
    return note;
}

void readyFromMIDIKeyboard() {
    switch(endpointBuffer.TransferState) {
        case READY:
            clearBuffer();
            if(USBHostMIDIRead(deviceHandle, endpointBuffer.endpointIndex, endpointBuffer.pBufWriteLocation, bufferSize() ) == USB_SUCCESS )
            {
                endpointBuffer.TransferState = WAITING;
            }
            break;

        case WAITING:
            if(!USBHostMIDITransferIsBusy(deviceHandle, endpointBuffer.endpointIndex))
            {
                endpointBuffer.TransferState = READY;
                endpointBuffer.pBufWriteLocation += endpointBuffer.numOfMIDIPackets;

                // Check to see if we've gotten to the end of the USB buffer array
                if(endpointBuffer.pBufWriteLocation - endpointBuffer.bufferStart >= bufferSize())
                {
                    // If so, then loop it back to the beginning of the array
                    endpointBuffer.pBufWriteLocation = endpointBuffer.bufferStart;
                }
            }
            break;

    }    
}

void initializeEndpointBuffer(unsigned int endpointIndex) {
    // We will accept however many will fit inside the maximum USB packet size
    endpointBuffer.endpointIndex = endpointIndex;
    endpointBuffer.numOfMIDIPackets = USBHostMIDISizeOfEndpoint(deviceHandle, endpointIndex) / sizeof(USB_AUDIO_MIDI_PACKET);

    // And we want to start it off trying to read data
    endpointBuffer.TransferState = READY;
    endpointBuffer.bufferStart = malloc( sizeof(USB_AUDIO_MIDI_PACKET) * endpointBuffer.numOfMIDIPackets * MIDI_USB_BUFFER_SIZE );
    endpointBuffer.pBufReadLocation = endpointBuffer.bufferStart;
    endpointBuffer.pBufWriteLocation = endpointBuffer.bufferStart;
}

unsigned int bufferSize() {
    return endpointBuffer.numOfMIDIPackets * sizeof(USB_AUDIO_MIDI_PACKET);
}

static void clearBuffer() {
    memset(endpointBuffer.pBufWriteLocation, 0x00, bufferSize());
}

static bool onDeviceAttached(void *data) {
    uint8_t currentEndpoint;
    ENDPOINT_DIRECTION direction;
    deviceHandle = data;
    midiState = DEVICE_READY;

    for( currentEndpoint = 0; currentEndpoint < USBHostMIDINumberOfEndpoints(deviceHandle); currentEndpoint++ )
    {
        direction = USBHostMIDIEndpointDirection(deviceHandle, currentEndpoint);
        if (direction == IN)
        {
            initializeEndpointBuffer(currentEndpoint);

            break;
        }
    }    
    
    LEDS_keyboardAttached();

    return true;           
}

void handleMIDIPackets(void)
{
    // Check to see if the buffer has any packets to be read
    if (endpointBuffer.pBufReadLocation != endpointBuffer.pBufWriteLocation)
    {
        int8_t midiPktNumber;   
        uint8_t* midiPacket;

        // If so, then parse through the entire USB packet for each individual MIDI packet
        for(midiPktNumber = 0; midiPktNumber < endpointBuffer.numOfMIDIPackets; midiPktNumber++)
        {
            if(endpointBuffer.pBufReadLocation->Val == 0ul)
            {
                // If there's nothing in this MIDI packet, then skip the rest of the USB packet
                endpointBuffer.pBufReadLocation += endpointBuffer.numOfMIDIPackets - midiPktNumber;
                break;
            }    
            else
            {
                midiPacket = endpointBuffer.pBufReadLocation->v;
                handleMIDIPacket(midiPacket[1], midiPacket[2], midiPacket[3]);
                endpointBuffer.pBufReadLocation++;
            }
        }
        
        if (endpointBuffer.pBufReadLocation - endpointBuffer.bufferStart
            >= endpointBuffer.numOfMIDIPackets * MIDI_USB_BUFFER_SIZE) {
            // If so, then loop it back to the beginning of the array
            endpointBuffer.pBufReadLocation = endpointBuffer.bufferStart;
        }

    }        
}


void addKeypress(uint8_t note, uint8_t velocity) {
    KEYPRESS* keypressPointer = malloc(sizeof(KEYPRESS));
    KEYPRESS keypress = { note, velocity, keypressBuffer };
    *keypressPointer = keypress;
    keypressBuffer = keypressPointer;
}

void removeKeypress(uint8_t note) {
    KEYPRESS* previousKeypress = NULL;
    KEYPRESS* keypress = keypressBuffer;
    
    while(keypress != NULL) {
        if (keypress->note == note) {
            if (previousKeypress == NULL) {
                keypressBuffer = keypress->nextKeypress;
            } else {
                previousKeypress->nextKeypress = keypress->nextKeypress;
            }
            free(keypress);
            break;
        } else {
            previousKeypress = keypress;
            keypress = keypress->nextKeypress;
        }
    }
}

void onNoteOff(uint8_t note) {
    removeKeypress(note);
}

void onNoteOn(uint8_t note, uint8_t velocity) {
    addKeypress(note, velocity);
}

void handleMIDIPacket(uint8_t command, uint8_t note, uint8_t velocity) {
    if (command == 0x80 || (command == 0x90 && velocity == 0)) {
        onNoteOff(note);
    } else if (command == 0x90) {
        onNoteOn(note, velocity);
    }
}
 
bool USB_Host_ApplicationEventHandler( uint8_t address, USB_EVENT event, void *data, uint32_t size )
{
    switch( (int)event )
    {
        /* Standard USB host events ******************************************/
        case EVENT_VBUS_REQUEST_POWER:
        case EVENT_VBUS_RELEASE_POWER:
        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR: 
        case EVENT_TRANSFER:
            return true;
        case EVENT_MIDI_TRANSFER_DONE:
            return false;
        case EVENT_MIDI_ATTACH:
            return onDeviceAttached( data );
            return true;
        case EVENT_MIDI_DETACH:
            asm ("RESET");            
        default:
            break;
    }

    return false;

}