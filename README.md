# Bop-It
// Junior Design Bop! It Project
// Brandon Ferruzza
// Daniel Feathers
// Veronica Roth
// The purpose of this program is to create a Bop-IT! toy capable of providing the user three types of minigames to play.

// This function sets up the ATMega by designating pins to specific inputs and outputs
void setup() 
{
  // Assigning input pin for the tempo slider potentiometer
  pinMode(A0, INPUT);
  
  // Assigning input pin for the volume knob potentiometer
  //pinMode(, INPUT);
  
  // Assigning input pin for the turn table rotary encoder
  //pinMode(, INPUT);
  
  // Assigning input pin for the speaker
  //pinMode(, INPUT);
  
  // Assigning input pin for the button that starts the game
  //pinMode(, INPUT);
  
  // Assigning output pin 13 for the LED that lights up over potentometer
  pinMode(13, OUTPUT);
  
  // Assigning output pin XX for the LED that lights up over volume
  //pinMode(, OUTPUT);
  
  // Assigning output pin XX for the LED that lights up over turn table
  //pinMode(, OUTPUT);
  
  // Assigning output pin for the OLED screen 
  //pinMode(, OUTPUT);
}

// Main function
void loop() 
{
  // Int variable to keep track of the score 
  int score = 0;
  
  // Boolean variable to keep track of whether the task was completed successfully
  bool successful = true;
  
  // Int variable to keep track of the time, which is initialized at 3 seconds
  float allotedRunTime = 3000;

  // Continue the game as long as the user is successful
  while(successful = true)
  {
    // Randomly pick a number between 1 and 3 to choose a minigame
    int choice = random(1, 3);
    
    // Volume Knob 
    if (choice == 1)
    {
       //Calls the volume knob function
       successful = volumeKnob(allotedRunTime, score);
    }
    
    // Tempo Slider
    else if (choice == 2)
    {
      // Calls the tempo slider function
      successful = tempoSlider(allotedRunTime, score);
    }
    
    // Turn Table
    else if(choice == 3)
    {
      // Calls the turn table function
      successful = turnTable(allotedRunTime, score);
    }
  }
}

// Volume Knob minigame
bool volumeKnob(float allotedRunTime, int score)
{
    // Play a voice audio of a DJ saying the specified voice clip
    
    // Light up the LED avove the slider 

    // The time it took since the program started 
    float initialTime = millis();
		
		// Time since the minigame began
		float currentTime = millis();
    
    // Defining a treshold for the diffrence between two voltages to count as a pass
    // Need to get this value by testing but temp 0.5v for now  
    int minVoltage = 0.5;
		
		// Get the initial voltage before the minigame officially begins
		float initialVoltage = analogRead(A0) * (5.0 / 1023.0);
    
		// While loop that checks the current status of the minigame
    while ((currentTime - initialTime) < allotedRunTime)
    {
      // Get the current time
      currentTime = millis();

      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      float currentVoltage = analogRead(A0) * (5.0 / 1023.0); 

      // If the difference in voltage is large enough and the user did it before time ran out, the user was successful
      if (abs(initialVoltage - currentVoltage) >= minVoltage)
      {
        // Add one point to the score and return to the main program
        score = score + 1;
				return TRUE;
      }
    }
    
    // Return false if the user fails to complete the task in time
    return FALSE;  
}


// Tempo Slider minigame
bool tempoSlider(float allotedRunTime, int score)
{
    // Play a voice audio of a DJ saying the specified voice clip
    
    // Light up the LED avove the slider 

    // The time it took since the program started 
    float initialTime = millis();
		
		// Time since the minigame began
		float currentTime = millis();
    
    // Defining a treshold for the diffrence between two voltages to count as a pass
    // Need to get this value by testing but temp 0.5v for now  
    int minVoltage = 0.5;
		
		// Get the initial voltage before the minigame officially begins
		float initialVoltage = analogRead(A0) * (5.0 / 1023.0);
    
		// While loop that checks the current status of the minigame
    while ((currentTime - initialTime) < allotedRunTime)
    {
      // Get the current time
      currentTime = millis();

      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      float currentVoltage = analogRead(A0) * (5.0 / 1023.0); 

      // If the difference in voltage is large enough and the user did it before time ran out, the user was successful
      if (abs(initialVoltage - currentVoltage) >= minVoltage)
      {
        // Add one point to the score and return to the main program
        score = score + 1;
				return TRUE;
      }
    }
    
    // Return false if the user fails to complete the task in time
    return FALSE;  
}

// Turn Table minigame
bool volumeKnob(float allotedRunTime, int score)
{
    // Play a voice audio of a DJ saying the specified voice clip
    
    // Light up the LED avove the slider 

    // The time it took since the program started 
    float initialTime = millis();
		
		// Time since the minigame began
		float currentTime = millis();
    
    // Defining a treshold for the diffrence between two voltages to count as a pass
    // Need to get this value by testing but temp 0.5v for now  
    int minVoltage = 0.5;
		
		// Get the initial voltage before the minigame officially begins
		float initialVoltage = analogRead(A0) * (5.0 / 1023.0);
    
		// While loop that checks the current status of the minigame
    while ((currentTime - initialTime) < allotedRunTime)
    {
      // Get the current time
      currentTime = millis();

      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      float currentVoltage = analogRead(A0) * (5.0 / 1023.0); 

      // If the difference in voltage is large enough and the user did it before time ran out, the user was successful
      if (abs(initialVoltage - currentVoltage) >= minVoltage)
      {
        // Add one point to the score and return to the main program
        score = score + 1;
				return TRUE;
      }
    }
    
    // Return false if the user fails to complete the task in time
    return FALSE;  
}
