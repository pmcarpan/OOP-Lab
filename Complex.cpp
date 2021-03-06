#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Complex {
    private:
        double real_, img_;

    public:
    	Complex() {
    		real_ = 0;
    		img_ = 0;
    	}

    public:
    	Complex(double real) {
    		real_ = real;
    		img_ = 0;
    	}

	public:
    	Complex(double real, double img) {
    		real_ = real;
    		img_ = img;
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
            return add(other);
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
            return sub(other);
        }

    public:
        void disp() const {
            cout << "Complex num: " << real_ << " + i" << img_ << endl;
        }

    private:
    	bool parseInput(const string input) {
    		// cout << "parseInput input = " << input << endl;

    		string::size_type pos1, pos2; 

    		pos1 = input.find('+');
    		pos2 = input.find('+', pos1 + 1);
    		if (pos1 != string::npos && pos2 != string::npos) { cout << "1" << endl;
    			return false;
    		}
    		if (pos1 != string::npos) {
    			return parseInputWithPlusOrMinus(input, true);
    		}

    		pos1 = input.find('-');
    		if (pos1 == 0) pos1 = input.find('-', pos1 + 1);
    		pos2 = input.find('-', pos1 + 1);
    		if (pos1 != string::npos && pos2 != string::npos) { cout << "2" << endl;
    			return false;
    		}

    		pos2 = input.find('i');
    		if (pos2 != string::npos) {
    			if (pos1 == 0 || pos1 == string::npos) {
    				return parseInputWithImg(input);
    			}
	    		else {
	    			return parseInputWithPlusOrMinus(input, false);
	    		}
    		}
    		else {
    			return parseInputWithReal(input);
    		}
    	}

	private:
		bool parseInputWithPlusOrMinus(const string input, bool isPlus) {
			// cout << "parseInputWithPlusOrMinus" << endl;

			string::size_type pos1, pos2;
			string left, right;
			double real, img;

			pos1 = (isPlus) ? (input.find('+')) : (input.find('-'));
			if (pos1 == 0) pos1 = input.find('-', pos1 + 1);
			pos2 = input.find('i');

			if (pos2 == string::npos) return false;
			if (pos2 != pos1 + 2) return false;
			
			left = input.substr(0, pos1);
			right = input.substr(pos2 + 1);

			try {
				real = stod(left);
				img = stod(right);
			}
			catch (...) {
				return false;
			}


			real_ = real; 
			img_ = (isPlus) ? (img) : (-img);
			return true;
		}

	private:
		bool parseInputWithImg(const string input) { 
			// cout << "parseInputWithImg" << endl;
			
			string::size_type pos1, pos2;
			string left, right;
			double img;

			pos1 = input.find('-');
			pos2 = input.find('i');

			if (pos2 == string::npos) return false;
			if (pos1 != string::npos && pos2 != pos1 + 1 && pos2 != pos1 + 2) return false;
			
			right = input.substr(pos2 + 1);

			try {
				img = stod(right);
			}
			catch (...) {
				return false;
			}

			// cout << img << endl;
			real_ = 0; 
			img_ = (pos1 == string::npos) ? (img) : (-img);
			return true;
		}

	private:
		bool parseInputWithReal(const string input) {
			// cout << "parseInputWithReal" << endl;

			double real;

			try {
				real = stod(input);
			}
			catch (...) {
				return false;
			}

			real_ = real;
			img_ = 0;
			return true;
		}

        friend ostream& operator<<(ostream& output, const Complex& c) {
            output << "Complex num: " << c.real_;
            if (c.img_ >= 0) output << " + i" << c.img_;
            else			output << " - i" << -c.img_;
            return output;
        }

        friend istream& operator>>(istream& is, Complex& c) {
        	if (is.fail()) return is;

        	string input;
        	getline(is, input);

        	if (!c.parseInput(input)) {
        		is.setstate(ios::failbit);
        	}

        	return is;
        }
};

void dispMenu() {
    cout << "\nChoice\tFunction\n" <<
            "1\tAdd 2 complex numbers\n" <<
            "2\tSub 2 complex numbers\n" <<
            "3\tDisplay\n" <<
            "4\tExit" << endl;
}

int main() {
    int chc;
    string inp;
    Complex c1, c2;

    cout << "Enter complex number: ";
    cin >> c1;
    while (cin.fail()) {
    	cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cout << "Invalid input. Enter complex number: ";
    	cin >> c1;
    }
    cout << "Entered number:\n" << c1 << endl;

    do {
    	dispMenu();
    	cout << "Enter choice: "; 
    	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cin >> chc; 
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	
    	if (chc == 1) {
    		cout << "Enter another complex number: "; 
    		cin >> c2;
    		while (cin.fail()) {
	    		cin.clear();
	    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    		cout << "Invalid input. Enter complex number: ";
	    		cin >> c1;
    		}
    		c1 = c1 + c2;
    		cout << "Sum is " << c1 << endl;
     	}
    	else if (chc == 2) {
    		cout << "Enter another complex number: "; 
    		cin >> c2;
    		while (cin.fail()) {
	    		cin.clear();
	    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    		cout << "Invalid input. Enter complex number: ";
	    		cin >> c1;
    		}
    		c1 = c1 - c2;
    		cout << "Subtrahend is " << c1 << endl;
    	}
    	else if (chc == 3) {
    		cout << c1 << endl;
    	}
    	else if (chc == 4) {
    		cout << "Exiting" << endl;
    	}
    	else {
    		cout << "Invalid choice, enter again" << endl;
    	}
    } while (chc != 4);
}