//
//  router.cpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#include "router.h"
#include "geodb.h"
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;



Router::Router(const GeoDatabaseBase& geo_db):GEO_db(geo_db) {}


Router::~Router() {}


 GeoPoint Router::stringToGeoPoint(string temp) const {
    vector<string> abc;
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] == ' ') {
            abc.push_back(temp.substr(0, i));
            abc.push_back(temp.substr(i + 1));
        }
    }
    
     GeoPoint a(abc[0], abc[1]);
     return a;
     
     
}







std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {


    std::vector<GeoPoint> path;

          // If start and end points are the same, return a path with just one point
          if (pt1.sLatitude == pt2.sLatitude && pt1.sLongitude == pt2.sLongitude) {
              path.push_back(pt1);
              return path;
          }

    std::unordered_map<std::string, GeoPoint> parent_map;

    std::unordered_map<std::string, std::string> cameFrom;
    std::unordered_map<std::string, double> g_score;
   std::priority_queue<std::pair<GeoPoint, double>, std::vector<std::pair<GeoPoint, double>>, ComparePairs> pq;
//    std::priority_queue<GeoPoint, std::vector<GeoPoint>, ComparePairs> pq;

    pq.push({pt1, 0.0});
    cameFrom[getLongLat(pt1)] = getLongLat(pt1);
    g_score[getLongLat(pt1)] = 0.0;
    while(!pq.empty()) {
        std::pair<GeoPoint, double> top_pair = pq.top();
            //double dist = top_pair.second;
            GeoPoint current = top_pair.first;
            pq.pop();

        if(current.sLatitude == pt2.sLatitude && current.sLongitude == pt2.sLongitude){
            
            GeoPoint current = pt2;
            while(current.sLatitude != pt1.sLatitude && current.sLongitude != pt1.sLongitude) {
                path.push_back(current);
                current = stringToGeoPoint(cameFrom[getLongLat(current)]);
            }
            path.push_back(pt1); // optional
            std::reverse(path.begin(), path.end());
            
            return path;
        }

        for(GeoPoint next : GEO_db.get_connected_points(current)) {
            double new_cost = g_score[getLongLat(current)] + heuristic(current, next);
            if(g_score.find(getLongLat(next)) == g_score.end() || new_cost < g_score[getLongLat(current)] ) {
                g_score[getLongLat(next)] = new_cost;
                double priority = new_cost + heuristic(next, pt2);
                pq.push({next, priority});
                cameFrom[getLongLat(next)] = getLongLat(current);
            }
        }
    }

    return path;



    }


