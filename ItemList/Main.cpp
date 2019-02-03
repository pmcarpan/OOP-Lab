#include <iostream>
#include <string>
using namespace std;

class Item {
private:
	int code, qty;
	string name;
	double rate;
public:
	Item() {
		code = -1; qty = -1; name = "", rate = -1;
	}
	void getData() {
		cout << "Enter code: "; cin >> code;
		cout << "Enter qty:  "; cin >> qty;
		cout << "Enter name: "; cin >> name;
		cout << "Enter rate: "; cin >> rate;
	}
	int getCode() { return code; }
	double getRate() { return rate; }
	int getQuantity() { return qty; }
	void dispItem() {
		cout << "Item{code=" << code << ", qty=" << qty << ", name=" << name <<
				", rate=" << rate << "}\n";
	}
	void setQuantity(int q) { qty = q; }
	void setName(string n) { name = n; }
	void setRate(double r) { rate = r; }
};

class ItemList {
public:
	static const int MAX_ITEMS = 10;
private:
	static Item itemList[MAX_ITEMS];
	static int currSize;
public:
	static void addItem() {
		if (currSize > MAX_ITEMS) {
			cout << "Item list is full, cannot add more items\n";
			return;
		}
		Item temp;
		cout << "Enter item details:\n";
		temp.getData();
		int idx = getIndexInList(temp.getCode());
		if (idx != -1) cout << "Failed to add, code already present\n";
		else itemList[currSize++] = temp;
	}
	static void updateItem() {
		int code, qty;
		string name;
		double rate;
		cout << "Enter item code for update: "; cin >> code;
		int idx = getIndexInList(code);
		if (idx == -1) { cout << "Code does not exist\n"; return; }
		cout << "Item being updated: "; itemList[idx].dispItem();
		cout << "Enter qty:  "; cin >> qty;
		cout << "Enter name: "; cin >> name;
		cout << "Enter rate: "; cin >> rate;
		itemList[idx].setQuantity(qty);
		itemList[idx].setName(name);
		itemList[idx].setRate(rate);
	}
	static int getIndexInList(int code) {
		for (int i = 0; i < currSize; i++)
			if (itemList[i].getCode() == code)
				return i;
		return -1;
	}
	static void dispItemList() {
		for (int i = 0; i < currSize; i++) {
			cout << "#" << i << ": ";
			itemList[i].dispItem();
		}
	}
	static Item getItem(int itemIdx) {
		return itemList[itemIdx];
	}
	static void reduceQuantity(int itemIdx, int amount) {
		itemList[itemIdx].setQuantity(itemList[itemIdx].getQuantity() - amount);
	}
};

Item ItemList::itemList[ItemList::MAX_ITEMS];
int ItemList::currSize = 0;

class OrderLine {
private:
	int code, qty;
public:
	OrderLine() { code = -1; qty = -1; }
	void getData() {
		cout << "Enter code: "; cin >> code;
		cout << "Enter qty:  "; cin >> qty;
	}
	int getCode() { return code; }
	int getQuantity() { return qty; }
	void displayOrderLine() {
		cout << "OrderLine{code=" << code << ", qty=" << qty << "}\n";
	}
};

class Order {
public:
	static const int MAX_ORDER = 10;
private:
	OrderLine order[MAX_ORDER];
	int currSize;
	double totPrice;
public:
	Order() { currSize = 0; totPrice = 0; }
	void takeOrder() {
		int exitFlag = 0;
		OrderLine tmp;
		do {
			cout << "Enter purchase item code and qty:\n"; tmp.getData();
			int itemListIdx = ItemList::getIndexInList(tmp.getCode()), 
				orderListIdx = getIndexInOrderList(tmp.getCode());
			if (itemListIdx == -1) { cout << "Invalid item code\n"; continue; }
			if (orderListIdx != -1) { cout << "Item already purchased\n"; continue; }

			Item i = ItemList::getItem(itemListIdx);
			if (i.getQuantity() < tmp.getQuantity()) {
				cout << "Not enough quantity available\n"; continue;
			}

			totPrice += i.getRate() * tmp.getQuantity();
			ItemList::reduceQuantity(itemListIdx, tmp.getQuantity());
			order[currSize++] = tmp;
			
			cout << "More items? 0 = No, other = Yes :"; cin >> exitFlag;
			cout << "Exit Flag is " << exitFlag << "\n";
		} while (currSize <= MAX_ORDER && exitFlag != 0);
	}
	int getIndexInOrderList(int code) {
		for (int i = 0; i < currSize; i++)
			if (order[i].getCode() == code)
				return i;
		return -1;
	}
	void displayOrder() {
		cout << "Items=" << currSize << ", Price=" << totPrice << "\n";
		for (int i =  0; i < currSize; i++) {
			cout << "#" << i << ": ";
			order[i].displayOrderLine();
		}
	}
};

class AdminInterface {
private:
	static const int passcode = 13599;
public:
	static void dispMenu() {
		cout << "\nChoice\tFunction\n" <<
            "1\tAdd Item\n" <<
            "2\tUpdate Item\n" <<
            "3\tDisplay\n" <<
            "4\tExit\n" << endl;
	}

	static void runAdmin() {
		int pass;
		cout << "Enter passcode: "; cin >> pass;
		if (pass != passcode) {
			cout << "Invalid passcode\n";
			return;
		}
		int chc;
		do {
			dispMenu();
			cout << "Enter choice: "; cin >> chc;
			if (chc == 1) {
				ItemList::addItem();
			}
			else if (chc == 2) {
				ItemList::updateItem();
			}
			else if (chc == 3) {
				ItemList::dispItemList();
			}
			else if (chc == 4) {
				cout << "Exiting\n";
			}
			else {
				cout << "Invalid Choice\n";
			}
		} while (chc != 4);
	}
};

class UserInterface {

};

class MasterInterface {

};

int main() {
	AdminInterface::runAdmin();
}
 