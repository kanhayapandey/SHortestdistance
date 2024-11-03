#include <bits/stdc++.h>
using namespace std;


//Succcessfully aplying dijkstra  algorithm and created my own project
// I am trying to find the shortest distance between two cities and also the time it will take to reach the destination city.
//sucessfuly learnt  try catch block.

class Cities
{
protected:
    unordered_map<string, vector<pair<string, pair<int, int>>>> adjcities;

public:
    void addcities(const string &city1, const string &city2, int distance, int time)
    {
        // Add both directions for an undirected graph
        adjcities[city1].push_back({city2, {distance, time}});
        adjcities[city2].push_back({city1, {distance, time}});
    }

    bool checkcity(const string &city)
    {
        return adjcities.find(city) != adjcities.end();
    }
};

class finding : public Cities
{
public:
    pair<int, int> findShortestPathdistance(const string &startCity, const string &endCity)
    {
        if (adjcities.find(startCity) == adjcities.end() || adjcities.find(endCity) == adjcities.end())
        {
            cout << "One or both cities not found." << endl;
            return {-1, -1};
        }

        unordered_map<string, int> distances;
        unordered_map<string, int> times;
        for (const auto &city : adjcities)
        {
            distances[city.first] = INT_MAX;
            times[city.first] = INT_MAX;
        }
        distances[startCity] = 0;
        times[startCity] = 0;

        using Node = pair<int, string>; // (distance, city)
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0, startCity}); // initial distance and start city

        while (!pq.empty())
        {
            int currentDistance = pq.top().first;
            string currentCity = pq.top().second;
            pq.pop();

            if (currentCity == endCity)
            {
                return {currentDistance, times[currentCity]};
            }

            for (const auto &entry : adjcities[currentCity])
            {
                string neighbourCity = entry.first;    // Neighbor city
                int cityDistance = entry.second.first; // Distance to neighbor
                int travelTime = entry.second.second;  // Travel time to neighbor

                int newDistance = currentDistance + cityDistance;
                int newTime = times[currentCity] + travelTime;

                if (newDistance < distances[neighbourCity] || (newDistance == distances[neighbourCity] && newTime < times[neighbourCity]))
                {
                    distances[neighbourCity] = newDistance;
                    times[neighbourCity] = newTime;
                    pq.push({newDistance, neighbourCity});
                }
            }
        }
        return {-1, -1}; // return -1 if no path is found
    }
};

int main()
{
    finding finder; // Create an object of finding to add cities and perform path finding

    // Add cities and paths
    finder.addcities("A", "B", 10, 3);
    finder.addcities("A", "C", 5, 2);
    finder.addcities("B", "C", 8, 2);
    finder.addcities("B", "D", 4, 1);
    finder.addcities("B", "E", 10, 2);
    finder.addcities("C", "F", 10, 2);
    finder.addcities("D", "G", 6, 2);
    finder.addcities("E", "H", 15, 4);
    finder.addcities("E", "F", 1, 1);
    finder.addcities("F", "I", 5, 2);

    string cityA, cityB;
    cout << "Enter your location: ";
    cin >> cityA;
    cout << "Where you want to go: ";
    cin >> cityB;

    if (cityA == cityB)
    {
        cout << "Both locations should not be the same." << endl;
    }
    else
    {
        try
        {
            if (!finder.checkcity(cityA) || !finder.checkcity(cityB))
            {
                cout << "We are not reached there" << endl;
            }
            else
            {
                auto result = finder.findShortestPathdistance(cityA, cityB);
                int distance = result.first;
                int time = result.second;
                
                if (distance == -1)
                {
                    cout << "No path found between " << cityA << " and " << cityB << endl;
                }
                else
                {
                    cout << "Total distance is: " << distance << " units" << endl;
                    cout << "Total travel time is: " << time << " units" << endl;
                }
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    return 0;
}
