#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename.c_str());
    string line;
    names.clear();
    scores.clear();
    grades.clear();
    char cN[100];
    int S[3], sum;
    while(getline(source, line)){
        sscanf(line.c_str(), "%[^:]: %d %d %d", cN, &S[0], &S[1], &S[2]);
        sum = S[0] + S[1] + S[2];
        names.push_back((string)cN);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &cmd, string &key){
    string line;
    char ccmd[10];
    char ckey[100];

    cout << "Please input your command: ";
    getline(cin, line);
    sscanf(line.c_str(), "%s %[^\n]", ccmd, ckey);
    cmd = (string) ccmd;
    key = (string) ckey;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == toUpperStr(key)){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << '\n';
            cout << names[i] << "'s grade = " << grades[i] << '\n';
            cout << "---------------------------------\n";
            return;
        }
    }

    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool isFounded = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(toupper(key[0]) == toupper(grades[i])){
            isFounded = true;
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }

    if(!isFounded){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
