#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#define fmt2w setfill('0') << setw(2) // pad with zeros, width 2 chars

class Time {
    private:
        int h_ = 0, m_ = 0, s_ = 0;

    public:
        bool takeInput() {
            string timeStr;
            cout << "Time formats - HH:MM:SS / HH:MM:SSAM / HH:MM:SSPM" << endl;
            cout << "Enter time: ";
            cin >> timeStr;

            if (!isValidtimeStr(timeStr)) {
                cout << "Input time format invalid" << endl;
                return false;
            }

            int len = timeStr.length();
            int pos1 = timeStr.find(":");
            int pos2 = timeStr.find(":", pos1 + 1);
            int pos3 = (len == 8) ? (len) : (len - 2);

            h_ = stoi( timeStr.substr(0, pos1) );
            m_ = stoi( timeStr.substr(pos1 + 1, pos2) );
            s_ = stoi( timeStr.substr(pos2 + 1, pos3) );

            if (!isValidTime()) {
                cout << "Input time value(s) invalid" << endl;
                return false;
            }

            if (len == 10) {
                if (timeStr[len - 2] == 'P') {
                    h_ = (h_ == 12) ? (h_) : (h_ + 12);
                }
                else {
                    h_ = (h_ == 12) ? (0) : (h_);
                }
            }

            return true;
        }

    private:
        bool isValidtimeStr(string timeStr) {
            int len = timeStr.length();
            if (len != 8 && len != 10)
                return false;
            
            if (!isdigit(timeStr[0]) || !isdigit(timeStr[1]) || timeStr[2] != ':' || 
                !isdigit(timeStr[3]) || !isdigit(timeStr[4]) || timeStr[5] != ':' || 
                !isdigit(timeStr[6]) || !isdigit(timeStr[7]))
                return false;
            
            if (len == 10)
                if ( (timeStr[8] != 'A' && timeStr[8] != 'P') || timeStr[9] != 'M' )
                    return false;
            
            return true;
        }

    private:
        bool isValidTime() {
            if (h_ < 0 || h_ > 24 || m_ < 0 || m_ > 59 || s_ < 0 || s_ > 59)
                return false;
            return true;
        }

    public:
        void disp24HourFormat() {
            cout << "24 h format: ";
            cout << fmt2w << h_ << ":" << fmt2w << m_ << ":" << fmt2w << s_ <<
                endl;
        }

    public:
        void disp12HourFormat() {
            int hNormal;
            cout << "12 h format: ";
            if (h_ >= 12) {
                hNormal = (h_ != 12) ? (h_ - 12) : (h_);
                cout << fmt2w << hNormal << ":" << fmt2w << m_ << ":" << fmt2w << 
                    s_ << "PM" << endl;
            }
            else {
                hNormal = (h_ == 0) ? (12) : (h_);
                cout << fmt2w << hNormal << ":" << fmt2w << m_ << ":" << fmt2w << 
                    s_ << "AM" << endl;
            }
        }

    public:
        void addMinutes(int mins) {
            m_ += mins;
            h_ += m_ / 60;
            m_ %= 60;
            if (m_ < 0) {
                m_ += 60;
                h_--;
            }
            h_ %= 24;
            if (h_ < 0) h_ += 24;
        }

    public:
        void compareWithSystemTime() {
            int hSys, mSys, sSys, totSec, totSecSys;
            
            time_t t = time(0); // time Sys
            tm *now = localtime(&t); // time_t to tm*
            
            // extract system time components
            hSys = now->tm_hour; mSys = now->tm_min; sSys = now->tm_sec;
            
            totSec = h_ * 3600 + m_ * 60 + s_;
            totSecSys = hSys * 3600 + mSys * 60 + sSys;
            
            compareTimeInSeconds(totSecSys, totSec);
        }

    private:
        void compareTimeInSeconds(int sys, int t) {
            if (sys == t) {
                cout << "System time and current time are same." << endl;
            }
            else {
                int diff = sys - t;
                if (diff < 0) {
                    cout << "System time is lagging by ";
                    diff = -diff;
                }
                else {
                    cout << "System time is leading by ";
                }
                cout << (diff / 3600) << " hrs " << ((diff / 60) % 60) << " mins " <<
                        (diff % 60) << " secs" << endl;
            }
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
    int chc;
    Time t1;

    cout << "Current time is" << endl;
    t1.disp24HourFormat();
    
    do {
        dispMenu();
        cout << "Enter choice: ";
        cin >> chc;

        if (chc == 1) {
            while (!t1.takeInput()) {
                cout << "Input again" << endl;
            }
        }
        else if (chc == 2) {
            t1.disp12HourFormat();
        }
        else if (chc == 3) {
            t1.disp24HourFormat();
        }
        else if (chc == 4) {
            int minsToAdd;
            cout << "Enter minutes: "; cin >> minsToAdd;
            t1.addMinutes(minsToAdd);
        }
        else if (chc == 5) {
            t1.compareWithSystemTime();
        }
        else if (chc == 6) {
            cout << "Exiting." << endl;
        }
        else {
            cout << "Invalid choice, enter again." << endl;
        }

    } while (chc != 6);
}