#define ARRAY_SIZE 100
#define VOLTAGE_THRESHOLD 1
#define DELAY_TIME 150

#define LED 12

int voltages[ARRAY_SIZE];
int averages[ARRAY_SIZE];
int final_averages[ARRAY_SIZE];

boolean placed = false;

int voltage_index = 0;
int average_index = 0;
int final_index = 0;

void loop();
/* WHAT:
 * Controls an LED based on the LCD backlight of a Philips DC390.
 * 
 * BASICS:
 * The backlight is toggled by pushbuttons above the LCD. I was unable
 * to determine how to interface with the pushbuttons, and instead
 * used the average voltage.
 *
 * WHY:
 * The LCD backlight is supplied by 5V DC PWM or 3V AC. This means the voltage
 * supplied alternates between either 0V and +5V, or +3V and -3V. Since I'm
 * not sure what the duty time is, to find out what state the backlight is
 * in, 100 voltage readings are taken, then averaged and stored in an array
 * of 100 averaged voltage readings. When the averaged voltage readings array
 * is full, the average is taken, and which is in turn stored in one more array
 * of 20 averaged readings. Theoretically it is now a very close average.
*/

void setup() {
  pinMode(LED, OUTPUT);  
  pinMode(A0, INPUT);
  
  Serial.begin(9600);
}



/* Finds average of array given */
int getArrayAverage(int array[]) {
  unsigned long sum = 0;
  for (int i=0; i < ARRAY_SIZE; i++) {
    sum += array[i];
  }
  return sum / (ARRAY_SIZE);
}

/* Controls light if average voltage is below defined threshold */
boolean controlLight(int average) {
  Serial.println(average);
  if (average < VOLTAGE_THRESHOLD) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

void loop() {
  int voltage = analogRead(A0);
  
  voltages[voltage_index] = voltage;
  
  /* If array is full, compute average of array */
  if (voltage_index == ARRAY_SIZE-1) {
    /* Adds voltage average to array of voltage averages */
    averages[average_index] = getArrayAverage(voltages);
    voltage_index = 0;
    
    /* If array of voltage averages is full, compute average */
    if (average_index == ARRAY_SIZE-1) {
      final_averages[final_index] = getArrayAverage(averages);
      average_index = 0;
      
      if (final_index = ARRAY_SIZE) {
        int final_average = getArrayAverage(final_averages);
        final_index = 0;
        
        controlLight(final_average);
      }
      else {
        final_index++;
      }
    }
    else {
      average_index++;    
    }
  }
  else {
   voltage_index++;
  }
}
