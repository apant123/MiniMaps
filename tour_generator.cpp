//
//  tour_generator.cpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#include "tour_generator.h"
#include "geotools.h"
#include <vector>

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router):GEO_db(geodb), Router_db(router) {}


TourGenerator::~TourGenerator() {}


string TourGenerator::getDirection(GeoPoint a, GeoPoint b) const {
    double angle = angle_of_line(a,b);
    string temp;
    
    if( angle >= 0 && angle < 22.5) return "east";
    else if(angle < 67.5) return "northeast";
    else if(angle < 112.5) return "north";
    else if(angle < 157.5) return "northwest";
    else if(angle < 202.5) return "west";
    else if(angle < 247.5) return "southwest";
    else if(angle < 292.5) return "south";
    else if(angle < 337.5) return "southeast";
    
    return "east";
    
}







std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> result;
    
    for(int i = 0; i < stops.size(); i++) { // changed stops.size () - 1 to stops.size()
        TourCommand current;
        string accesspoi;
       // string accessnextpoi;
        string accesscommentary;
        //string accessnextcommentary;
        stops.get_poi_data(i, accesspoi, accesscommentary);
        //stops.get_poi_data(i + 1, accessnextpoi, accessnextcommentary);
        current.init_commentary(accesspoi, accesscommentary);
        result.push_back(current);
        if(i != stops.size() - 1){
            string accessnextpoi;
            string accessnextcommentary;
            stops.get_poi_data(i + 1, accessnextpoi, accessnextcommentary);
            GeoPoint now;
            GeoPoint tomorrow;
            GEO_db.get_poi_location(accesspoi, now);
            GEO_db.get_poi_location(accessnextpoi, tomorrow);
            vector<GeoPoint> path = Router_db.route(now, tomorrow);
       
            
            
            for(int j = 0; j < path.size() - 1 && path.size() != 0; j++) {
                string streetName = GEO_db.get_street_name(path[j], path[j + 1]);
                string direction = getDirection(path[j], path[j + 1]);
                double distance = distance_earth_miles(path[j], path[j + 1]);
                TourCommand Proceed;
                Proceed.init_proceed(direction, streetName, distance, now, tomorrow);
                result.push_back(Proceed);
                if(j + 2 < path.size()) { // changed <= to <
                    GeoPoint third = path[j + 2];
                    string secondStreetName = GEO_db.get_street_name(path[j + 1], third);
                    if(secondStreetName != streetName) {
                        double angleTurn = angle_of_turn(path[j], path[j+1], third);
                        if(angleTurn >= 1 && angleTurn <= 359) {
                            string Turndirection;
                            if(angleTurn >= 1 && angleTurn < 180) Turndirection = "left";
                            else Turndirection = "right";
                            TourCommand turn;
                            //string Turndirection = getDirection(path[j + 1], third);
                            turn.init_turn(Turndirection, secondStreetName);
                            result.push_back(turn);
                        }
                    }
                    
                }

            }
        }
        
        
        
        
    }
    
    
    
    
    return result;
    
}
