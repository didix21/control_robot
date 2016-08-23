
/* ==================== DEFINE PINS ==================== */
#define INTERRUPT_PIN_MOTOR_A 3
#define INTERRUPT_PIN_MOTOR_B 2
//Define PIN L298n
#define ENA 5
#define ENB 6
#define IN4 10
#define IN3 9
#define IN2 7
#define IN1 8

/* =================== Configuration =================== */

// Serial
#define MYSERIAL Serial
#define BAUDRATE 9600

// Math (CONFIGURE YOUR OWN MOTOR CHARACTERISTICS)
#define COUNTS_PER_REVOLUTION 340 // PPR (pulses per revolution) or Counts/rpm
#define MIN2MICROSECONDS 60E6 // 1 min = 60.000.000 microseconds
