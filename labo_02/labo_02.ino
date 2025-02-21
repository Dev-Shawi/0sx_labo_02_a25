
const int potPin = A1;       
const int buttonPin = 2;     
const int leds[] = {8, 9, 10, 11}; 


int potValue = 0;            
int mappedValue = 0;        
bool buttonPressed = false; 
unsigned long lastDebounceTime = 0; // Dernier temps de détection du bouton
const unsigned long debounceDelay = 200; // Délai d'anti-rebond


const char progressChar = '#'; 

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) 
  {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600); 
}

void loop() {
  // Lecture du potentiomètre
  potValue = analogRead(potPin);
  mappedValue = map(potValue, 0, 1023, 0, 20);


  if (digitalRead(buttonPin) == HIGH) 
  {
    if (millis() - lastDebounceTime > debounceDelay) 
    {
      buttonPressed = true;
      lastDebounceTime = millis(); // Mettre à jour le temps de détection
    }
  }

 
  if (buttonPressed) {
    displayProgressBar(mappedValue);
    buttonPressed = false; 
  }

  // Contrôle des DELs
  controlLeds(mappedValue);
}


void displayProgressBar(int value) 
{
  int percentage = value * 5; 
  Serial.print(percentage);
  Serial.print("% ");


  Serial.print("[");
  for (int i = 0; i < 20; i++) {
    if (i < value) {
      Serial.print(progressChar);
    } else {
      Serial.print(".");
    }
  }
  Serial.println("]");
}


void controlLeds(int value) {
  int numLeds = 0;

 
  switch (value) {
    case 0 ... 5:   
      numLeds = 1;
      break;
    case 6 ... 10:  
      numLeds = 2;
      break;
    case 11 ... 15: 
      numLeds = 3;
      break;
    case 16 ... 20: 
      numLeds = 4;
      break;
  }

  // Allumer les DELs
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(leds[i], i < numLeds ? HIGH : LOW);
  }
}
