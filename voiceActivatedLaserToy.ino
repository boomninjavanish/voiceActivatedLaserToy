#include <ServoEasing.h>
#include "config.h"
#include "dataStructures.h"

// create the two servos; pitch is the top servo, yaw is the bottom
ServoEasing pitchServo;
ServoEasing yawServo;

// track the state of the yaw and pitch
int currentPitch = 90;
int currentYaw = 90;


// the minimum/maxiumum pitch and yaw; calibrate these to the size of the room
int minPitch = 115;
int maxPitch = 140;

int minYaw = 67;
int maxYaw = 100;

// track the time for heart beat
int currentTime = millis();

// create the feeds from the Adafruit IO
AdafruitIO_Feed *catLaserYawFeed = io.feed("catLaserYaw");
AdafruitIO_Feed *catLaserPitchFeed = io.feed("catLaserPitch");
AdafruitIO_Feed *catLaserInitPlayFeed = io.feed("catLaserInitPlay");
AdafruitIO_Feed *catLaserPollFeed = io.feed("catLaserPoll");
AdafruitIO_Feed *catLaserToggleFeed = io.feed("catLaserToggle");

void setup()
{
    // home servos and setup laser 
    homeLaser();
    pinMode(14, OUTPUT); // laser pin = 14

    // setup serial connection
    Serial.begin(115200);
    // wait for serial monitor
    //while( ! Serial);

    // connect to Adafruit IO Service
    Serial.print("Connecting to Adafruit IO");
    io.connect();

    // handle messages from the Adafruit IO feeds
    catLaserPitchFeed->onMessage(handlePitchMessage);
    catLaserYawFeed->onMessage(handleYawMessage);
    catLaserToggleFeed->onMessage(handleLaserMessage);
    catLaserInitPlayFeed->onMessage(handlePlayMessage);

    // wait for Adafruit IO connection
    while(io.status() < AIO_CONNECTED) 
    {
        // print dots to terminal and blink laser
        Serial.print(".");
        delay(250);
        toggleLaser(HIGH);
        delay(250);
        toggleLaser(LOW);
    }

    // once connected to Adafruit IO
    Serial.println();
    Serial.println(io.statusText());
    catLaserPitchFeed->get();
    catLaserYawFeed->get();
    catLaserToggleFeed->get();

    // reset all status indicators on Adafruit IO
    catLaserToggleFeed->save("OFF");
    catLaserPitchFeed->save(currentPitch);
    catLaserYawFeed->save(currentYaw);

}

void loop()
{
	// stay connected to Adafruit IO and process incoming commands
    io.run();

    // let Adafruit know we are alive
    sendHeartBeatToAdafruit();
}

// turn the servos on or off; send a LOW for off or HIGH for on
void toggleServos(int servosState)
{
    if (servosState == HIGH)
    {
        pitchServo.attach(13); // top servo pin = 13
        yawServo.attach(12); // bottom servo pin = 12
    } else if (servosState == LOW)
    {
        pitchServo.detach();
        yawServo.detach();
    }
}

// turn the laser on and off; send a LOW for off or HIGH for on
void toggleLaser(int laserState)
{
    digitalWrite(14, laserState); // laser pin = 14

    // update Adafruit IO
    String stateName;
    if (laserState == HIGH)
    {
        //catLaserToggleFeed->save("ON");
    } 
    else
    {
        //catLaserToggleFeed->save("OFF");
    }
    
}

// move to laser to home position
void homeLaser(){
    currentPitch = 20;
    currentYaw = 110;
    setSpeedForAllServos(30);
    toggleServos(HIGH);
    pitchServo.setEaseTo(currentPitch);
    yawServo.setEaseTo(currentYaw);
    synchronizeAllServosStartAndWaitForAllServosToStop();

    // make it "pop" back into place
    yawServo.write(90);

    // update the Adafruit IO values
    //catLaserPitchFeed->save(currentPitch);
    //catLaserYawFeed->save(currentYaw);

    delay(2000); // give enough time to get there
    toggleServos(LOW);
}

// handle the Adafruit IO messages for the pitch servo
void handlePitchMessage(AdafruitIO_Data *data)
{
    int angle = data->toInt();
    toggleServos(HIGH);
    pitchServo.write(angle);
    delay(2000);
    toggleServos(LOW);
}

// handle the Adafruit IO messages for the pitch servo
void handleYawMessage(AdafruitIO_Data *data)
{
    int angle = data->toInt();
    toggleServos(HIGH);
    yawServo.write(angle);
    delay(2000);
    toggleServos(LOW);
}

// handle the Adafruit IO messages for turning the laser on and off
void handleLaserMessage(AdafruitIO_Data *data)
{
    String state = data->toString();
    if (state == "ON")
    {
        toggleLaser(HIGH);
    } else if (state == "OFF")
    {
        toggleLaser(LOW);
    }
}

// handle the Adafruit IO messages for initiation of play session
void handlePlayMessage(AdafruitIO_Data *data)
{
    String toggleValue = data->toString();
    
    if(toggleValue == "PLAYING")
    {
        // start play session
        makeRandomCommandSet();
        executePlayCommandSet(randomCommandSet, 50);
        //executePlayCommandSet(laserWallJump, countElements(laserWallJump));
        makeRandomCommandSet();
        executePlayCommandSet(randomCommandSet, 50);

        catLaserInitPlayFeed->save("OFF");
        homeLaser();
    
    } 
}

// sends a '1' to Adafruit IO every minute to let it know we are alive
void sendHeartBeatToAdafruit()
{
    int timeDifferential = millis() - currentTime;
    if (timeDifferential > 60000)
    {
        catLaserPollFeed->save(1);
        currentTime = millis();
    }
}

// execute a play command setup
void executePlayCommandSet(PlayCommandSet commandSet[], int elementsInCommandSet)
{
    // attach servos
    toggleServos(HIGH);

    setSpeedForAllServos(140);

    for (int i = 0; i < elementsInCommandSet; i++)
    {
        
        toggleLaser(commandSet[i].laserToggle);

        // smoothly move laser to next location
        int diffBetweenPitch = commandSet[i].pitch - commandSet[i-1].pitch;

        pitchServo.setEaseTo(commandSet[i].pitch);
        yawServo.setEaseTo(commandSet[i].yaw);
        synchronizeAllServosStartAndWaitForAllServosToStop();

        delay(commandSet[i].delayTime);
    }

    // detach servos and shutoff laser
    toggleServos(LOW);
    toggleLaser(LOW);
}

// make a laser floor trace game
 void makeRandomCommandSet()
{
    //int numberOfElements = countElements(randomCommandSet);
    int numberOfElements = 50;

    for (int i = 0; i < numberOfElements; i++)
    {
        // consitent delay between movements
        randomCommandSet[i].delayTime = random(300,500);

        // rarely turn off the laser
        int randomNumber = random(50);
        if (randomNumber == random(50))
        {
            randomCommandSet[i].laserToggle = LOW;
        }
        else
        {
            randomCommandSet[i].laserToggle = HIGH;
        }

        // keep pitch between 120 and 180
        randomCommandSet[i].pitch = random(minPitch, maxPitch);

        // keep yaw between 30 and 100
        randomCommandSet[i].yaw = random(minYaw, maxYaw);
    }
}

// count the number of elements in the command set
int countElements(PlayCommandSet commandSet[])
{        
    int elementsInCommandSet = sizeof(commandSet) / sizeof(commandSet[0]);
    return elementsInCommandSet;
}
