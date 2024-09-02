// Coefficients of the polynomial f(x) = ax^4 + bx^3 + cx^2 + dx + e
double a = 1.0;  // Coefficient of x^4
double b = 2.0;  // Coefficient of x^3
double c = 3.0;  // Coefficient of x^2
double d = 4.0;  // Coefficient of x
double e = 5.0;  // Constant term

// Integration limits
double x_start = 0.0; // Lower limit of integration
double x_end = 10.0;  // Upper limit of integration
int num_intervals = 1000; // Number of intervals for numerical integration

// Function prototype
double polynomial(double x);
double trapezoidalIntegration(double x_start, double x_end, int num_intervals);

void setup() {
  Serial.begin(115200);
  
  // Perform integration
  double result = trapezoidalIntegration(x_start, x_end, num_intervals);
  
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

// Function to define the polynomial f(x) = ax^4 + bx^3 + cx^2 + dx + e
double polynomial(double x) {
  return a * pow(x, 4) + b * pow(x, 3) + c * pow(x, 2) + d * x + e;
}

// Function to perform numerical integration using the Trapezoidal Rule
double trapezoidalIntegration(double x_start, double x_end, int num_intervals) {
  double h = (x_end - x_start) / num_intervals; // Step size
  double integral = 0.0;

  // Calculate the sum of first and last terms
  integral += polynomial(x_start) / 2.0;
  integral += polynomial(x_end) / 2.0;

  // Sum up the middle terms
  for (int i = 1; i < num_intervals; i++) {
    double x = x_start + i * h;
    integral += polynomial(x);
  }

  // Multiply by step size to get the final integral value
  integral *= h;

  return integral;
}
