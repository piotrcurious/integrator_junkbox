// Coefficients of the polynomial f(x) = ax^4 + bx^3 + cx^2 + dx + e
double a = 1.0;  // Coefficient of x^4
double b = 2.0;  // Coefficient of x^3
double c = 3.0;  // Coefficient of x^2
double d = 4.0;  // Coefficient of x
double e = 5.0;  // Constant term

// Integration limits
double x_start = 0.0; // Lower limit of integration
double x_end = 10.0;  // Upper limit of integration

// Function prototypes
double polynomialAntiderivative(double x);
double symbolicIntegration(double x_start, double x_end);

void setup() {
  Serial.begin(115200);

  // Perform symbolic integration
  double result = symbolicIntegration(x_start, x_end);
  
  // Print the result
  Serial.print("The integral of the polynomial from ");
  Serial.print(x_start);
  Serial.print(" to ");
  Serial.print(x_end);
  Serial.print(" is: ");
  Serial.println(result, 6); // Print result with 6 decimal places
}

void loop() {
  // Nothing to do here
}

// Function to calculate the antiderivative of the polynomial: F(x) = (a/5)*x^5 + (b/4)*x^4 + (c/3)*x^3 + (d/2)*x^2 + e*x
// Optimized using a variation of Horner's Method for antiderivatives
double polynomialAntiderivative(double x) {
  return ((((a / 5.0 * x + b / 4.0) * x + c / 3.0) * x + d / 2.0) * x + e) * x;
}

// Function to perform symbolic integration using the exact antiderivative of the polynomial
double symbolicIntegration(double x_start, double x_end) {
  // Evaluate the antiderivative at the limits
  double F_x_start = polynomialAntiderivative(x_start);
  double F_x_end = polynomialAntiderivative(x_end);
  
  // Calculate the definite integral
  return F_x_end - F_x_start;
}
