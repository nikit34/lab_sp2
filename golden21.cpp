#include <iostream>
#include "mlisp.h"

double fun (double x);
double golden__section__search (double a, double b);
double golden__start (double a, double b);
double __pna__try (double a, double b, double xa, double ya, double xb, double yb);
bool close__enough_Q (double x, double y);
extern double mphi;
extern double tolerance;
extern double total__iterations;
extern double xmin;

double a = 2.;
double b = 6.;
double fun (double x) {
    x = x - 24. / 25.;
    return x + sin(x) + cos(x);
}
double golden__section__search (double a, double b) {
    {
        double
            xmin(a < b ? golden__start(a, b) : golden__start(b, a));
        newline();
        return xmin;
    }
}
double golden__start (double a, double b) {
    total__iterations = 0.;
    {
        double
            xa(a + mphi * (b - a)),
            xb(b + ( - mphi * (b - a)));
        return __pna__try(a, b, xa, fun(xa), xb, fun(xb));
    }
}
double mphi = (3. - sqrt(5.)) * (1. / 2.);
double __pna__try (double a, double b, double xa, double ya, double xb, double yb) {
    return (close__enough_Q(a,b) ? (
        (a + b) * 0.5) : (
            (display("+"), total__iterations++, ( ya < yb ? (
                        b = xb,
                        xb = xa,
                        yb = ya,
                        xa = a + mphi * (b - a),
                        __pna__try(a, b, xa, fun(xa), xb, yb)
                    ) : (
                        a = xa,
                        xa = xb,
                        ya = yb,
                        xb = b + ( - (mphi * (b - a))),
                        __pna__try(a, b, xa, ya, xb, fun(xb))
                    )
                )
            )
        )
    );
}
bool close__enough_Q (double x, double y) {
    return (abs(x - y) < tolerance);
}
double tolerance = 0.001;
double total__iterations = 0.;
double xmin = 0.;
int main() {
    xmin = golden__section__search(a, b);
    display("interval=\t[");
    display(a);
    display(" , ");
    display(b);
    display("]\n");
    display("Total number of iteranions=");
    display(total__iterations);
    display("\n");
    display("xmin=\t\t");
    display(xmin);
    display("\n");
    display("f(xmin)=\t");
    display(fun(xmin));
    newline();
    return 0;
}