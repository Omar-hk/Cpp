#include<iostream>
#include<limits>
using namespace std;
using ll = int64_t;

//global variables
const int MAX_SPEC = 20;
const int MAX_QUEUE = 5;

int menu(){
	int choice = -1;
	do{
		cout << "\nEnter your choice:\n";
		cout << "1) Add new patient\n";
		cout << "2) Print all patients\n";
		cout << "3) Get next patient\n";
		cout << "4) Exit\n";

		if (!(cin >> choice)) {
            // handle non-integer input
            cout << "Invalid input (not a number). Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        if (choice < 1 || choice > 4) {
            cout << "WRONG INPUT, TRY AGAIN!\n";
            choice = -1;
        }
    } while (choice == -1);

    return choice;
}

struct hospital_queue {
    struct patient_data
    {
        string names[MAX_QUEUE];
        int status[MAX_QUEUE];
    } p_data;
    int len;
    int spec;

    hospital_queue(){ // def
        len = 0;
        spec = -1; 
    }
    hospital_queue(int _spec){
        len = 0;
        spec = _spec;
    }
    bool add_end(string name, int stat){ // normal patient/ bool cuz we want to know if the array of patients is full or not. more info at #128 if-cond
        if(len == MAX_QUEUE){
            return false;
        }
        else{
            p_data.names[len] = name;
            p_data.status[len] = stat;
            len++;
            return true;
        }
    }
    bool add_front(string name, int stat){ // same as add_end.
        if(len == MAX_QUEUE){
            return false;
        }
        else{
            //shift right
            for(int i = len - 1; i >= 0; --i){
                p_data.names[i+1] = p_data.names[i];
                p_data.status[i+1] = p_data.status[i];   
            }
            p_data.names[0] = name;
            p_data.status[0] = stat;
            len++;
            return true;
        }
    }
    void remove_front(){ 
        if(len == 0){
            cout << "there is no patients left" << endl;
        }
        else{
            cout << "patient: " << p_data.names[0] << " go with Dr" << endl;
            for(int i = 1; i < len; i++){
                p_data.names[i-1] = p_data.names[i];
                p_data.status[i-1] = p_data.status[i];
                len--;
            }
        }
        
    }
    void print(){
        if(len == 0){
            return; // empty
        }
        else{
            cout << "there is " << len << " number of patients" << endl;
            for(int i = 0; i < len; i++){
                cout << p_data.names[i] << " ";
                if(p_data.status[i]){
                    cout << "Urgent" << endl;
                }
                else{
                    cout << "Normal" << endl;
                }
            }
        }
        cout << endl;
    }
};

struct hospital_sys{
    hospital_queue queues[MAX_SPEC];
    hospital_sys(){
        for(int i = 0; i < MAX_SPEC; i++){ // to create MAX_SPEC's specilizations
            queues[i] = hospital_queue(i);
        }
    }
    bool add_patient(){
        int spec, stat;
        string name;
        cout << "Enter Name, Spec, Statue: ";
        cin >> name >> spec >> stat;
        bool statue;
        if(stat == 0){
            statue = queues[spec].add_end(name, stat);

        }
        else{
            statue = queues[spec].add_front(name, stat);
        }
        if(!statue){
            cout << "We Can't add more, FULL" << endl;
            return false;
        }
        return true;
    }

    void print_all(){
        for(int spec = 0; spec < MAX_SPEC; spec++){
            queues[spec].print();
        }
    }

    void Dr_Selection(){
        int spec;
        cout << "Enter Spec: ";
        cin >> spec;
        queues[spec].remove_front();
    }  
    void run(){
	    while(true){
		    int choice = menu();
		    if(choice == 1){
			    add_patient();
		    }
		    else if(choice == 2){
			    print_all();
		    }
		    else if(choice == 3){
			    Dr_Selection();
		    }
		    else{
			    break;
		    }
	    }
    }
};

int main(){
    hospital_sys hospital = hospital_sys();
	hospital.run();
}