
/* ==================== DEFINE PINS ==================== */
#define INTERRUPT_PIN_MOTOR_A 2
#define INTERRUPT_PIN_MOTOR_B 3
//Define PIN L298n
#define ENA 22
#define ENB 24
#define IN4 7
#define IN3 6
#define IN2 5
#define IN1 4

/* =================== Configuration =================== */

// Serial
#define MYSERIAL Serial
#define BAUDRATE 9600

// Math (CONFIGURE YOUR OWN MOTOR CHARACTERISTICS)
#define COUNTS_PER_REVOLUTION 340 // PPR (pulses per revolution) or Counts/rpm
#define MIN2MICROSECONDS 60E6 // 1 min = 60.000.000 microseconds
