#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <utility>
#include "SocialNetwork.cpp"

using namespace std;

void readUserFile(vector<User*>& users, string fileName){
    ifstream file;
    file.open(fileName);

    string line="";
    getline(file, line); //ignoring header line
    line="";
    while(getline(file, line)){
        int userId;
        string userName;
        string fullName;
        string tempString="";
    
        stringstream inputString(line);

        //getting id
        getline(inputString, tempString, ',');
        userId = atoi(tempString.c_str()); //converting from string to int

        //getting name
        getline(inputString, userName, ',');
        getline(inputString, fullName);

        User* user = new User(userId, userName, fullName);
        users.push_back(user);
    }
    
    file.close();
}

bool compareFrequency(const pair<User*, int>& a, const pair<User*, int>& b) {
    return a.second > b.second; // Sort in descending order
}

bool compareConnections(const User* a, const User* b) {
    return a->connections < b->connections; // Sort in ascending order
}


void randomConnections(vector<User*>& users, SocialNetwork*& network){
    for (int i = 0; i < users.size(); i++) {
        int connections = (rand() % 50) + 1; //randomizing number of connections user will have
        users.at(i)->connections = connections; //initializing connections integer

        unordered_set<User*> addedFriends; //keeping track of added friends
        while (addedFriends.size() < connections) { //loop until we have the desired number of connections
            int num = (rand() % users.size()); //randomizing to find user to connect to

            if (users.at(i) != users.at(num) && addedFriends.find(users.at(num)) == addedFriends.end()) { //created to avoid duplicates
                users.at(i)->friends.push_back(users.at(num)); //adding friend to current user's friend list
                network->addEdge(users.at(i), users.at(num)); //connect current user to random user
                addedFriends.insert(users.at(num)); //mark this user as added
            }
        }
    }
}

void influentialMeasures(vector<User*> users){
    vector<User*> most_influential_users; //keeping track of influential users
    vector<User*> least_influential_users; //keeping track of least influential users
    
    int count_most=0;
    int count_least=0;
    cout << "*ANALYZING INFLUENTIAL USERS USING CENTRALITY MEASURES*" << endl;
    for(int i=50; i>0; i--){ //finding users with connections 50 to 0
        for(int j=0; j<250; j++){ //looping through all users
            if(users.at(j)->connections == i){  //if number of connections matches i, then top connections
                if(count_most>9){ //if count mark is reached, break out of loop
                    break;
                }
                most_influential_users.push_back(users.at(j)); //keeping track of users with the top connections
                count_most++;//increase count because user is added
            }
        }
    }

    cout << "*Top 10 Most Influential Users*" << endl;
    for(int i=0; i<most_influential_users.size(); i++){
        cout << i+1 << ". ";
        most_influential_users.at(i)->print();
    }

    for(int i=0; i<50; i++){ //finding users with connections 0 to 50
        for(int j=0; j<250; j++){ //looping through all users
            if(users.at(j)->connections == i){  //if number of connections matches i, then least connections
                if(count_least>9){ //if count mark is reached, break out of loop
                    break;
                }
                least_influential_users.push_back(users.at(j)); //keeping track of users with the least connections
                count_least++;//increase count because user is added
            }
        }
    }
    cout << endl; //for spacing
    cout << "*Top 10 Least Infuential Users*" << endl;
    for(int i=0; i<least_influential_users.size(); i++){
        cout << i+1 << ". ";
        least_influential_users.at(i)->print();
    }
    
}

void connectedNetworkComponents(vector<User*> users){
    cout << "*IDENTIFY STRONGLY CONNECTED NETWORK COMPONENTS*" << endl;
    int average = 0; //calculating average
    for(int i=0; i < users.size(); i++){ //adding each user's number of connections to calculate average
        average += users.at(i)->connections;
    }
    cout << "Average number of connections per user: " << "\n" << (average/users.size()) << endl; //calculating average num of connections per user

    vector<User*> sorted_users = users;
    sort(sorted_users.begin(), sorted_users.end(), compareConnections);

    double median = 0.0; //calculating median
    int n = sorted_users.size();

    if(n%2 == 0){ //checking if number of elements is even
        median = (sorted_users[n / 2 - 1]->connections + sorted_users[n / 2]->connections) / 2.0; //taking two middle values and then averaging
    }
    else{
        median = sorted_users[n/2]->connections;
    }

    cout << "Median number of connections: " << "\n" << median << endl;

}


