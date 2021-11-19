// Bop-It! Eta Group
// ECE 1895 - Bop-It! Design Project 2
// Brandon Ferruzza, BJF54
// Daniel Feathers, DWF16
// Veronica Roth, VGR3
// The purpose of this program is to create a Bop-It! toy capable of providing the user three types of minigames to play.

//------------------------------------------------ INITIALIZATION ----------------------------------------------------

// Include the libraries required for the audio and visual displays
#include <U8x8lib.h>
#include <SD.h>
#include "TMRpcm.h"
#include <SPI.h>

// Define the input pins for the start button
#define STARTBUTTON_PIN   4

// Define the input pins for the minigame hardware
#define KNOB_PIN          A2
#define SLIDER_PIN        A0
#define TURNTABLE_PIN     8

// Define the output pins for the LEDs indicating which minigame to play
#define LED_KNOB          3
#define LED_SLIDER        A1
#define LED_TURNTABLE     7

// Define the output pins for the OLED display screen
#define OLED_CS           2
#define OLED_RESET        0
#define OLED_DC           1

// Define the output pins for the RGB success LED
#define LED_SUCCESS_GREEN 6
#define LED_SUCCESS_RED   5

// Define the output pins for the audio output
#define SPEAKER_PIN       9
#define SD_ChipSelectPin  10

// Initializes the OLED screen
U8X8_SSD1306_128X64_NONAME_4W_SW_SPI u8x8
(
  /* clock=*/ 13, /* data=*/ 11, OLED_CS, OLED_DC, OLED_RESET
);

// Create a global TMRpcm variable to be used as the speaker
TMRpcm tmrpcm;

// Create a global boolean variable to check for the first run
bool firstPlay;

// This function sets up the ATMega by designating pins to specific inputs and outputs
void setup() 
{
  // Assigning input pins for the minigame inputs
  pinMode(STARTBUTTON_PIN, INPUT);
  pinMode(KNOB_PIN, INPUT);
  pinMode(SLIDER_PIN, INPUT);
  pinMode(TURNTABLE_PIN, INPUT);
  
  // Assigning output pins for the LED that lights up over the current minigame
  pinMode(LED_KNOB, OUTPUT);
  pinMode(LED_SLIDER, OUTPUT);
  pinMode(LED_TURNTABLE, OUTPUT);

  // Assigning output pin for the success RGB LED
  pinMode(LED_SUCCESS_GREEN, OUTPUT);
  pinMode(LED_SUCCESS_RED, OUTPUT);

  // Turn on the OLED Screen and select its font
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Hello World!");

  // Turn on the Speaker
  tmrpcm.speakerPin = PB1;
  Serial.begin(9600);

  // Make sure that the SD card can be read
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }

  // Set the volume of the speaker
  tmrpcm.setVolume(6);

  // Check for the button press during the first playthrough
  firstPlay = true;
}

//------------------------------------------------ MAIN ----------------------------------------------------

