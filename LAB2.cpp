#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class Integral {
public:
    using size_t = unsigned int;
    using value_t = float;
    using Iterator = value_t*;

    Integral(const vector<double>& val, const vector<double>& elem)
        : funcval(val), arrayelemNew(elem) {
        n = val.size() - 1; // Number of subintervals
        step = elem[n] - elem[0]; // Width of the interval
    }

    Integral(size_t s) : newsize(s) {
        if (s > maxs()) {
            throw range_error("invalid array size");
        }
        newdata = new value_t[s];
    }

    Integral(size_t size, value_t default_value) : Integral(size) {
        for (auto& element : *this) {
            element = default_value;
        }
    }

    double leftRectangle() {
        double integral = 0;

        for (int i = 0; i < n; ++i)
            integral += funcval[i] * (arrayelemNew[i + 1] - arrayelemNew[i]);

        return integral;
    }

    double MiddleRectangle() {
        double integral = 0;

        for (int i = 0; i < n; ++i) {
            double help = (funcval[i] + funcval[i + 1]) / 2.0;

            integral += help * (arrayelemNew[i + 1] - arrayelemNew[i]);
        }

        return integral;
    }

    double RightRectangle() {
        double integral = 0;

        for (int i = 0; i < n; ++i)
            integral += funcval[i + 1] * (arrayelemNew[i + 1] - arrayelemNew[i]);

        return integral;
    }

    double Trapezia() {
        double integral = 0;

        for (int i = 0; i < n; ++i)
            integral += (funcval[i] + funcval[i + 1]) * (arrayelemNew[i + 1] - arrayelemNew[i]) / 2;
        return integral;
    }

    double Simpson() {
        double integral = 0;

        for (int i = 0; i < n; i += 2) {
            double step = arrayelemNew[i + 2] - arrayelemNew[i];

            integral += (funcval[i] + 4 * funcval[i + 1] + funcval[i + 2]) * step / 6;
        }
        return integral;
    }

    double Newton() {
        double integral = 0;

        if (n % 3 == 0) {
            for (int i = 0; i < n; i += 3)
                integral += (funcval[i] + 3 * funcval[i + 1] + 3 * funcval[i + 2] + funcval[i + 3]) *
                            (arrayelemNew[i + 3] - arrayelemNew[i]) / 8;
        }
        return integral;
    }

    void disp() {
        cout << "input= argument ";

        for (int i = 0; i < arrayelemNew.size(); ++i)
            cout << arrayelemNew[i] << " ";

        cout << '\n';

        cout << "function ";

        for (int i = 0; i < funcval.size(); ++i)
            cout << funcval[i] << " ";

        cout << '\n';
    }

    size_t getsize() const {
        return newsize;
    }
    static size_t maxs() {
        return sizemax;
    }

    const Iterator begin() const {
        newdata;
    }
    const Iterator end() const {
        return newdata + newsize;
    }


private:
    double step;

    int n;
    vector<double> funcval;

    vector<double> arrayelemNew;


    double helpfunc(double x) {
        return x * x;
    }

    const static size_t sizemax = 10000;

    size_t newsize;

    value_t* newdata;
};

string transform(double v) {

    double help = numeric_limits<double>::epsilon() * 1000.0;

    ostringstream oss;

    if (abs(v - round(v)) < help)
        oss << static_cast<int>(v);
    else
        oss << fixed << setprecision(1) << v;

    return oss.str();
}

int main() {
    int arrsize;

    cin >> arrsize;

    vector<double> elem(arrsize);
    vector<double> val(arrsize);

    
    for (int i = 0; i < arrsize; ++i)
        cin >> elem[i];

   
    for (int i = 0; i < arrsize; ++i)
        cin >> val[i];

    Integral findIntegral(val, elem);

    findIntegral.disp();

    cout << "lev priam= " << findIntegral.leftRectangle() << endl;
    cout << "sr priam= " << findIntegral.MiddleRectangle() << endl;
    cout << "prav priam= " << findIntegral.RightRectangle() << endl;
    cout << "trapeciy= " << findIntegral.Trapezia() << endl;
    cout << "Simpson= " << findIntegral.Simpson() << endl;
    cout << "Newton " << findIntegral.Newton() << endl;

    return 0;
}
