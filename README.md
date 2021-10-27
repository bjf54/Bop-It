# Bop-It
//Jinior Design Bop! It Project

void setup() {
  
  //Assigning potentometer pin input 
  pinMode( A0, INPUT ); 
  //Assigning volume pin input
  //pinMode( , INPUT );
  //Assigning turn table pin input
  //pinMode( , INPUT );
  //Assigning speaker pin input
  //pinMode( , INPUT );
  //Starting the game pin input
  //pinMode( , INPUT );
  
  //Output pin 13 ad LED that lights up over potentometer
  pinMode( 13, OUTPUT );
  //Output pin XX ad LED that lights up over volume
  //pinMode( , OUTPUT );
  //Output pin XX ad LED that lights up over turn table
  //pinMode( , OUTPUT );
  //Output pin for screen 
  //pinMode( , OUTPUT );
}

void loop() {

  //Score 
  int score = 0;
  //If its done right 
  bool successful = true;

  while( successful = true )
  {
    //Randomly picks a number between 1 and 3 
    int choice = random(1, 3);
  
    //Time starts at 3 seconds
    int allotedRunTime = 3;
    
    //Volume 
    if ( choice == 1 )
    {
       //Calls the volume function
    }
    
    //Tempo Slider
    else if ( choice == 2 )
    {
      //Calls the tempo slider function
      bool successful = tempoSlider( allotedRunTime, score );
    }
    
    //Trun Table
    else if( choice == 3 )
    {
    
    } 
  }

}

int tempoSlider ( int allotedRunTime, int score )
{
    //Play a voice audio of a DJ saying the specified voice clip
    
    //Light up the LED avove the slider 

    //The time it took since the program started running 
    //Idk if this is what we want but like???????????????????????
    int timeTaken = millis();
    
    //Defining a treshold for the diffrence between two voltages to count as a pass
    //Need to get this numbers by testing but temp 0.5v for now  
    int minvVoltage = 0.5;
    
    //Read the input on analog pin 0
    int sensorValueInt = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
    float voltageInt = sensorValueInt * (5.0 / 1023.0); 
  
    //Can change but right now the delay is the length of time for that level in seconds
    //minus 1 secoond before the next reading ???????????????
    delay( allotedRunTime - 1000 ); 
    
    //Read the input again
    int sensorValueFin = analogRead(A0);
    //Convert the analog reading to a voltage again
    float voltageFin = sensorValueFin * (5.0 / 1023.0); 
  
    //If the diffrence in voltage is large enough and the uder did it before time ran out
    //Sucessful run
    if ( (abs(voltageInt - voltageFin) >= minvVoltage) && (allotedRunTime > timeTaken) )
    {
      //Add one point to the score 
      score = score + 1;
      
    }
    //Failed run
    else 
    {
        //Bool goes to false and shows final score
        //Do i even need this??????????????????111
    }
    
    //Maybe return score idk if we should return anything esle 
    return score;  
}
