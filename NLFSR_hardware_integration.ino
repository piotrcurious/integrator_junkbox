#include <Arduino.h>

/**
 * NLFSR-based Integration
 *
 * This sketch demonstrates polynomial integration using principles inspired by
 * Non-Linear Feedback Shift Registers (NLFSRs). In a hardware context,
 * bitwise shifts and additions/XORs are used to efficiently compute
 * polynomial terms.
 *
 * To maintain accuracy without floating point, we use a common denominator
 * for the antiderivative:
 * F(x) = (12*a*x^5 + 15*b*x^4 + 20*c*x^3 + 30*d*x^2 + 60*e*x) / 60
 */

// Polynomial coefficients for f(x) = ax^4 + bx^3 + cx^2 + dx + e
int32_t a = 1;
int32_t b = 2;
int32_t c = 3;
int32_t d = 4;
int32_t e = 5;

// Integration bounds
int32_t x_start = 0;
int32_t x_end = 10;

// Function prototypes
int32_t multiplyNLFSR(int32_t value, int32_t multiplier);
int32_t evaluateScaledAntiderivative(int32_t x);
double integratePolynomialNLFSR(int32_t x_start, int32_t x_end);

void setup() {
  Serial.begin(115200);

  // Perform integration
  double result = integratePolynomialNLFSR(x_start, x_end);

  Serial.print("The integral of the polynomial from ");
  Serial.print(x_start);
  Serial.print(" to ");
  Serial.print(x_end);
  Serial.print(" is: ");
  Serial.println(result, 2);
}

void loop() {}

/**
 * Hardware-inspired multiplication using shifts and additions.
 * Mimics the accumulation logic in NLFSR/ALU designs.
 */
int32_t multiplyNLFSR(int32_t value, int32_t multiplier) {
  int32_t result = 0;
  bool negative = false;

  if (multiplier < 0) {
    multiplier = -multiplier;
    negative = !negative;
  }
  if (value < 0) {
    value = -value;
    negative = !negative;
  }

  uint32_t u_value = (uint32_t)value;
  uint32_t u_multiplier = (uint32_t)multiplier;
  uint32_t u_result = 0;

  while (u_multiplier > 0) {
    if (u_multiplier & 1) {
      u_result += u_value;
    }
    u_value <<= 1;
    u_multiplier >>= 1;
  }

  result = (int32_t)u_result;
  return negative ? -result : result;
}

/**
 * Power function using NLFSR-based multiplication
 */
int32_t powerNLFSR(int32_t base, int8_t exp) {
  int32_t res = 1;
  for (int8_t i = 0; i < exp; i++) {
    res = multiplyNLFSR(res, base);
  }
  return res;
}

/**
 * Evaluates 60 * F(x) using integer arithmetic.
 * 60 * F(x) = 12*a*x^5 + 15*b*x^4 + 20*c*x^3 + 30*d*x^2 + 60*e*x
 */
int32_t evaluateScaledAntiderivative(int32_t x) {
  int32_t term1 = multiplyNLFSR(12 * a, powerNLFSR(x, 5));
  int32_t term2 = multiplyNLFSR(15 * b, powerNLFSR(x, 4));
  int32_t term3 = multiplyNLFSR(20 * c, powerNLFSR(x, 3));
  int32_t term4 = multiplyNLFSR(30 * d, powerNLFSR(x, 2));
  int32_t term5 = multiplyNLFSR(60 * e, x);

  return term1 + term2 + term3 + term4 + term5;
}

/**
 * Computes the definite integral by evaluating the scaled antiderivative
 * at bounds and dividing by the common denominator.
 */
double integratePolynomialNLFSR(int32_t x_start, int32_t x_end) {
  int32_t F60_end = evaluateScaledAntiderivative(x_end);
  int32_t F60_start = evaluateScaledAntiderivative(x_start);

  return (double)(F60_end - F60_start) / 60.0;
}
