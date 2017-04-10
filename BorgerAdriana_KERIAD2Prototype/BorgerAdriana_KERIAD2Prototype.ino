/*Deze code zorgt ervoor dat de weerstand op Arduino pins wordt gemeten. Als deze hoger is dan "int minResistance" 
wordt het gezien als aanraking. 
A.d.h.v. waar de ezel wordt aangeraakt (in dit geval of er een positieve, neutrale of negatieve pin wordt aangeraakt)
geeft deze code een bepaalde toonhoogte terug.*/

// On-board led als extra check
int ledPin = 13;

//Buzzer pin
int buzzerPin = 8;

// Pin die naar het geleidende oppervlak gaat
int capSensePinPositive = 2;
int capSensePinNeutral = 4;
int capSensePinNegative = 6;

// Minimale weerstand die als aanraking mag worden gezien
int minResistance = 60;

// Vlaggetje dat kijkt of de negatieve pins al aangeraakt zijn
bool negativeTouch = false;


void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop()
{
  // Checkt of de positieve pin wordt aangeraakt
  if(readCapacitivePin(capSensePinPositive) > minResistance)
  {
    Serial.print("Positive: ");
    Serial.println(readCapacitivePin(capSensePinPositive));
    
    digitalWrite(ledPin, HIGH);
    //Waarde uit de pin * 22 (om het hoger te maken) wordt als toon gestuurd
    tone(buzzerPin, (readCapacitivePin(capSensePinPositive)*22)); 
    //Korte delay om het wat hyperder te laten klinken
    delay(60);
    noTone(buzzerPin);
  }

  // Checkt of de neutrale pin wordt aangeraakt
  else if(readCapacitivePin(capSensePinNeutral) > minResistance) 
  {
    Serial.print("Neutral: ");
    Serial.println(readCapacitivePin(capSensePinNeutral));
    
    digitalWrite(ledPin, HIGH);
    //Waarde uit de pin * 4 (om het nét hoger te maken) wordt als toon gestuurd
    tone(buzzerPin, (readCapacitivePin(capSensePinNeutral)*4));
    //Langere delay om het wat rustiger te laten klinken
    delay(180);
    noTone(buzzerPin);
  }

  // Checkt of de negatieve pin wordt aangeraakt
  else if(readCapacitivePin(capSensePinNegative) > minResistance) 
  {
    Serial.print("Negative: ");
    Serial.println(readCapacitivePin(capSensePinNegative));
    
    digitalWrite(ledPin, HIGH);

    // Checkt of de negatieve pin al is aangeraakt
    if (negativeTouch == false)
    {
      //Waarde uit de pin - 37 (om het lager te laten klinken) wordt als toon gestuurd
      tone(buzzerPin, (readCapacitivePin(capSensePinNegative) - 37));
      //Lange delay om de toon duidelijker te maken
      delay(230);
      noTone(buzzerPin);
      //Geeft aan dat de negatieve pin al is aangeraakt
      negativeTouch = true;
    }
  }

  // Checkt of de negatieve pin weer is losgelaten (- 10 als buffer)
  else if(readCapacitivePin(capSensePinNegative) < (minResistance - 20))
  {
    //Geeft aan dat de negatieve pin weer is losgelaten
    negativeTouch = false;
  }

  // Als niks wordt aangeraakt, is het stil.
  else
  {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

}


//-----EEN STUKJE CODE VAN HET INTERNET-----

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//          how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
//  In order for this to work now,
// The pin should have a 1+Megaohm resistor pulling
//  it up to +5v.
uint8_t readCapacitivePin(int pinToMeasure){
  // This is how you declare a variable which
  //  will hold the PORT, PIN, and DDR registers
  //  on an AVR
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  // Now see how long the pin to get pulled up
  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  
  return cycles;
}



