#pragma once

#include "Person.cpp"
#include <numeric>
#include <limits>

class Graph {
private:
    std::vector<std::pair<int, Person>> graph;
    int size;

public:
    //constructor
    Graph();

    Person* getPerson(int id) const;
    int getSize() const;
    std::vector<std::pair<int, Person>> getGraph() const;
    static int edgeWeight(const Graph &graph, int u, int v);

    void addPerson(int id, const Person &person);
    void removeFriendship(int id1, int id2);

    std::vector<int> suggestFriends(int person_id, int mode) const;
    std::vector<int> suggestFriendsByCommonFriends(const Person *person) const;
    std::vector<int> suggestFriendsByOccupation(const Person *person) const;
    std::vector<int> suggestFriendsByAge(const Person *person) const;

    void degreeCentrality() const;
    double clusteringCoefficient(int id) const;
    std::vector<std::vector<int>> girvanNewman(int iterations) const;

};

//overloaded operator
std::ostream& operator<<(std::ostream& os, const Graph& g);
auto sortComparator = [](const std::pair<int, Person>& a, const std::pair<int, Person>& b){};
auto equalityComparator = [](const std::pair<int, Person>& a, const std::pair<int, Person>& b){};