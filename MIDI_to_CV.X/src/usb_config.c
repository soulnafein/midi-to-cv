#include "usb.h"
#include "usb_host_midi.h"
#include "usb_host.h"

// *****************************************************************************
// Client Driver Function Pointer Table for the USB Embedded Host foundation
// *****************************************************************************

CLIENT_DRIVER_TABLE usbClientDrvTable[] =
{
    {
        USBHostMIDIInit,
        USBHostMIDIEventHandler,
        0
    }
};

// *****************************************************************************
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************

USB_TPL usbTPL[] =
{
    //{ INIT_CL_SC_P( 3ul, 1ul, 2ul ), 0, 0, {TPL_CLASS_DRV} } // (null)
    { INIT_CL_SC_P( 1ul, 3ul, 0ul ), 0, 0, {TPL_CLASS_DRV} }, // MIDI Audio Subclass 
};