// Main function
void loop() 
{
  // Make sure no LEDs are on
  digitalWrite(LED_KNOB, LOW);
  digitalWrite(LED_SLIDER, LOW);
  digitalWrite(LED_TURNTABLE, LOW);
  digitalWrite(LED_SUCCESS_GREEN, HIGH);
  digitalWrite(LED_SUCCESS_RED, LOW);

  // Variables for the start button's state
  int startButtonState;
  int lastStartButtonState;

  // Only run this during first playthrough
  if (firstPlay == true)
  {
    // Keep the user looped until they press the start button
    startButtonState = digitalRead(STARTBUTTON_PIN);
    lastStartButtonState = startButtonState;
  
    while (startButtonState == lastStartButtonState)
    {
      startButtonState = digitalRead(STARTBUTTON_PIN);
    }
  
    // Show to the user that the game has begun
    digitalWrite(LED_SUCCESS_RED, HIGH);
    digitalWrite(LED_SUCCESS_GREEN, LOW);
    delay(2500);
    digitalWrite(LED_SUCCESS_GREEN, HIGH);
    delay(1250);
  }
  
  // Begin playing the background music
  tmrpcm.play("mario.wav");
  tmrpcm.loop(1);

  // Draw a welcome message on the OLED screen
  u8x8.drawString(0,0,"Hello World!");
  
  // Int variable to keep track of the score 
  int score = 0;

  // Int variable to keep track of the time, which is initialized at 3 seconds
  float allotedRunTime = 3000;
  
  // Boolean variable to keep track of whether the task was completed successfully
  bool successful = true;

  // Continue the game as long as the user is successful
  while(successful == true)
  {
    // Display the current score
    u8x8.print(score);
    
    // Change the alloted time for each minigame depending on progress
    if (score >= 5)
    {
      allotedRunTime = 2000;
    
      // Time for a score of 10 or higher
      if (score >= 10)
      {
        allotedRunTime = 1500;
      
        // Time for a score of 20 or higher
        if (score >= 20)
        {
          allotedRunTime = 1000;
        
          // Time for a score of 30 or higher
          if (score >= 30)
          {
            allotedRunTime = 500;
          }
        }
      }
    }
  
    // Randomly pick a number between 1 and 3 to choose a minigame
    int choice = 3;//random(1,4);
    
    // Volume Knob 
    if (choice == 1)
    {
       // Calls the volume knob function
       successful = volumeKnob(allotedRunTime, score);
    }
    
    // Tempo Slider
    else if (choice == 2)
    {
      // Calls the tempo slider function
     successful = tempoSlider(allotedRunTime, score);
    }
    
    // Turn Table
    else if (choice == 3)
    {
      // Calls the turn table function
      successful = turnTable(allotedRunTime, score);
    }

    // Delay until next game is chosen depends on score
    if (score < 5)
    {
      delay(750);
    }
    
    else if (score < 10)
    {
      delay(500);
    }

    else if (score < 20)
    {
      delay(250);
    }

    else
    {
      delay(0);
    }
  }

  // User failed their minigame
  digitalWrite(LED_KNOB, LOW);
  digitalWrite(LED_SLIDER, LOW);
  digitalWrite(LED_TURNTABLE, LOW);
  digitalWrite(LED_SUCCESS_GREEN, HIGH);
  digitalWrite(LED_SUCCESS_RED, HIGH);
  
  // NEED TO FIGURE OUT HOW TO STOP MUSIC
  // NEED TO FIGURE OUT HOW TO DISPLAY "Your final score was XXX. Press the Start button to play again!"

  // Print the user's final score
  u8x8.print(score);

  // Keep the user looped until they press the Start button
  startButtonState = digitalRead(STARTBUTTON_PIN);
  lastStartButtonState = startButtonState;

  while (startButtonState == lastStartButtonState)
  {
    startButtonState = digitalRead(STARTBUTTON_PIN);
  }

  // Show to the user that the game has restarted
  digitalWrite(LED_SUCCESS_RED, HIGH);
  digitalWrite(LED_SUCCESS_GREEN, LOW);
  delay(2500);
  digitalWrite(LED_SUCCESS_GREEN, HIGH);
  delay(1250);

  // Set the bool variable to false since it's not the first playthrough
  firstPlay = false;
}

//------------------------------------------------ MINIGAMES ----------------------------------------------------

