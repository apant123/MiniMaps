p00//
//  geodb.hpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#ifndef geodb_hpp
#define geodb_hpp

#include <stdio.h>
#include "base_classes.h"
#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class GeoDatabase: public GeoDatabaseBase
{
public:
    GeoDatabase();
    virtual ~GeoDatabase();
    virtual bool load(const std::string& map_data_file) ;
    virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
    
private:
    HashMap<GeoPoint> poiLocations;
    HashMap<std::string> streetNames;
    
    HashMap<std::vector<GeoPoint>> connectedPoints;
    vector<string> wtf;
    vector<string> externalGeo;
    
    
    string main;
    string main1;
    
    int count;
    bool checker;
    bool thisisnotgood;
    
    GeoPoint createSingularGeopoint(string temp) const;
    vector<string> splitstring(string temp) const;
    bool containS(string temp) const;
    vector<string> splitspace(string temp, int type) const;
    vector<string> calculations(string temp) const;
    vector<GeoPoint> createGeopoint(string temp) const;
    string extractCoordinates(const string& input) const;
    string createAppention(string one, string two, string three) const;
    void addGeoPoint(string temp) const;
    string stringConcat(string one, string two) const;
    string fourConcat(string one, string two, string three, string four) const;
    bool hasAlphabetCharacter(const std::string& str);
     
    
};





#endif /* geodb_hpp */
