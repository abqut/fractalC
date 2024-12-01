#include "polynomial.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


float fastPow(float b, int p){
    if(p == 0){
        return 1;
    }
    div_t divRes = div(p, 2);

    float res = fastPow(b, divRes.quot);
    res *= res;
    if(divRes.rem) return b * res;
    return res;
}

void assignCoeff(float C[], Polynomial* P, int N) {
    assert(P->degree + 1 == N);
    P->coeff = malloc(N * sizeof(float));
    for (int i = 0; i < N; i++) {
        P->coeff[i] = C[i];
    }
}

Polynomial add(Polynomial p, Polynomial q) {
    Polynomial r;

    if (p.degree > q.degree) {
        r.degree = p.degree;
        r.coeff = malloc((p.degree + 1) * sizeof(float));
        for (int i = 0; i <= p.degree; i++) {
            if (i <= q.degree) {
                r.coeff[i] = q.coeff[i] + p.coeff[i];
            } else {
                r.coeff[i] = p.coeff[i];
            }
        }
    } else if (p.degree < q.degree) {
        r.coeff = malloc((q.degree + 1) * sizeof(float));
        r.degree = q.degree;
        for (int i = 0; i <= q.degree; i++) {
            if (i <= p.degree) {
                r.coeff[i] = q.coeff[i] + p.coeff[i];
            } else {
                r.coeff[i] = q.coeff[i];
            }
        }
    } else if (p.degree == q.degree) {
        r.degree = p.degree;
        r.coeff = malloc((r.degree + 1) * sizeof(float));
        for (int i = 0; i <= r.degree; i++) {
            r.coeff[i] = (q.coeff[i] + p.coeff[i]);
        }
    }

    return r;
}

float eval(Polynomial p, float x) {
    float res = p.coeff[0];
    for (int i = 1; i <= p.degree; i++) {
        res += fastPow(x, i) * p.coeff[i];
    }
    return res;
}

Polynomial smultiply(Polynomial p, float x) {
    Polynomial temp;
    temp.degree = p.degree;
    temp.coeff = malloc((p.degree + 1) * sizeof(float));
    for (int i = 0; i <= p.degree; i++) {
        temp.coeff[i] = (p.coeff[i]) * x;
    }

    return temp;
}

Polynomial multiply(Polynomial p, Polynomial q) {
    Polynomial res;
    res.degree = p.degree + q.degree;
    res.coeff = malloc((res.degree + 1) * sizeof(float));
    for (int i = 0; i <= res.degree + 1; i++) {
        float temp = 0;
        for (int j = 0; j <= i; j++) {
            if (j > p.degree || (i - j) > q.degree) {
                continue;
            } else {
                temp += p.coeff[j] * q.coeff[i - j];
            }
        }
        res.coeff[i] = temp;
    }
    return res;
}

Polynomial* monCubIn(float x[], float y[], int length) {
    float* sec = malloc((length - 1) * sizeof(float));
    float* tans = malloc((length) * sizeof(float));
    Polynomial h00, h10, h01, h11;
    Polynomial* res = malloc((length - 1) * sizeof(Polynomial));
    h00.degree = 3;
    h10.degree = 3;
    h01.degree = 3;
    h11.degree = 3;
    float c00[4] = {1, 0, -3, 2};
    float c10[4] = {0, 1, -2, 1};
    float c01[4] = {0, 0, 3, -2};
    float c11[4] = {0, 0, -1, 1};

    assignCoeff(c00, &h00, 4);
    assignCoeff(c01, &h01, 4);
    assignCoeff(c10, &h10, 4);
    assignCoeff(c11, &h11, 4);

    int i, j, k, l;
    for (i = 0; i < length - 1; i++) {
        sec[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }

    tans[0] = sec[0];
    tans[length - 1] = sec[length - 2];

    for (j = 1; j < length - 1; j++) {
        if (sec[j - 1] * sec[j] < 0) {
            tans[j] = 0;

        } else {
            tans[j] = (sec[j - 1] + sec[j]) / 2.0;
        }
    }
    for (l = 0; l < length - 1; l++) {
        if (sec[l] * sec[l] < 1E-12) {
            tans[l] = 0;
            tans[l + 1] = 0;
        }
    }
    float del;
    for (k = 0; k < length - 1; k++) {
        del = (x[k + 1] - x[k]);
        Polynomial p1 = smultiply(h11, (del * tans[k + 1]));

        Polynomial p2 = smultiply(h01, y[k + 1]);

        Polynomial p3 = smultiply(h10, (tans[k] * del));

        Polynomial p4 = smultiply(h00, y[k]);

        Polynomial p5 = add(p4, p3);

        Polynomial p6 = add(p5, p2);

        res[k] = add(p6, p1);
        free(p1.coeff);
        free(p2.coeff);
        free(p3.coeff);
        free(p4.coeff);
        free(p5.coeff);
        free(p6.coeff);
    }

    free(tans);
    free(sec);

    free(h00.coeff);
    free(h01.coeff);
    free(h10.coeff);
    free(h11.coeff);

    return res;
}

float evalSpline(Polynomial* Spline, float* xs, float x, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (xs[i] <= x && x < xs[i + 1]) {
            float t = (x - xs[i]) / (xs[i + 1] - xs[i]);
            return (eval(Spline[i], t));
        }
    }
    fprintf(stderr, "ERROR: Spline input out of bounds.");
    return -1;
}

void freePolyPtr(Polynomial* ptr) {
    if (ptr->coeff) {
        free(ptr->coeff);
    }
    free(ptr);
}



void freeSpline(Polynomial* Spline, int N) {
    for (int i = 0; i < N; i++) {
        free(Spline[i].coeff);
    }
    free(Spline);
}