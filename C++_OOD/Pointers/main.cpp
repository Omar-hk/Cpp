#include<iostream>
#include<limits>
using namespace std;

void swap(int *a, int *b){
    if(a == nullptr || b == nullptr) return; // check for null pointers, fixed after second review
    int temp = *a;
    *a = *b;
    *b = temp;
}

int sum(const int *arr, int size){ // using pointer arithmetic
    int total = 0;
    for(int i = 0; i < size; i++){
        total += *(arr+i); // arr is a pointer pointing at the start of the array, so we can use pointer arithmetic to access the elements
    }
    return total;
}

int* largest_value(int *arr, int size){
    if (arr == nullptr || size <= 0) return nullptr; // check for null pointer and size
    int *largest = arr; // the start of the array;
    for(int i = 0; i < size; i++){
        if(*(largest) < *(arr+i)) largest = arr+i;
    }
    return largest;
}

struct DynamicArray {
    int* arr = nullptr;
    int size = 0;

    int* create_array(int newSize) {
        if (newSize <= 0) return nullptr;

        delete[] arr;

        size = newSize;
        arr = new int[size];
        for(int i = 0; i < size; i++){
            cin >> arr[i];
        }
        return arr;
    }

    void free_array() {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }

    void resizeArray(int newSize) {
        if (newSize <= 0) {
            free_array();
            return;
        }

        int* newArr = new int[newSize];

        int cnt = (newSize < size) ? newSize : size;

        for (int i = 0; i < cnt; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;

        arr = newArr;
        size = newSize;
    }

    void reverse_array() {
        for (int i = 0; i < size / 2; i++) {
            swap(&arr[i], &arr[size - 1 - i]);
        }
    }

    void print_array() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int SizeofArray() {
        return size;
    }

    ~DynamicArray() {
        delete[] arr;
    }
} dynamicArray ;


int menu(){
	int choice = -1;
	do{
		cout << "\nEnter your choice:\n";
		cout << "1) Create Array\n";
		cout << "2) Print\n";
		cout << "3) Reverse\n";
		cout << "4) Resize\n";
        cout << "5) Get Size\n";
        cout << "6) Exit\n";

		if (!(cin >> choice)) {
            // handle non-integer input
            cout << "Invalid input (not a number). Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }
        if(choice == 6){
            cout << "Exiting" << endl;
            break;
        }
        if (choice < 1 || choice > 5) {
            cout << "WRONG INPUT, TRY AGAIN!\n";
            choice = -1;
        }
    } while (choice == -1);

    return choice;
}

void run() {
    while (true) {
        int choice = menu();

        if (choice == 1) {
            int n;
            cout << "Size of the array?: ";
            cin >> n;

            dynamicArray.create_array(n);
        }
        else if (choice == 2) {
            dynamicArray.print_array();
        }
        else if (choice == 3) {
            dynamicArray.reverse_array();
            dynamicArray.print_array();
        }
        else if (choice == 4) {
            int newSize;
            cout << "The new Size: ";
            cin >> newSize;

            dynamicArray.resizeArray(newSize);

            cout << "Size: "
                 << dynamicArray.SizeofArray()
                 << endl;
        }
        else if (choice == 5) {
            cout << "Size: "
                 << dynamicArray.SizeofArray()
                 << endl;
        }
        else if (choice == 6) {
            break;
        }
    }
}
int main(){
    run();
}