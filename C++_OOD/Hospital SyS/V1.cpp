#include<iostream>
#include<limits>
using namespace std;
const int MAX_SPEC = 20;
const int MAX_QUEUE = 5;
string names[MAX_SPEC+1][MAX_QUEUE+1];
int status[MAX_SPEC+1][MAX_QUEUE+1];
int queue_len[MAX_SPEC+1];

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

// encups type shit:
void shift_left(int spec, string names_sp[], int status_sp[]){ //deletion
    // shift elements from right to left
    int len = queue_len[spec];
	for (int i = 1; i < len; i++) {
        names_sp[i-1] = names_sp[i];
		status_sp[i-1] = status_sp[i];
    }
	queue_len[spec]--; // decrease size because there is one patient left with the Dr.
}

void shift_right(int spec, string names_sp[], int status_sp[]){ // addition 
	int len = queue_len[spec];
	for (int i = len-1; i >= 0; i--) {	// critical to start from END
		names_sp[i+1] = names_sp[i];
		status_sp[i+1] = status_sp[i];
	}
	queue_len[spec]++; // increase size because we made room for the new patient.
}

bool add_patient(){ // output: urgent or not
	string name;
	int spec, stat;
	cin >> spec >> name >> stat;
	int pos = queue_len[spec];
	if(pos >= MAX_QUEUE){
		cout << "Sorry There is no available seats in the current specialization ):";
		return false;
	}
	if(status == 0){ // not urgent
		names[spec][pos] = name;
		status[spec][pos] = stat;
		queue_len[spec]++;
	}
	else{
		shift_right(spec, names[spec], status[spec]);
		names[spec][0] = name;
		status[spec][0] = stat; 
		// the urgent patient became the first one
	}
	return true;
}

void print_patient(int spec, string names_sp[], int status_sp[]){
	int len = queue_len[spec];
	if(len == 0){
		return;
	}
	cout << "There is " << len << " in " << spec << " Specilizaions" << endl;
	for(int i = 0; i < len; ++i){
		cout << names_sp[i] << " ";
		if(status_sp[i]){
			cout << "Urgent\n"; 
		}
		else{
			cout << "Regular\n";
		}
		
	}
	cout << endl;
}

void print_all(){
	cout << "------------------------------" << endl;
	for(int spec = 0; spec < MAX_SPEC; ++spec){
		print_patient(spec, names[spec], status[spec]);
	}
}

void Dr_Selection(){
	int spec;
	cout << "Enter Specialization: ";
	cin >> spec;
	int len = queue_len[spec];
	if(len == 0){
		cout << "No Patients, Rest Doc (:" << endl;
		return;
	}
	else{
		cout << names[spec][0] << " Go with Dr" << endl;
		shift_left(spec, names[spec], status[spec]);
	}
}

void system_dsp(){
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
int main(){
	system_dsp();
	return 0;
}