void networkStatistics(vector<User*>& users){ //calculting network statistics
    int average = 0; //calculating average
    vector<User*> topConnections; //keeping track of top connections

    for(int i=0; i < users.size(); i++){ //adding each user's number of connections to calculate average
        average += users.at(i)->connections;
    }

    int count = 0; //count keeps track of the top 10 users

    for(int i=50; i>0; i--){ //finding users with connections 50 to 0
        for(int j=0; j<250; j++){ //looping through all users
            if(users.at(j)->connections == i){  //if number of connections matches i, then top connections
                if(count>10){ //if count mark is reached, break out of loop
                    break;
                }
                topConnections.push_back(users.at(j)); //keeping track of users with the top connections
                count++;//increase count because user is added
            }
        }
    }
    cout << "*NETWORK STATISTICS:*" << endl;
    cout << "Number of users: " << "\n" << users.size() << endl; //printing number of users
    cout << "Average number of connections per user: " << "\n" << (average/users.size()) << endl; //calculating average num of connections per user
    cout << "Top 10 users with most connections: " << endl;

    for(int i=0; i<topConnections.size()-1; i++){ //looping through top connections vector
        cout << i+1 << ". " << topConnections.at(i)->fullName << endl;
        cout << "With " << topConnections.at(i)->connections << " connections" << endl;
    }
    
}

void friendSuggestions(vector<User*> users){
    cout << "*FRIEND SUGGESTIONS*" << endl;
    for(int s=0; s<5; s++){
        int a = rand() % users.size();
        User* user = users.at(a);

        vector<User*> mutuals; //keep tracking of mutuals

        for(int i=0; i<user->friends.size(); i++){ //looping through current user's friends list
            vector<User*> friend_mutuals = user->friends.at(i)->friends; //current user's friend's friends
            mutuals.insert(mutuals.end(), friend_mutuals.begin(), friend_mutuals.end()); //adding to mutuals
        }

        unordered_map<User*, int> frequency; //storing frequency of users 
        for(int i=0; i<mutuals.size(); i++){
            frequency[mutuals[i]]++;
        }

        vector<pair<User*, int> > sorted_frequency; //storing the frequency data in pairs
        for (const auto& entry : frequency) {
            sorted_frequency.push_back(make_pair(entry.first, entry.second));
        }
        
        sort(sorted_frequency.begin(), sorted_frequency.end(), compareFrequency);
    
        cout << user->fullName << endl;
        cout << "Top 5 suggested users: " << endl;; //printing out suggested users
        for (int i = 0; i < min(5, (int)sorted_frequency.size()); i++) {
            cout << sorted_frequency[i].first->fullName << endl;
        }
        cout << endl;
    }
}

void shortestPath(SocialNetwork* network, vector<User*> users){
    cout << "*DETERMINING SHORTEST PATH*" << endl;
    for(int i=0; i<5; i++){
        int a = rand() % users.size();
        int b = rand() % users.size();

        vector<User*> short_path = network->shortestPath(users.at(a), users.at(b));

        cout << "From " << users.at(a)->fullName << endl;
        cout << " to " << users.at(b)->fullName << endl;
        cout << "---------------" << endl;
        for(int i=0; i<short_path.size(); i++){
            cout << short_path.at(i)->fullName << endl;
            if(i!= short_path.size()-1){
                cout << " to " << endl;
            } 
        }
        cout << endl;
    }
}


int main(){
    vector<User*> users;
    string fileName = "users.csv";
    readUserFile(users, fileName);

    SocialNetwork* network = new SocialNetwork();

    for(int i=0; i<users.size();i++){ //adding to graph
        network->addVertex(users.at(i));
    }

    randomConnections(users, network);
    cout << endl; //spacing
    cout << endl; //spacing

    networkStatistics(users);
    cout << endl; //spacing
    cout << endl; //spacing

    friendSuggestions(users);
    cout << endl; //spacing
    cout << endl; //spacing

    shortestPath(network, users);
    cout << endl; //spacing
    cout << endl; //spacing

    influentialMeasures(users);
    cout << endl; //spacing
    cout << endl; //spacing

    connectedNetworkComponents(users);

    return 0;
}