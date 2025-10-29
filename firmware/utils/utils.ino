/*
 * Based on "ReceiveDump.cpp" from IRremote
 * https://github.com/Arduino-IRremote/Arduino-IRremote
 * See More: github.com/diaslui/klinus
 */

#include <Arduino.h>

#include "PinDefinitionsAndMore.h"

#if !defined(RAW_BUFFER_LENGTH)
// For air condition remotes it may require up to 750. Default is 200.
#if !((defined(RAMEND) && RAMEND <= 0x4FF) || (defined(RAMSIZE) && RAMSIZE < 0x4FF))
#define RAW_BUFFER_LENGTH 730 // this allows usage of 16 bit raw buffer, for RECORD_GAP_MICROS > 20000
#endif
#endif
// #define MARK_EXCESS_MICROS    40    // Adapt it to your IR receiver module. 40 is recommended for the cheap VS1838 modules at high intensity.

// #define RECORD_GAP_MICROS 12000 // Default is 8000. Activate it for some LG air conditioner protocols
// #define DEBUG // Activate this for lots of lovely debug output from the decoders.

#include <IRremote.hpp>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200); // Status message will be sent to PC at 9600 baud

#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/ || defined(USBCON) /*STM32_stm32*/ \
    || defined(SERIALUSB_PID) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_attiny3217)
    while (!Serial)
        ;
#endif

    Serial.println("Welcome to Klinus Utils 1.0.1 (pt-br)");
    Serial.println("");
    Serial.println(" _  ___ _                   _   _ _   _ _     ");
    Serial.println("| |/ / (_)_ __  _   _ ___  | | | | |_(_) |___ ");
    Serial.println("| ' /| | | '_ \\| | | / __| | | | | __| | / __|");
    Serial.println("| . \\| | | | | | |_| \\__ \\ | |_| | |_| | \\__ \\");
    Serial.println("|_|\\_\\_|_|_| |_|\\__,_|___/  \\___/ \\__|_|_|___/");
    Serial.println(" (adapted from IRremote by lui -> https://github.com/diaslui/klinus)");

    Serial.println("Para Corretamente utilizar Garanta que as seguintes condições foram cumpridas ::");
    Serial.println("Tens um Modulo Ir Receiver e um Arduino Uno");
    Serial.println("A Saída OUT do Ir Receiver se encontra na porta digital 2 no arduino");
    Serial.println("VCC -> 5v & GND -> GND");

    Serial.println("------------------------ Vamos começar");

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("* Pronto para receber sinais IR "));
}

void loop()
{
    if (IrReceiver.decode())
    {
        Serial.println();
        Serial.println();
        Serial.println("-----------------------------------------------------------------------------------");
        Serial.println("Um Novo Sinal IR foi captado :");

        IrReceiver.printIRResultShort(&Serial);
        // Check if the buffer overflowed
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW)
        {
            Serial.println(F("Try to increase the \"RAW_BUFFER_LENGTH\" value of " STR(RAW_BUFFER_LENGTH) " in " __FILE__));
            // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
        }
        else
        {
            if (IrReceiver.decodedIRData.protocol == UNKNOWN)
            {
                Serial.println(F("Ruído recebido ou protocolo desconhecido (ou ainda não ativado)"));
            }

            Serial.print(F("Resultado como matriz de microssegundos - compensada com MARK_EXCESS_MICROS="));
            Serial.println(MARK_EXCESS_MICROS);
            IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, true);

            Serial.print("-----------------------------------------------------------------------------------");

            IrReceiver.resume();
        }
    }
}
