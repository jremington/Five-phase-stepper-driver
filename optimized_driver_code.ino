//indexing tables optimized, half step mode selected
// five phase drive for Vexta PX33M-A-C6 0.21A, 33R per phase, 0.36 degrees/step
// S. J. Remington 10/2020

// 3x Pololu DRV8835 dual motor driver
// **IN/IN mode selected**
// Truth Table
// IN1 IN2 OUT1 OUT2
// 0   0   open open
// 1   0   H    L
// 0   1   L    H

// Vexta PK PX, wire colors -> APPARENT phase and coil polarity assignments
//A - blue > red        (start > finish)
//B - yellow > white
//C - brown > purple
//D - gray > black
//E - orange > green

// drive sequences from 10_wire_sequence.png
// half step (2000 steps/rev). Set index_max=20, skip=8
//                     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
  int coil_drive[20] = { 1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
  int index_max = 20;
  int skip = 8;

/*
// full step (1000 steps/revolution), set index_max=10, skip=4
int coil_drive[10] = {  0, -1, -1, -1, -1, 0, 1, 1, 1, 1};
int index_max = 10;
int skip = 4;
*/

//
// pin assignment table: coil, {start,finish}
//                       A       B       C       D       E
int pin_table [5][2] = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {11, 12}};
int index = 0;

void setup() {
  int i;
  for (i = 0; i < 10; i++) pinMode(pin_table[i], OUTPUT);  //motor control pins
}

void loop() {

  int k, permuted_indices[5];

  //execute 2000 steps at full speed, from dead stop
  for (int i = 0; i < 2000; i++) {
    permuted_indices[0] = index;
    permuted_indices[1] = (permuted_indices[0] + skip) % index_max;
    permuted_indices[2] = (permuted_indices[1] + skip) % index_max;
    permuted_indices[3] = (permuted_indices[2] + skip) % index_max;
    permuted_indices[4] = (permuted_indices[3] + skip) % index_max;
    for (int j = 0; j < 5; j++) { //loop over coils
      k = permuted_indices[j];
      if (coil_drive[k] > 0) {
        digitalWrite(pin_table[j][0], 1); // plus
        digitalWrite(pin_table[j][1], 0);
      }
      if (coil_drive[k] == 0) {
        digitalWrite(pin_table[j][0], 0); // off
        digitalWrite(pin_table[j][1], 0);
      }
      if (coil_drive[k] < 0) {
        digitalWrite(pin_table[j][0], 0); // minus
        digitalWrite(pin_table[j][1], 1);
      }
    } // end for j
    delay(2); //500 steps/second OK
    index++;  //forward
//    index--;  //reverse
    if (index >= index_max) index = 0;
    if (index < 0 )index = index_max - 1;
  }
  delay(500); //pause after one revolution for skipped step test.
}
