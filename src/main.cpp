#include <Arduino.h>

#include "FlipDot/FlipDot.h"

String buffer = "";
char incomingByte = 0;
int decodeResult = 0;
String encodedFrame = "";

int passed = 0;

FlipDot flipDot;

void doTest(String testString)
{
    decodeResult = flipDot.decodeFrame(testString);
    Serial.printf("decodeResult: %d\n", decodeResult);
    flipDot.dump();

    Serial.printf("Encoded Result:\n");

    encodedFrame = flipDot.encodeFrame();
    encodedFrame.trim();

    Serial.println("");

    Serial.println(testString);
    Serial.println(encodedFrame);

    Serial.println("");

    passed = (testString == encodedFrame);

    Serial.printf("Passed: %d\n", passed);

    Serial.println("");

    flipDot.clear();
}

void setup()
{
    Serial.begin(115200);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.printf("Test #1:\n");
    doTest(":01000102FFFD");

    Serial.printf("Test #2:\n");
    doTest(":01000202FFFC");

    Serial.printf("Test #3:\n");
    doTest(":010002040FEA");

    Serial.printf("Test #4:\n");
    doTest(":0100020200FB");

    Serial.printf("Test #5:\n");
    doTest(":010002040FEA");

    Serial.printf("Test #6:\n");
    doTest(":01000203A159");

    Serial.printf("Test #7:\n");
    doTest(":010002059563");

    Serial.printf("Test #8:\n");
    doTest(":1000000008B300100C100078030028000000000066");

    Serial.printf("Test #9:\n");
    doTest(":00000101FE");

    Serial.printf("Waiting for input...\n");
}

void loop()
{
    if (Serial.available())
    {
        buffer = Serial.readStringUntil('\n');

        buffer.trim();
        Serial.printf("Received:\t%s\n", buffer.c_str());

        int decodeResult = flipDot.decodeFrame(buffer);
        if (decodeResult == 0)
        {

            String newFrame = flipDot.encodeFrame();
            Serial.printf("newFrame:\t%s\n", newFrame.c_str());
            Serial.printf("\n");
            flipDot.dump();
            Serial.printf("\n");
        }
        else
        {
            Serial.printf("Error decoding Frame: %d\n", decodeResult);
        }

        buffer = "";
    }
}