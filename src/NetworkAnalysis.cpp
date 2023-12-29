#include "NetworkAnalysis.h"


NetworkAnalysis::NetworkAnalysis(const GraphType &networkGraph)
    : networkGraph(networkGraph){}

string NetworkAnalysis::get_max_element(vector<int> verticies_arr) {
      string max = "NULL";
    
    auto max_vertex_iterator = max_element(verticies_arr.begin(), verticies_arr.end());
    
    if(max_vertex_iterator != verticies_arr.end())
    {
        int max_vertex_index = distance(verticies_arr.begin(), max_vertex_iterator);

        max = networkGraph.get_vertex(max_vertex_index);
    }

    return max; 
}


string NetworkAnalysis::calculateMostActive()
{  
    string mostActive = "NULL";
    vector<int> inDegree = networkGraph.getIndegree();
    vector<int> outDegree = networkGraph.getOutdegree();

    int max = -1, max_index = -1;
    for(int i = 0; i < inDegree.size() && i < outDegree.size(); i++)
    {
        if((inDegree[i] + outDegree[i]) > max)
        {
            max = inDegree[i] + outDegree[i];
            max_index = i;
        }
    }
    
    if(max_index != -1)
    {
        mostActive = networkGraph.get_vertex(max_index);
    }

    return mostActive; 
}

string NetworkAnalysis::calculateMostInfluencer()
{
    string mostInfluencer = get_max_element(networkGraph.getOutdegree());
    
    return mostInfluencer; 
}

vector<string> NetworkAnalysis::get_mutual_friends(string user_1, string user_2) 
{
    vector<string> mutual_friends;

    int user_1_index = networkGraph.get_vertex_index(user_1);
    int user_2_index = networkGraph.get_vertex_index(user_2);
    
    //This means you entered an ID of a user that doesn't exist
    if(user_1_index == -1 ||user_2_index == -1 )
    {
        mutual_friends.push_back("FALSE");
        return mutual_friends;
    }

    int vertices_max = networkGraph.get_vertices_max();

    int ** adjacency_matrix = networkGraph.get_adjacency_matrix();
    for(int i = 0; i < vertices_max; i++)
    {
        if(i == user_1_index || i == user_2_index)
            continue;

        if(adjacency_matrix[user_1_index][i] && adjacency_matrix[user_2_index][i])
            mutual_friends.push_back(networkGraph.get_vertex(i));
    } 

    return mutual_friends;
}

vector<string> NetworkAnalysis::suggest_new_followers(string user)
{   
    vector<string> suggested_new_followers;
    
    int user_index = networkGraph.get_vertex_index(user);

    //This means you entered an ID of a user that doesn't exist
    if(user_index == -1)
    {
        suggested_new_followers.push_back("FALSE");
        return suggested_new_followers;
    }

    int vertices_max = networkGraph.get_vertices_max();

    vector<int> followers_indices;
    int ** adjacency_matrix = networkGraph.get_adjacency_matrix();
    for(int i = 0; i < vertices_max; i++)
    {
        if(i != user_index && adjacency_matrix[user_index][i])
        {
            followers_indices.push_back(i);
        }
    } 

    for(int vertex_index : followers_indices)
    {
        for(int i = 0; i < vertices_max; i++)
        {
            if(i != user_index && adjacency_matrix[vertex_index][i])
            {
                suggested_new_followers.push_back(networkGraph.get_vertex(i));
            }
        } 
    }

    return suggested_new_followers;
}