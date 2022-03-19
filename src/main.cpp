#include <Arduino.h>

#include <FlipDot.hpp>

String buffer = "";
char incomingByte = 0;
int decodeResult = 0;
String encodedFrame = "";

int passed = 0;

FlipDot flipDot;


void doTest(String testString)
{
    static int testNumber = 1;

    Serial.printf("Test #%d:\n", testNumber);

    decodeResult = flipDot.decodeFrame(testString);

    Serial.printf("decodeResult: %d\n", decodeResult);

    flipDot.dump();

    Serial.printf("Encoded Result:\n");

    encodedFrame = flipDot.encodeFrame();

    Serial.println("");

    testString.trim();
    encodedFrame.trim();

    Serial.printf("testString:\t%s\n", testString.c_str());
    Serial.printf("encodedFrame:\t%s\n", encodedFrame.c_str());

    Serial.println("");

    Serial.printf("Passed: %d\n", (testString == encodedFrame));

    Serial.println("");

    flipDot.clear();

    testNumber++;
}

void setup()
{
    Serial.begin(115200);

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    doTest(":01000102FFFD\r\n");

    doTest(":01000202FFFC\r\n");

    doTest(":010002040FEA\r\n");

    doTest(":0100020200FB\r\n");

    doTest(":010002040FEA\r\n");

    doTest(":01000203A159\r\n");

    doTest(":010002059563\r\n");

    doTest(":1000000008B300100C100078030028000000000066\r\n");

    doTest(":00000101FE\r\n");

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