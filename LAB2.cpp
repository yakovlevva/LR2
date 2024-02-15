#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

class Integral {
public:
    using size_t = unsigned int;
    using value_t = float;
    using Iterator = value_t*;

    Integral(const std::vector<double>& val, const std::vector<double>& elem)
        : funcval(val), arrayelemNew(elem) {
        n = val.size() - 1; // Number of subintervals
        step = elem[n] - elem[0]; // Width of the interval
    }

    Integral(size_t s) : newsize(s) {
        if (s > maxs()) {
            throw std::range_error("invalid array size");
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
        std::cout << "input= argument ";

        for (int i = 0; i < arrayelemNew.size(); ++i)
            std::cout << arrayelemNew[i] << " ";

        std::cout << '\n';

        std::cout << "function ";

        for (int i = 0; i < funcval.size(); ++i)
            std::cout << funcval[i] << " ";

        std::cout << '\n';
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
    std::vector<double> funcval;

    std::vector<double> arrayelemNew;


    double helpfunc(double x) {
        return x * x;
    }

    const static size_t sizemax = 10000;

    size_t newsize;

    value_t* newdata;
};

std::string transform(double v) {

    double help = std::numeric_limits<double>::epsilon() * 1000.0;

    std::ostringstream oss;

    if (std::abs(v - round(v)) < help)
        oss << static_cast<int>(v);
    else
        oss << std::fixed << std::setprecision(1) << v;

    return oss.str();
}

int main() {
    int arrsize;

    std::cin >> arrsize;

    std::vector<double> elem(arrsize);
    std::vector<double> val(arrsize);

    
    for (int i = 0; i < arrsize; ++i)
        std::cin >> elem[i];

   
    for (int i = 0; i < arrsize; ++i)
        std::cin >> val[i];

    Integral findIntegral(val, elem);

    findIntegral.disp();

    std::cout << "lev priam= " << findIntegral.leftRectangle() << std::endl;
    std::cout << "sr priam= " << findIntegral.MiddleRectangle() << std::endl;
    std::cout << "prav priam= " << findIntegral.RightRectangle() << std::endl;
    std::cout << "trapeciy= " << findIntegral.Trapezia() << std::endl;
    std::cout << "Simpson= " << findIntegral.Simpson() << std::endl;
    std::cout << "Newton " << findIntegral.Newton() << std::endl;

    return 0;
}
