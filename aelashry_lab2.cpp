//Amina El-Ashry
//Program that demonstrates the two types of searches 

//preprocessor directives
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

//global constants and enum for menu
const int NUM_TEAMS{ 10 };
const int NUM_MEMBERS{ 3 };
enum {DISPLAY=1, LSEARCH, BSEARCH, QUIT};

//struct that stores team info
struct TeamS {
	int ID;
	string names[NUM_MEMBERS];
};

//function calls
void initialize(vector <TeamS>& TeamV, const int id[], const string members[][NUM_MEMBERS], int arraySize);
void displayTeams(const vector <TeamS>& TeamV);
void menu();
void linSearchTeams(const vector <TeamS>& TeamV, int id);
void binSearchTeams(const vector <TeamS>& TeamV, int id);

int main() {

	//vector of type TeamS
	vector<TeamS> TeamV;

	//array of team ids
	const int teamID[NUM_TEAMS]{ 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };

	//2d array of team members
	const string teamMembers[NUM_TEAMS][NUM_MEMBERS]{
		{"Ayo", "Angie", "Shawn"},
		{"Avalon", "Nehemiah", "James"},
		{"Zulekha", "Kyle", "Jay"},
		{"Mickey", "Minnie", "Daisy"},
		{"Donald", "Goofy", "Pluto"},
		{"Huey", "Dewey", "Louie"},
		{"Luke", "Leia", "Han"},
		{"Natasha", "Carol", "Wanda"},
		{"Harry", "Ron", "Hermione"},
		{"May", "Peter", "Mary Jane"}
	};

	//function that loads data from above array into TeamV vector
	initialize(TeamV, teamID, teamMembers, NUM_TEAMS);
	//function that displays the data that was loaded
	displayTeams(TeamV);

	int choice{ 0 };
	int id;

	//loop the displays menu after every completed selection
	//quits when user selects option 4
	do {
		//function call to display menu info
		menu();
		
		cout << "Choose an option above based on number:";
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> choice;
		}
		while (choice <= 0 || choice > 4) {
			cout << "invalid entry, please enter again:";
			cin >> choice;
		}

		//switch case that calls various functions based on choice selected
		switch (choice) {
		case DISPLAY:
			displayTeams(TeamV);
			break;
		case LSEARCH:
			cout << "What team ID would you like to search for?";
			cin >> id;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "invalid entry, please enter again:";
				cin >> id;
			}
			while (id <= 0) {
				cout << "invalid entry, please enter again:";
				cin >> id;
			}
			linSearchTeams(TeamV, id);
			break;
		case BSEARCH:
			cout << "What team ID would you like to search for?";
			cin >> id;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "invalid entry, please enter again:";
				cin >> id;
			}
			while (id <= 0) {
				cout << "invalid entry, please enter again:";
				cin >> id;
			}
			binSearchTeams(TeamV, id);
			break;
		case QUIT:
			cout << "Thank you for using this program. Exiting program...";
			break;
		default:
			cout << "invalid choice.";
			break;
		}
	} while (choice != QUIT);
	

	system("pause");
	return 0;
}

//function that loads all the data from both id and name arrays
void initialize(vector<TeamS>& TeamV, const int id[], const string members[][NUM_MEMBERS], int arraySize)
{
	//creates instance of TeamS type
	TeamS v;
	//loop that assigns element from array to element in vector
	for (int i{ 0 }; i < arraySize; i++) {
		v.ID = id[i];
		for (int j{ 0 }; j < NUM_MEMBERS; j++) {
			v.names[j] = members[i][j];
		}
		//adds struct members to element in vector
		TeamV.push_back(v);
	}
}

//function that displays the data that was previously loaded into the vector
void displayTeams(const vector<TeamS>& TeamV)
{
	//loops through vector and displays data
	for (int i{ 0 }; i < TeamV.size(); i++) {
		cout << "Team ID:" << TeamV[i].ID << endl;
		for (int j{ 0 }; j < NUM_MEMBERS; j++) {
			cout << "Team Members:" << TeamV[i].names[j] << endl;
		}
		cout << endl;
	}

}

//function that displays the menu options
void menu() {
	//menu display 
	cout << "\nMENU" << endl << endl <<
		"1. DISPLAY" << endl <<
		"2. LINEAR SEARCH" << endl <<
		"3. BINARY SEARCH" << endl <<
		"4. QUIT PROGRAM" << endl << endl;
}

//function that performs linear search based on team id user wants to look for
void linSearchTeams(const vector<TeamS>& TeamV, int id)
{
	int i{ 0 }; //index to search vector
	int position{ -1 }; //position where value is found
	bool found{ false }; //whether value was found or not

	//loops through vector and if id is found the position is stored 
	//otherwise position will stay -1 and value will not be found
	while (i < TeamV.size() && !found) {
		if (TeamV[i].ID == id) {
			found = true;
			position = i;
			cout << "ID was found. Here is the team information:" << endl;
			cout << "Team ID: " << TeamV[position].ID << endl;
			cout << "Team Members:";
			for (int index{ 0 }; index < NUM_MEMBERS; index++) {
				cout << TeamV[position].names[index] << " ";
			}
			cout << endl;
		}
		i++;
	}
	if (position == -1 ) {
		cout << "Team ID not found.";
	}
}

//function that performs binary search based on team id user wants to look for
void binSearchTeams(const vector<TeamS>& TeamV, int id)
{
	int first{ 0 }, middle, position{ -1 };
	int last = TeamV.size()-1; //last variable is set to last element in vector 
	bool found{ false };

	while (!found && first <= last) {
		middle = (first + last) / 2; //starts search in the middle
		//if value is middle, then it is found and position is the middle
		if (TeamV[middle].ID == id) {
			found = true;
			position = middle;
			cout << "ID was found. Here is the team information:" << endl;
			cout << "Team ID: " << TeamV[position].ID << endl;
			cout << "Team Members:";
			for (int index{ 0 }; index < NUM_MEMBERS; index++) {
				cout << TeamV[position].names[index] << " ";
			}
			cout << endl;
		}
		//if id user is looking for is less than middle position, check the values to the left of middle
		else if (TeamV[middle].ID > id) {
			last = middle - 1;
			
		}
		// if id user is looking for is greater than middle position, check the values to the right of middle
		else {
			first = middle + 1;
		}
	}

	//if value of position after looping through vector is -1, then id was not found
	if (position == -1 ) {
		cout << "Team ID not found.";
	}
}
