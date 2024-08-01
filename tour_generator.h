//
//  tour_generator.hpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#ifndef tour_generator_hpp
#define tour_generator_hpp

#include <stdio.h>
#include "base_classes.h"
#include "router.h"
#include "geodb.h"
#include "geopoint.h"
#include "geotools.h"
#include "HashMap.h"
#include "tourcmd.h"
#include "stops.h"
#include "string"
using namespace std;


class TourGenerator: public TourGeneratorBase
{
public:
 TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
 virtual ~TourGenerator();
 virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
    
    
private:

    const GeoDatabaseBase& GEO_db;
    const RouterBase& Router_db;

    string getDirection(GeoPoint a, GeoPoint b) const;
    
};












#endif /* tour_generator_hpp */
