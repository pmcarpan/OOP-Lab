#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Complex {
    private:
        double real_ = 0, img_ = 0;

    public:
        bool takeInput() {
            cin >> real_ >> img_;
            return cin.fail();
        }

    public:
        Complex add(const Complex& other) const {
            Complex sum;
            sum.real_ = real_ + other.real_;
            sum.img_ = img_ + other.img_;
            return sum;
        }

    public:
        Complex operator+(const Complex& other) const {
            return this->add(other);
        }

    public:
        Complex sub(const Complex& other) const {
            Complex subtr;
            subtr.real_ = real_ - other.real_;
            subtr.img_ = img_ - other.img_;
            return subtr;
        }

    public:
        Complex operator-(const Complex& other) const {
            return this->sub(other);
        }

    public:
        void disp() const {
            cout << "Complex num: " << real_ << " + i" << img_;
        }

    private:
        friend ostream & operator<<(ostream &output, const Complex &c) {
            output << "Complex num: " << c.real_ << " + i" << c.img_;
            return output;
        }

};

void dispMenu() {
    cout << "\nChoice\tFunction\n" <<
            "1\tInput\n" <<
            "2\tDisplay in 12 h format\n" <<
            "3\tDisplay in 24 h format\n" <<
            "4\tAdd minutes\n" <<
            "5\tCompare with system time\n" <<
            "6\tExit" << endl;
}

int main() {
    Complex c1, c2, c3;
    c1.takeInput(); c2.takeInput();
    c1.disp(); c2.disp();

    c3 = c1 + c2;
    cout << c3 << endl;
    c3 = c1 - c2;
    cout << c3 << endl;
}