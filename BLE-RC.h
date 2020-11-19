/*
 * BLE-RC.h
 *
 *  Created on: Nov 19, 2020
 *      Author: hephaestus
 */

#ifndef BLE_RC_H_
#define BLE_RC_H_



//==============================================================================
// Robot controlled by VR Box using BLE on an ESP32
// Target:   DoIt ESP32 DEVKIT V1, ESP-VROOM-32 module
// Compiler: Arduino 1.8.10
// SDK:      ESP32 Arduino SDK by Expressif Ver 1.0.4
//==============================================================================
// ESP32 (DoIt ESP32 DEVKIT V1, ESP-VROOM-32 module) board
// In Arduino Board Manager, Select the following;
// Arduino Board: "ESP32 Dev Module"
// Flash Mode: QIO
// Flash Size: 4MB (32Mb)
// Flash Frequency: "80MHz"
// Upload Speed: 921600
// Core Debug Level: None
//******************************************************************************

// VRBOX is a handheld Bluetooth BLE device with a joystick and six useful
// buttons. This code shows how to setup the ESP32 as a BLE client to work
// with the VRBOX BLE server. Most of the code is generic to any BLE server.
// The name of the BLE server to search for and the services and characteristics
// are specific to the VRBOX server.
// You can use this code as a primer on how to connect other BLE servers to the
// ESP32 or as the basis of any ESP32 project that you want to control using the
// VRBOX device. The code should work with any ESP32 module.

// The VR BOX server will shut itself off if there is no activity for 5 minutes.
// This will cause the ESP32 to lose the Bluetooth connection and do a reset.

// I bought mine at the local 5 Below store. The box is labeled; "Spektrum VR Control
// Bluetooth RemoteController". I have also seen similar looking devices on the
// Internet for upwards of $20.00. "VR BOX" is the name the device uses to identify
// itself to other bluetooth devices.

// Each defined task requires its own dedicated RAM allocation for its stack
// How much RAM to allocate is determined by how nested the task is and how
// many variables are stored on the stack (local variables). The default size
// defined here is for 5K * 4 bytes/32 bit word, so 20K bytes
// If you are getting;
// JGuru Meditation Error: Core  0 panoc'd (Unhandled debug exception)
// Debug excaption reason: Stack canary watchpoint triggered (task name)
// then increase the TaskStackSize by 1024 until the Stack canary errors stop.
// The ESP32 VROOM module has 288K bytes of RAM.
#define TaskStackSize   5120

// The blue and green LEDs are used to indicate when the ESP32 is scanning for
// BLE servers and when the ESP32 has connected to the BLE server. The LEDs
// can be moved to any GPIO pin (except LED, that is the builtin blue LED) that
// is not input only.

#include <BLEDevice.h>
#include <Arduino.h>

//------ VR Box Definitions -----
enum
{
  VB_TRIGGERS = 0,
  VB_JOYX,
  VB_JOYY,
  VB_BTNAB,
  VB_BTNCD,
  VB_NUMBYTES
};

// ===== VR Box Button Masks =====
#define VB_LOW_TRIGGER    0x01
#define VB_UPR_TRIGGER    0x02
#define VB_BUTTON_A       0x10
#define VB_BUTTON_B       0x20
#define VB_BUTTON_C       0x01
#define VB_BUTTON_D       0x02
#define FRESHFLAG         0x80

#define JOYTIMEOUT        30      // joystick no activity timeout in mS

#define JoyStickDeadZone  0

#define ServerName  "VR BOX"      // change this if your server uses a different name

//----- ESP32 Definitions ------------------------------------------------------
//----- ESP32 GPIO Allocation -----
#define SCL         22      // GPIO 22 -> I2C SCL
#define SDA         21      // GPIO 21 -> I2C SDA

#define BUILTINLED  2       // GPIO 2  -> built-in blue LED, on ->high, off -> low
#define GREENLED    15      // GPIO 15 -> Green LED - lit -> scanning
#define BLUELED     5       // GPIO 2  -> Blue LED  - lit -> connected
#define REDLED      4       // GPIO 4  -> Red LED

// these values are for GPIO driven LEDs. BUILTIN Blue LED is opposite.
#define LEDOFF    HIGH
#define LEDON     LOW

// ===== VRBOX Modes =====
// This code assumes you are using the Mouse Mode
// @ + A -> Music & Video mode
// @ + B -> Horizontal Game mode
// @ + C -> Vertical Game mode
// @ + D -> Mouse Mode  // use this mode
//  4 byte notification, Trigger Sws, Joystick X, Joystick Y, 0x00

// All four modes send data. However each mode uses different byte positions and
// values for each of the switches. The joystick acts like a 'D' pad when not in
// Mouse Mode (no analog value).

typedef void (*NotifyCallback)(BLERemoteCharacteristic*, uint8_t*, size_t, bool);

#endif /* BLE_RC_H_ */
