#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class UserLogin {
private:
    
    unordered_map< string, string > table;
    

public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password
       
};

UserLogin::UserLogin() = default;

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename) {
    
 ifstream input;
    
    string full_line;
    input.open(filename);

    if (!input.is_open()) // checks to see if file is open
    {
        return;
    }

    
  
    while (getline(input, full_line))
    {
        string userName, passWord;
        stringstream SS(full_line); // gets line to read username and password to tables

       
        SS >> userName >> passWord;

        table[userName] = passWord; //inputting to table
    }

}

size_t UserLogin::numberOfUsers() {

  return table.size(); //returns the amount of users

}

string UserLogin::passWordCheck(const string& userName) {

   return table.find(userName) != table.end() ? table[userName] : "Non-existent User"; //returns the password of user if found if not then returns "Non-existant user"

}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {

    return table.bucket(userName); //returns the bucket where username is 


}

size_t UserLogin::wordBucketIdMethod2(const string& userName) {
    
    int x = table.bucket_count();

    for (int i = 0; i < x; i++) { // for loop to find a specific bucket using an iterator to navigate through the table to find the bucket that holds the username
      
        for (auto it = table.begin(i); it != table.end(i); ++it)
        {
            if (it->first == userName) //checks if bucket has username
            {
                return i; // returns bucket
         }
                  

        }
            
    }
    
}

bool UserLogin::validateUser(const string& userName) {
    
     return table.find(userName) != table.end(); //returns true if user is found in table if not false
     
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) { 
bool exists = table.find(userName) != table.end(); // searches for the user until end of table

    if (exists)
    {
        return (table.find(userName)->second == passWord); // if password matches then it returns true

    }                                                    

    return false;

      
 }
