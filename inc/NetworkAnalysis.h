#pragma once 
#include "GraphType.h"

using namespace std;

class NetworkAnalysis
{
private:
    GraphType networkGraph; 

    string get_max_element(vector<int> verticies_arr);
public:

/** @defgroup  Constructors
  * @{
  */
    /**
     * @brief Overloaded constructor 
     * 
     * @param networkGraph: The graph to do the analysis on.
     */
    NetworkAnalysis(const GraphType &networkGraph);
/**
  * @}
  */

    /**
     * @brief Finds the user in the graph that follows the most people [OutDegree]
     * 
     * @return string: ID of the user, and NULL in case of we didn't find it.
     */
    string calculateMostInfluencer();

    /**
     * @brief Finds the user in the graph that is connected to the most people [OutDegree + inDegree]
     * 
     * @return string: ID of the user, and NULL in case of we didn't find it. 
     */
    string calculateMostActive();

    /**
     * @brief Gets a list of users that both user_1 and user_2 follows.
     * 
     * @param user_1 
     * @param user_2 
     * @return vector<string>: list of mutual users
     * In case we didn't find a user with the given ID it will return a vector with one element
     * called "FALSE"..
     */
    vector<string> get_mutual_friends(string user_1, string user_2);

    /**
     * @brief Gets a list of recommended users to follow {the people that his followers follow}
     * 
     * @param user: the user to suggest followers to.
     * @return vector<string>: list of recommended users in case of we found the user,
     * In case we didn't find a user with the given ID it will return a vector with one element
     * called "FALSE".
     */
    vector<string> suggest_new_followers(string user);
};