int input = 2;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(input);
  int volumen = min(value/10, 100);

  // The C program will read this value to change the volume
  Serial.println(volumen); 
  delay(50); 
}

