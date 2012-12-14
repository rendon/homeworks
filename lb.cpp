//  Lin-Bairstow method
//  This method is used to find roots of polynomials and the theory
//  f(x) = a[0] + a[1] * x + a[2] * x^2 + ... + a[n] * x^n
//       = (x^2 - u * x - v)(b[2] + b[3] * x + b[3] * x^2 + 
//         ... + b[n-2] * x^(n-2)) + b[1](x - u) + b[0]
//       = (b[0] - u * b[1] - v * b[2]) + x(b[1] - u * b[2] - v * b[3]) +
//         x^2(b[2] - u * b[3] - v * b[4]) + ... + x^(n-1)(b[n-1] - u * b[n]) +
//         x^n * b[n]
//
//  Generalizing:
//  c[n] = b[n] = a[n]
//  b[n-1] = a[n-1] + u * b[n]
//  c[n-1] = b[n-1] + u * c[n]
//
//  b[i] = a[i] + u * b[i+1] + v * b[i+2]     i = n - 2, n - 1, ..., 1
//  c[i] = b[i] + u * c[i+1] + v * c[i+2]
//
//  b[0] = a[0] + u * b[1] + v * b[2]
//
//  u and v are unknown, so we need to use an approximate value
//  and iterate till we get an acceptable accuracy.
//
//  u[i+1] = u[i] + (b[0] * c[3] - b[1] * c[2]) / (c[2]^2 - c[1] * c[3])
//  v[i+1] = v[i] + (b[1] * c[1] - b[0] * c[2]) / (c[2]^2 - c[1] * c[3])
//
//      u ± sqrt(u^2 + 4v)
//  x = -------------------
//              2
//
//  Source: http://faculty.cbu.ca/dkeefe/chem302/Chapter%201_WS_part3.pdf

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
  double epsilon = 1e-8, *a, *b, *c, u, v;
  double du, dv, dr, r1, r2, error, det, sq;
  int n, i;

  cout << "Enter order of polynomial: ";
  cin >> n;
  a = new double[n + 1];
  b = new double[n + 1];
  c = new double[n + 1];

  for (i = 0; i < n + 1; i++) {
    cin >> a[i];
  }


  cout << "\n\nRoots of the polynomial are:\n";

  while (a[n] == 0) {
    n--;
  }

  // make sure n>3
  while (n > 3) {
    u = 0;
    v = 0;
    error = 1;
    c[n] = b[n] = a[n];

    while (error > epsilon) {
      b[n - 1] = a[n - 1] + u * b[n];
      c[n - 1] = b[n - 1] + u * c[n];

      for (i = n - 2; i > 0; i--) {
        b[i] = a[i] + u * b[i + 1] + v * b[i + 2];
        c[i] = b[i] + u * c[i + 1] + v * c[i + 2];
      }

      b[0] = a[0] + u * b[1] + v * b[2];
      det = c[2] * c[2] - c[1] * c[3];

      if (det == 0) {
        du = dv = 1;
      } else {
        du = (b[0] * c[3] - b[1] * c[2]) / det;
        dv = (c[1] * b[1] - c[2] * b[0]) / det;
      }

      u += du;
      v += dv;
      error = sqrt(du * du + dv * dv);
    }

    sq = u * u + 4 * v;

    if (sq < 0) { //complex roots
      r1 = u / 2;
      r2 = sqrt(-sq) / 2;
      cout << r1 << " + " << r2 << "i" << endl;
      cout << r1 << " - " << r2 << "i" << endl;
    } else { // real roots
      r1 = u / 2 + sqrt(sq) / 2;
      r2 = u / 2 - sqrt(sq) / 2;
      cout << r1 << endl;
      cout << r2 << endl;
    }

    n -= 2;

    for (i = 0; i < n + 1; i++)
      a[i] = b[i + 2];
  }


  // When n = 3 we need to implement Horner's method to reduce the degree
  // by one. Horner's method uses the Newton-Raphson method to find r.
  //
  // f(x) = a[0] + a[1] * x + a[2] * x^2 + ... + a[n] * x^n
  //      = (x - r)(b[1] + b[2] * x + ... + b[n] * x^(n-1)) + b[0]
  //      = b[0] - r * b[1] + x(b[1] - r*b[2]) + x^2(b[2] - r * b[3]) + 
  //         ... + x^(n-1)(b[n-1] - r * b[n]) + b[n] * x^n
  //
  //    Generalizing:
  //    b[n] = a[n]
  //    b[i] = a[i] + r * b[i+1]   for i = n - 1, n - 2, ..., 1, 0
  //
  //    b[0] = f(r)
  //
  //    When n = 3:
  //      b[3] = a[3]
  //      b[2] = a[2] + r * b[3]
  //      b[1] = a[1] + r * b[2]
  //      b[0] = a[0] + r * b[1]
  //
  //  Source: http://faculty.cbu.ca/dkeefe/chem302/Chapter%201_WS_part2.pdf
  
  if (n == 3) {
    double r = 0;
    b[n] = a[n];
    error = 1;

    while (error > epsilon) {
      b[2] = a[2] + r * b[3];
      b[1] = a[1] + r * b[2];
      b[0] = a[0] + r * b[1];

      // f(x) = a[0] + a[1] * x + a[2] * x^2 + a[3] * x^3
      // f'(x) = a[1]  +  2 * a[2] * x  +   3 * a[3] * x^2
      double d = a[1] + (2 * a[2] * r) + (3 * a[3] * r * r);

      // This should be abs(d) < eps
      if (d == 0) // When u = 0 and a[1] = 0
        dr = 1;
      else
        dr = -b[0] / d;

      r += dr;
      error = sqrt(dr * dr);
    }

    cout << r << endl;
    n--;

    for (i = 0; i < n + 1; i++)
      a[i] = b[i + 1];
  }

  if (n == 2) {
    u = -a[1] / a[2];
    v = -a[0] / a[2];
    sq = u * u + 4 * v;

    if (sq < 0) { //complex roots
      r1 = u / 2;
      r2 = sqrt(-sq) / 2;
      cout << r1 << " + " << r2 << "i" << endl;
      cout << r1 << " - " << r2 << "i" << endl;
    } else {
      r1 = u / 2 + sqrt(sq) / 2;
      r2 = u / 2 - sqrt(sq) / 2;
      cout << r1 << endl;
      cout << r2 << endl;
    }
  } else if (n == 1) {
    r1 = -a[0] / a[1];
    cout << r1 << endl;
  }

  delete[] a;
  delete[] b;
  delete[] c;
  cout << "\n\nFinished finding roots." << endl;
  return EXIT_SUCCESS;
}



