#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include "User.cpp"

using namespace std;

class SocialNetwork{
    private:
        unordered_map<User*, unordered_set<User*> > adjList;
    public:
        void addVertex(User* user);
        bool addEdge(User* user1, User* user2);
        void printGraph(); //for debugging purposes
        vector<User*> shortestPath(User* user1, User* target);
};

vector<User*> SocialNetwork::shortestPath(User* user1, User* target){
    queue<User*> q; //will hold nodes needed to explore
    unordered_map<User*, User*> parent; //will store each node's parent node
    unordered_set<User*> visited; //will keep track of already explored node
    vector<User*> path; //this vector will store the nodes in the order that it is found

    q.push(user1); //adding our first user to queue since it is the first node explored 
    visited.insert(user1); //user 1 has already been visited so we add it to set
    parent[user1] = nullptr; // user 1 node has no parent 

    while(!q.empty()){ //will continue to loop until queue is empty, meaning all of the possible paths have been explored
        User* current = q.front(); // initializing temp node to current/first node from queue since we are already exploring it
        q.pop(); //removing current/first node from queue


        if(current == target){ //our current node matches target node
            for (User* node = target; node != nullptr; node = parent[node]) { //starting from the target node and going back to the start of parent map
                path.push_back(node); //adding current node to path
            }
            reverse(path.begin(), path.end()); // reverse the path
            return path; 
        }

        for(User* neighbor : adjList[current]){ //looping through each current user in the adjacency list
            if (visited.find(neighbor) != visited.end()) { //checking to see if neighbor has been visited already
                continue;
            }
            visited.insert(neighbor); //marking neighbor as visited
            parent[neighbor] = current; //setting parent to the current node
            q.push(neighbor); // add neighbor to queue

        }
    }
    return path; //not found
}



void SocialNetwork::printGraph(){
    int count = 0;
    for (auto i = adjList.begin(); i != adjList.end(); i++) { //looping through adjList map
        cout << "User: " << i->first->fullName << endl; //user's first name will be printed
        for(auto it = i->second.begin(); it != i->second.end(); ++it){ //looping through the set of connections the user has
            cout << "Connection: " ;
            cout << (*it)->fullName << endl; //prints all connections
        }
        cout << endl;
    }
}


void SocialNetwork::addVertex(User* user){
    if(adjList.count(user)==0){ //checking if vertex doesn't exist in graph
        adjList[user]; //adding to graph
    }
}

bool SocialNetwork::addEdge(User* user1, User* user2){
    if(adjList.count(user1) != 0 && adjList.count(user2) != 0){
        adjList.at(user1).insert(user2);
        adjList.at(user2).insert(user1);
        return true;
    }
    return false;
}