// Volume Knob minigame
bool volumeKnob(float allotedRunTime, int score)
{   
    // Light up the LED above the selected minigame and turn off the success LED
    digitalWrite(LED_KNOB, HIGH);
    digitalWrite(LED_SUCCESS_GREEN, HIGH);
    digitalWrite(LED_SUCCESS_RED, HIGH);

    // Get the initial voltage before the minigame officially begins
    float initialVoltage = analogRead(KNOB_PIN) * (5.0 / 1023.0);

    // Defining a treshold for the diffrence between two voltages to count as a pass
    // Need to get this value by testing but temp 0.5v for now  
    float minVoltage = 0.5;

    // The time it took since the program started 
    float initialTime = millis();
    
    // Time since the minigame began
    float currentTime = initialTime;

    // While loop that checks the current status of the minigame
    while (abs(currentTime - initialTime) < allotedRunTime)
    {
      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      float currentVoltage = analogRead(KNOB_PIN) * (5.0 / 1023.0); 

      // If the difference in voltage is large enough and the user did it before time ran out, the user was successful
      if (abs(initialVoltage - currentVoltage) >= minVoltage)
      {
        // Turn on the success LED
        digitalWrite(LED_KNOB, LOW);
        digitalWrite(LED_SUCCESS_GREEN, LOW);

        // Display the updated score
        score = score + 1;
        //u8x8.setCursor(0,0);
        //u8x8.print(score);
        
        return true;
      }

      // Get the current time
      currentTime = millis();
    }
    
    // Return false if the user fails to complete the task in time
    digitalWrite(LED_KNOB, LOW);
    digitalWrite(LED_SUCCESS_RED, LOW);
    delay(1250);
    return false;  
}

// Tempo Slider minigame
bool tempoSlider(float allotedRunTime, int score)
{
    // Light up the LED above the selected minigame and turn off the success LED
    digitalWrite(LED_SLIDER, HIGH);
    digitalWrite(LED_SUCCESS_GREEN, HIGH);
    digitalWrite(LED_SUCCESS_RED, HIGH);

    // The time it took since the program started 
    float initialTime = millis();
    
    // Time since the minigame began
    float currentTime = millis();
    
    // Defining a treshold for the diffrence between two voltages to count as a pass
    // Need to get this value by testing but temp 0.5v for now  
    float minVoltage = 0.5;
    
    // Get the initial voltage before the minigame officially begins
    float initialVoltage = analogRead(SLIDER_PIN) * (5.0 / 1023.0);

    // While loop that checks the current status of the minigame
    while ((currentTime - initialTime) < allotedRunTime)
    {
      // Get the current time
      currentTime = millis();

      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      float currentVoltage = analogRead(SLIDER_PIN) * (5.0 / 1023.0); 

      // If the difference in voltage is large enough and the user did it before time ran out, the user was successful
      if (abs(initialVoltage - currentVoltage) >= minVoltage)
      {
        // Turn on the success LED
        digitalWrite(LED_SLIDER, LOW);
        digitalWrite(LED_SUCCESS_GREEN,LOW);

        // Display the updated score
        score = score + 1;
        //u8x8.setCursor(0,0);
        //u8x8.print(score);
        
        return true;
      }
    }
    
    // Return false if the user fails to complete the task in time
    digitalWrite(LED_SLIDER, LOW);
    digitalWrite(LED_SUCCESS_RED, LOW);
    delay(1250);
    return false;  
}

// Turn Table minigame
bool turnTable(float allotedRunTime, int score)
{
    // Light up the LED above the selected minigame and turn off the success LED
    digitalWrite(LED_TURNTABLE, HIGH);
    digitalWrite(LED_SUCCESS_GREEN, HIGH);
    digitalWrite(LED_SUCCESS_RED, HIGH);

    // The time it took since the program started 
    float initialTime = millis();
    
    // Time since the minigame began
    float currentTime = millis();

    // Get the initial position of the rotary encoder
    int initialPosition = digitalRead(TURNTABLE_PIN);

    // While loop that checks the current status of the minigame
    while (abs(currentTime - initialTime) < allotedRunTime)
    {
      // Get the current time
      currentTime = millis();

      // Get the current position of the rotary encoder
      int currentPosition = digitalRead(TURNTABLE_PIN);

      if (initialPosition != currentPosition)
      {
        // Turn on the success LED
        digitalWrite(LED_TURNTABLE, LOW);
        digitalWrite(LED_SUCCESS_GREEN,LOW);
        
        // Display the updated score
        score = score + 1;
        //u8x8.setCursor(0,0);
        //u8x8.print(score);
        
        return true;
      }
    }
    
    // Return false if the user fails to complete the task in time
    digitalWrite(LED_TURNTABLE, LOW);
    digitalWrite(LED_SUCCESS_RED, LOW);
    delay(1250);
    return false; 
  }
