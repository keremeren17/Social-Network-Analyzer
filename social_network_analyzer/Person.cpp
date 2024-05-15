#include "Person.h"

// Constructor
Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, const std::vector<int>& friends)
    : id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

//getters ande setters
int Person::getID() const 

{ 
    return id; 
}

std::string Person::getName() const 
{
     return name; 
}

int Person::getAge() const 
{ 
    return age; 
}

std::string Person::getGender() const 
{ 
    return gender; 
}

std::string Person::getOccupation() const 
{ 
    return occupation; 
}

std::vector<int> Person::getFriends() const 
{ 
    return friends; 
}

void Person::setID(int newId)
{ 
    id = newId; 
}

void Person::setName(std::string newName) 
{ 
    name = newName; 
}

void Person::setAge(int newAge) 
{ 
    age = newAge; 
}

void Person::setGender(std::string newGender) 
{
     gender = newGender; 
}

void Person::setOccupation(std::string newOccupation) 
{ 
    occupation = newOccupation; 
}

//others
void Person::addFriend(int friendID) 
{
    // Checks if the friend in question already exists
    if (std::find(friends.begin(), friends.end(), friendID) != friends.end()) 
    {
        return; // If the friend already exists, do not add it again
    }
    friends.push_back(friendID);
}

void Person::removeFriend(int friendID)
{
    auto it = std::find(friends.begin(), friends.end(), friendID);
    if (it != friends.end()) {
        friends.erase(it);
    }
}

bool Person::isFriend(int friendID) const 
{
    return std::find(friends.begin(), friends.end(), friendID) != friends.end();
}

std::ostream& operator<<(std::ostream& os, const Person& person_) {
    os << "\nID: " << person_.getID() << std::endl
       << "Name: " << person_.getName() << std::endl
       << "Age: " << person_.getAge() << std::endl
       << "Gender: " << person_.getGender() << std::endl
       << "Occupation: " << person_.getOccupation() << std::endl
       << "Friends: ";

    for (int friendID : person_.getFriends()) 
    {
        os << friendID << " ";
    }

    os << std::endl; //son geçiş

    return os;
}
