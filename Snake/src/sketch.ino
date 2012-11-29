/*
 *  Copyright (C) 2012 Rafael Rendón Pablo <smart.rendon@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

const int DOWN  = 8;
const int LEFT  = 6;
const int UP    = 10;
const int RIGHT = 12;
const int CONTINUE = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(UP, INPUT);
  pinMode(RIGHT, INPUT);
  
  // Pullups
  digitalWrite(DOWN, HIGH);
  digitalWrite(LEFT, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(RIGHT, HIGH);

  pinMode(13, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) {
    digitalWrite(13, HIGH);
    delay(3000);
    digitalWrite(13, LOW);
    Serial.read();
  } else {
    if (digitalRead(DOWN) == LOW)
      Serial.println(DOWN);
    else if (digitalRead(LEFT) == LOW)
      Serial.println(LEFT);
    else if (digitalRead(UP) == LOW)
      Serial.println(UP);
    else if (digitalRead(RIGHT) == LOW)
      Serial.println(RIGHT);
    else
      Serial.println(CONTINUE);
    delay(40);
  }

}

