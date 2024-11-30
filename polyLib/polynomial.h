//TODO
//float --> double

typedef struct{
    float *coeff;
    int degree;
} Polynomial;


float powi(float b, int p);

float fastPow(float b, int p);

void assignCoeff(float C[], Polynomial *P, int N);

Polynomial add(Polynomial p, Polynomial q);

float eval(Polynomial p, float x);

Polynomial smultiply(Polynomial p, float x);

Polynomial multiply(Polynomial p, Polynomial q);

Polynomial* monCubIn(float x[], float y[], int length);

float evalSpline(Polynomial *Spline, float *xs, float x, int length);

void freePolyPtr(Polynomial* ptr);

void freeSpline(Polynomial *Spline, int N);