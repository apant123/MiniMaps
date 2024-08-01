//
//  router.hpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#ifndef router_hpp
#define router_hpp

#include <stdio.h>
#include "base_classes.h"
#include "geodb.h"
#include "geotools.h"
#include <string>

using namespace std;





class Router: public RouterBase
{
public:
    Router(const GeoDatabaseBase& geo_db);
    virtual ~Router();
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
private:
    
    
    const GeoDatabaseBase& GEO_db;
    
    
    string getLongLat(GeoPoint one) const {
        return one.sLatitude + " " + one.sLongitude;
    }
    
    
    double heuristic(const GeoPoint& a, const GeoPoint& b) const {
        return distance_earth_miles(a, b);
    }
    
    GeoPoint stringToGeoPoint(string temp) const;
        
        
        
        
        

    
    
    
    
    struct ComparePairs {
        bool operator()(const std::pair<GeoPoint, double>& lhs, const std::pair<GeoPoint, double>& rhs) const {
            return lhs.second > rhs.second; // Compare the first element of the pair (the double)
        }
        
        
        
        
        
    };
    
    
};




#endif /* router_hpp */














    //    double getWeight(const GeoPoint& a) const {
    //          return distance_earth_miles(a.sLatitude, a.sLongitude);
    //      }


//    };
    //
    //template<>
    //struct hash<GeoPoint> {
    //    size_t operator()(GeoPoint a) const {
    //        std::hash<std::string> hash;
    //        return hash(a.sLatitude + a.sLongitude);
    //    }
    //};
    //
    //
    //
    //

