#include "Graph.h"

// Constructor
Graph::Graph() : size(0) 
{ 
    // graph is initially empty.    
}

Person* Graph::getPerson(int id) const 
{
    for (const auto& pair : graph) 
    {
        if (pair.first == id) 
        {
            return (Person*) &pair.second;
        }
    }
    return nullptr;
}

int Graph::getSize() const 
{
    return size;
}

std::vector<std::pair<int, Person>> Graph::getGraph() const 
{
    return graph;
}

int Graph::edgeWeight(const Graph &graph, int u, int v) 
{
    Person* person_u = graph.getPerson(u);
    Person* person_v = graph.getPerson(v);
    if (person_u && person_v) {
        std::vector<int> friends_u = person_u->getFriends();
        std::vector<int> friends_v = person_v->getFriends();
        std::vector<int> common_friends;
        std::set_intersection(friends_u.begin(), friends_u.end(), friends_v.begin(), friends_v.end(), std::back_inserter(common_friends));
        return common_friends.size();
    }
    return 0;
}

void Graph::addPerson(int id, const Person &person) 
{
    graph.push_back(std::make_pair(id, person));
    size++;
}

void Graph::removeFriendship(int id1, int id2) 
{
    Person* person1 = getPerson(id1);
    Person* person2 = getPerson(id2);
    if (person1 && person2) 
    {
        person1->removeFriend(id2);
        person2->removeFriend(id1);
    }
}

std::vector<int> Graph::suggestFriends(int person_id, int mode) const {
    const Person* person = getPerson(person_id);
    std::vector<int> suggestions;

    if (!person) 
    {
        return suggestions; 
    }

    switch(mode) 
    {
        case 1:
            return suggestFriendsByCommonFriends(person);
        case 2:
            return suggestFriendsByOccupation(person);
        case 3:
            return suggestFriendsByAge(person);
    }

    return suggestions;
}

std::vector<int> Graph::suggestFriendsByCommonFriends(const Person* person) const 
{
    std::vector<int> suggestions;

    if (!person) return suggestions;

   
    for (const auto& pair : graph) 
    {
        
        if (person->isFriend(pair.first)) 
        {
            for (const auto& friendOfFriendID : pair.second.getFriends()) 
            {
                
                if (!person->isFriend(friendOfFriendID) && friendOfFriendID != person->getID()) 
                {
                    suggestions.push_back(friendOfFriendID);  //suggest
                }
            }
        }
    }

    //remove duplicates
    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());

    return suggestions;
}

std::vector<int> Graph::suggestFriendsByOccupation(const Person *person) const {
    std::vector<int> suggestions;

    if (!person) return suggestions;

    // Loop through all the pairs in the graph
    for (const auto& pair : graph) 
    {
        // If this person is not already a friend and shares the same occupation
        if (pair.second.getOccupation() == person->getOccupation() && !person->isFriend(pair.first) && pair.first != person->getID()) 
            {
                suggestions.push_back(pair.first);  // Suggest them as a friend
            }
    }

    return suggestions;
}

std::vector<int> Graph::suggestFriendsByAge(const Person *person) const {
    std::vector<int> suggestions;

    if (!person) return suggestions;

    //age range (example 3 year)
    int age_lower_bound = person->getAge() - 3;
    int age_upper_bound = person->getAge() + 3;

    // Loop through all the pairs in the graph
    for (const auto& pair : graph) 
    {
        // If this person is not already a friend and is within the same age range
        if (pair.second.getAge() >= age_lower_bound && pair.second.getAge() <= age_upper_bound && !person->isFriend(pair.first) && pair.first != person->getID()) 
            {
                suggestions.push_back(pair.first);  // Suggest them as a friend
            }
    }

    return suggestions;
}


void Graph::degreeCentrality() const 
{
    for (const auto& pair : graph) 
    {
        std::cout << "Person " << pair.second.getID()  << pair.second.getName() << " has degree centrality: " << pair.second.getFriends().size() << std::endl;
    }
}

double Graph::clusteringCoefficient(int id) const {
    const Person* person = getPerson(id);
    if (!person) {
        
        return 0.0;
    }

    const std::vector<int>& friends = person->getFriends();
    int friendCount = friends.size();
    if (friendCount < 2) {
       
        return 0.0;
    }

    int triangleCount = 0;
    int possibleTriangles = 0;

    for (int i = 0; i < friendCount - 1; ++i) {
        for (int j = i + 1; j < friendCount; ++j) {
            int friend_1 = friends[i];
            int friend_2 = friends[j];

            // Check if friend_1 and friend_2 are connected
            const Person* person_1 = getPerson(friend_1);
            const Person* person_2 = getPerson(friend_2);

            if (person_1 && person_2) {
                const std::vector<int>& friends_1 = person_1->getFriends();
                const std::vector<int>& friends_2 = person_2->getFriends();

                // Check if friend_1 and friend_2 are friends with each other
                if (std::find(friends_1.begin(), friends_1.end(), friend_2) != friends_1.end() &&
                    std::find(friends_2.begin(), friends_2.end(), friend_1) != friends_2.end()) {
                    // friend_1 and friend_2 are connected now, so increase (++) triangleCount
                    ++triangleCount;
                }

                //increase possibleTriangles
                ++possibleTriangles;
            }
        }
    }

    if (possibleTriangles == 0) {
        
        return 0.0;
    }

    // Calculate and return the clustering coefficient
    return static_cast<double>(triangleCount) / possibleTriangles;
}

std::vector<std::vector<int>> Graph::girvanNewman(int iterations) const {
     
    Graph newGraph = *this;
    std::vector<std::pair<int, Person>> graphCopy = newGraph.getGraph();

     
    for (int i = 0; i < iterations; ++i) {
        int maxBetweenness = 0;
        int maxU = -1;
        int maxV = -1;

        // Find the edge with the highest weight (betweenness)
        for (const auto& pairU : graphCopy) {
            for (const auto& pairV : graphCopy) {
                if (pairU.first != pairV.first) {
                    int betweenness = Graph::edgeWeight(newGraph, pairU.first, pairV.first);
                    if (betweenness > maxBetweenness) {
                        maxBetweenness = betweenness;
                        maxU = pairU.first;
                        maxV = pairV.first;
                    }
                }
            }
        }

        // Remove the edge with the highest weight
        if (maxU != -1 && maxV != -1) {
            newGraph.removeFriendship(maxU, maxV);
        }
    }

     
    int minID = std::numeric_limits<int>::max();
    int maxID = std::numeric_limits<int>::min();
    for (const auto& pair : newGraph.getGraph()) {
        minID = std::min(minID, pair.first);
        maxID = std::max(maxID, pair.first);
    }

    //create a list (empty)
    std::vector<std::vector<int>> communities(maxID - minID + 1);

     
    for (const auto& pair : newGraph.getGraph()) {
        int index = pair.first - minID;
        for (int friendID : pair.second.getFriends()) {
            communities[index].push_back(friendID);
        }
    }

    
    communities.erase(std::remove_if(communities.begin(), communities.end(), [](const std::vector<int>& community) {
        return community.empty();
    }), communities.end());

    
    return communities;
}


// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Graph& g) {
    for (const auto &pair : g.getGraph()) {
        os << pair.second; //print person
    }
    return os;
}
