#include "utils.cpp"
#include <iostream>

void printMenu() 

{
    std::cout << "*****************************************************\n"; 
    std::cout << "               WELCOME TO PROGRAM               \n";
    std::cout << "*****************************************************\n";
    std::cout << "| 1) Display the social network                     |\n";
    std::cout << "| 2) Suggest friends                                |\n";
    std::cout << "| 3) Calculate degree centrality                    |\n";
    std::cout << "| 4) Calculate clustering coefficient               |\n";
    std::cout << "| 5) Detect communities                             |\n";
    std::cout << "| 6) Exit the program                               |\n";
    std::cout << "*****************************************************\n";
    std::cout << "Please enter your choice: ";
}

int main() 
{
    Graph graph = readData("social_network.csv");

    int enter;

    do 
    {
         printMenu();
        std::cin >> enter;

        switch (enter) {
            case 1: 
            {
                std::cout << graph << std::endl;
                break;
            }
            case 2: 
            {
                int id;
                int condition;
                std::cout << "Enter person id for friend suggestions: ";
                std::cin >> id;
                std::cout << "Enter condition (1-Common Friends, 2-Occupation, 3-Age): ";
                std::cin >> condition;
                std::vector<int> suggestions = graph.suggestFriends(id, condition);
                std::cout << "Friend suggestions for person " << id << " are: ";
                for (int id : suggestions) {
                    std::cout << id << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 3: 
            {
                graph.degreeCentrality();
                break;
            }
            case 4: 
            {
                int id;
                std::cout << "Enter person ID to calculate clustering coefficient: ";
                std::cin >> id;
                double coefficient = graph.clusteringCoefficient(id);
                std::cout << "Clustering coefficient for person " << id << " is " << coefficient << std::endl;
                break;
            }
            case 5: 
            {
                int iterations;
                std::cout << "Enter number of iterations for the Girvan-Newman algorithm: ";
                std::cin >> iterations;
                std::vector<std::vector<int>> communities = graph.girvanNewman(iterations);
                std::cout << "Detected communities are:\n";
                for (const std::vector<int>& community : communities) {
                    for (int id : community) {
                        std::cout << id << " ";
                    }
                    std::cout << std::endl;
                }
                break;
            }
            case 6: 
            {
                std::cout << "Exiting the program..." << std::endl;
                break;
            }
            default: 
            {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    } while (enter != 6); //continues unless the user wants to quit the programs

    return 0;
}