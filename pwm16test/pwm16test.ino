void setupPWM16() {
    DDRB |= _BV(PB1) | _BV(PB2);        /* set pins as outputs */
    TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
    TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS10);                    /* no prescaling */
    ICR1 = 0xffff;                      /* TOP counter value */
}

void analogWrite16(uint8_t pin, uint16_t val)
{
    switch (pin) {
        case  9: OCR1A = val; break;
        case 10: OCR1B = val; break;
    }
}


void setup() {
  
   setupPWM16();
   Serial.begin(9600);
   
}

void loop() {
   static uint16_t i;

   while (Serial.available() > 0) {
   i = Serial.parseInt();
   if (Serial.read() == '\n') {
      i = constrain(i, 0, 65535);
      analogWrite16(9, i);
      analogWrite16(10, i);
      Serial.print("Set PWM Value to ");
      Serial.println(i, DEC);
   }
   
   }
}
