/*
	Author: Guerschom Kayembe
	Course: CS405G
	Professor: Paul Linton
	Date of submission: Feb 03, 2020

*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <locale>
#include <algorithm>
using namespace std;

// lowercase a string
string LowerCase(string str) {
	string lower = "";
    	for(int i = 0; i < str.length(); i++) {
        	lower += tolower(str.at(i));
    }
    return lower;
}

int main() {
	string word;
	string line;
	ifstream myfile1;
	ifstream myfile2;

    	// open the txt files
    	myfile1.open ("personnel_addresses.txt");
    	myfile2.open ("personnel_salaries.txt");

    	// error if unable to open
    	if(!myfile1 && !myfile2){
        	cout << "Unable to open file"<< endl;
        	return 0;
    	}

    	// take user input
    	cout << "Enter a name of any city you'd like to search: ";
    	cin >> word;

    	// vector to store names of people whole city matches the search
    	vector<string> names;

    	// loop through the addresses txt file and store matched names
    	// in names vector
    	while(!myfile1.eof()){
        	string temp1;
        	getline(myfile1, temp1);

        	// split into name and city
        	string name, city;
        	stringstream lineStream(temp1);
        	getline(lineStream, name, '|');
        	getline(lineStream, city, '|');

        	// lowercase both to match correctly
        	if(LowerCase(city).find(LowerCase(word)) != std::string::npos) {
            		// push name to names vector
            		names.push_back(name);
        	}
    	}

    	// loop over the salaries txt file and store the details of
    	// people in a map
    	int counter = 0;
    	map<string, string> m;
    	while(!myfile2.eof()){
        	string temp2;
        	getline(myfile2, temp2);

        	stringstream lineStream(temp2);
        	string name, salary;
        	getline(lineStream, name, '|');
        	getline(lineStream, salary, '|');
        	m.insert(pair<string, string>(name, salary));
    	}

    	// loop through names vector and print the details of people that matched.
    	for(int i = 0; i < names.size(); i++) {
        	map<string, string>::iterator it = m.find(names.at(i));
        	if(it != m.end()) {
            		cout << ++counter << ". " << it->first << ":" << it->second << endl;
        	}
    	}

    	// close both txt files
    	myfile1.close();
    	myfile2.close();

    	return 0;
}

