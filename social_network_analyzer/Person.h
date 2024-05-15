#pragma once
#include <vector>
#include <string> /// for name, gender, occupation etc.
#include <algorithm> // to use std::find, std::sort 
#include <iostream>

class Person {
private:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string occupation;
    std::vector<int> friends;

public:
    // Constructor
    Person(int id, std::string name, int age, std::string gender, std::string occupation, const std::vector<int>& friends);

    //getters and setters
    int getID() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getOccupation() const;
    std::vector<int> getFriends() const;
    void setID(int id);
    void setName(std::string name);
    void setAge(int age);
    void setGender(std::string gender);
    void setOccupation(std::string occupation);

    //others
    void addFriend(int friendID);
    void removeFriend(int friendID);
    bool isFriend(int friendID) const;
};

// Overloaded operator<<
std::ostream& operator<<(std::ostream& os, const Person& p);
