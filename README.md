# Bop-It
Jinior Design Bop! It Porject

void setup() {
  
  //Assigning potentiometer pinout 
  pinMode( A0, INPUT ); 
}

void loop() {

  //Keeps track of score
  int score = 0;

  //Randomly picks a number between 1 and 3 
  int choice = random(1, 3);
  
  //Volume 
  if ( choice == 1 )
  {
  
  }
  
  //Tempo Slider
  if ( choice == 2 )
  {
    //Calls the tempo slider function
    int tempo = tempoSlider( choice, score );
  }
  
  //Turn Table
  if( choice == 3 )
  {
  
  }

}

int tempoSlider ( choice, score )
{
    //Play a voice audio of a DJ saying the specified voice clip
    
    //Light up the LED above the slider 

    //Time counter 
    
    //Defining a threshold for the difference between two voltages to count as a pass
    //Need to get this numbers by testing 
    int minvVoltage = 0.5;
    
    //Read the input on analog pin 0
    int sensorValueInt = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
    float voltageInt = sensorValueInt * (5.0 / 1023.0); 
  
    //Can change but right now delay is the length of time for that level in seconds
    //minus 1 second before the next reading
    delay( runTime - 1000 ); 
    
    //Read the input again
    int sensorValueNew = analogRead(A0);
    //Convert the analog reading to a voltage again
    float voltageNew = sensorValueNew * (5.0 / 1023.0); 
  
    //If the difference in voltage is large enough and the user did it before time ran out
    //Successful run
    if ( (abs( voltageInt - voltageNew ) >= minvVoltage) && (allotedRunTime > timeTaken) )
    {
      //Add one point to the score 
      score = score + 1;

      //Need to display the score
      
    }
    //Failed run
    else 
    {
        //Bool goes to false and shows final score 
    }
        
    }
} 
