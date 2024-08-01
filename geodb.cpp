//
//  geodb.cpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#include "geodb.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "geotools.h"
#include <string>
#include <cctype>
using namespace std;

GeoDatabase::GeoDatabase() {
    count = 0;
    thisisnotgood = true;
}

GeoDatabase::~GeoDatabase() {
  
    
}

bool GeoDatabase::hasAlphabetCharacter(const std::string& str) {
    for (char c : str) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    return false;
}




vector<string> GeoDatabase::splitstring(string temp) const {
    vector<string> a;
    
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] == '|') {
            a.push_back(temp.substr(0, i));
            a.push_back(temp.substr(i+1));
        }
    }
    
    for(int i = 0 ; i < a[1].size(); i++) {
        if(a[1][i] == ' ') {
            a.push_back(a[1].substr(0, i));
            a.push_back(a[1].substr(i + 1));
        }
    }
    
    return a;
}

bool GeoDatabase::containS(string temp) const{
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] == '|') {
            return true;
        }
    }
    return false;
    
}

vector<string> GeoDatabase::splitspace(string temp, int type) const {
    vector<string> a;
    int count = 0;
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] == ' ') {
            
            if(type == count) {
                a.push_back(temp.substr(0, i));
                a.push_back(temp.substr(i + 1));
            }
            
            if(type == count) {
                a.push_back(temp.substr(0, i));
                a.push_back(temp.substr(i + 1));
            }
            count++;
        }
    }
    return a;
}

string GeoDatabase::extractCoordinates(const string& input) const {
    
    size_t pos = input.find('|');
       if (pos != string::npos && pos < input.length() - 1) {
           return input.substr(pos + 1); // Extract the substring starting from the position after '|'
       } else {
           return ""; // Return an empty string if '|' is not found or if it's the last character
       }
}
string GeoDatabase::createAppention(string one, string two, string three) const{
    string temp = one + " " + two + " " + three;
    return temp;
}






//vector<string> GeoDatabase::calculations(string temp) const {
//    
//    
//}


GeoPoint GeoDatabase::createSingularGeopoint(string temp) const {
    vector<string> v;
  
    string current;
    for (char c : temp) {
          if (c == ' ') {
              v.push_back(current);
              current.clear();
          } else {
              current += c;
          }
      }
      v.push_back(current);
    GeoPoint a(v[0],v[1]);
    return a;
    
}


vector<GeoPoint> GeoDatabase::createGeopoint(string temp) const {
    vector<string> v;
    vector<GeoPoint> a;
    string current;
    for (char c : temp) {
          if (c == ' ') {
              v.push_back(current);
              current.clear();
          } else {
              current += c;
          }
      }
      v.push_back(current);
                            
    GeoPoint first(v[0],v[1]);
    GeoPoint second(v[2],v[3]);
    a.push_back(first);
    a.push_back(second);
    return a;
}



string GeoDatabase::stringConcat(string one, string two) const {
    string temp = one + " " + two;
    return temp;
}



bool GeoDatabase::load(const std::string& map_data_file) {
    std::ifstream file(map_data_file);
    if (!file.is_open()) {
           return false; // File not found
       }

       std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        
        if(containS(line) == true) {
           vector<string> temp = splitstring(line);
//            string string1 = temp[2];
//            string string2 = temp[3];
          GeoPoint temp1(temp[2], temp[3]);
            poiLocations.insert(temp[0], temp1);
        }
    
     
        if(count > 1) {
            if(line == "0"){
                count = -1;
            } else if(hasAlphabetCharacter(line) == true) {
                if(containS(line) == false) {
                    count = 0;
                } else {
                    vector<GeoPoint> temp = createGeopoint(main1);
                    GeoPoint mid = midpoint(temp[0], temp[1]);
                    vector<string> stringtemp = splitspace(main1, 1);
                    
                   // wtf.push_back(stringtemp[0]);
                    //wtf.push_back(stringtemp[1]);
                    //connectedPoints[stringtemp[0]];
                    //connectedPoints[stringtemp[1]];
                    
                    if(thisisnotgood){
                        wtf.push_back(stringConcat(mid.sLatitude, mid.sLongitude));
                        connectedPoints[stringConcat(mid.sLatitude, mid.sLongitude)];
                        externalGeo.push_back(createAppention(stringtemp[0], mid.sLatitude, mid.sLongitude));
                        externalGeo.push_back(createAppention(stringtemp[1], mid.sLatitude, mid.sLongitude));
                        thisisnotgood = false;
                    }
                    
                    streetNames.insert(createAppention(stringtemp[0], mid.sLatitude, mid.sLongitude) , main);
                    streetNames.insert(createAppention(stringtemp[1], mid.sLatitude, mid.sLongitude) , main);
                           
                    if(containS(line) == true) {
                        string stringtemp1 = extractCoordinates(line);
                        
                        connectedPoints[stringtemp1];
                        wtf.push_back(stringtemp1);
                        externalGeo.push_back(createAppention(stringtemp1, mid.sLatitude, mid.sLongitude));
                        
                        
                        
                        
                        string insert = createAppention(stringtemp1, mid.sLatitude, mid.sLongitude);
                        streetNames.insert(insert, "a path");
                    }
                    
                }
            
        }

            
        }
        
        if(count == 1) {
            //vector<string> temp = splitspace(line, 1);
            //streetNames.insert(temp[0], main);
            //streetNames.insert(temp[1], main);
            main1 = line;
            streetNames.insert(main1, main);
            count++;
            
            externalGeo.push_back(line);
            vector<string> temp = splitspace(line, 1);
            //connectedPoints.push_back
            //createGeopoint(line);
            connectedPoints[temp[0]];
            connectedPoints[temp[1]];
            wtf.push_back(temp[0]);
            wtf.push_back(temp[1]);
            
            //cout << "cooked " << endl;
            
            
            
            
        }
        
        if(count == 0) {
            main = line;
            count++;
            thisisnotgood =  true;
        }
        if(count == -1) count++;
    }
    
    
    for(int i = 0; i < wtf.size(); i++) {
        vector<GeoPoint> temp;
        for(int j = 0; j < externalGeo.size(); j++) {
            vector<string> tempstring = splitspace(externalGeo[j], 1);
            if(wtf[i] == tempstring[0]) {
                GeoPoint a = createSingularGeopoint(tempstring[1]);
                temp.push_back(a);
            } else if (wtf[i] == tempstring[1]) {
                GeoPoint b = createSingularGeopoint(tempstring[0]);
                temp.push_back(b);
            }

        }
        connectedPoints.insert(wtf[i], temp);
    }
//    
//    for(int i = 0; i <externalGeo.size(); i++ ) {
//        vector<string> temp;
//        for(int j = i + 1; j < externalGeo.size() - 1; j++) {
//            vector<string> temp;
//            if(externalGeo[i].sLatitude == externalGeo[j].sLatitude) {
//                temp.push_back(externalGeo[j].sLongitude);
//            }
//            if(externalGeo[i].sLongitude == externalGeo[j].sLongitude) {
//                temp.push_back(externalGeo[j].sLatitude);
//            }
//        }
//        connectedPoints.insert()
//        
//        
//    }
//    

    
    return true;
    

}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    
    
    const GeoPoint* foundPoint = poiLocations.find(poi);
    if(foundPoint == NULL) return false;
    point = *foundPoint;
    return true;
}


std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    
    if(connectedPoints.find(stringConcat(pt.sLatitude, pt.sLongitude)) != nullptr ){
        
        const vector<GeoPoint> a = *connectedPoints.find(stringConcat(pt.sLatitude, pt.sLongitude));
        return a;
    }


    const vector<GeoPoint> a;
    return a;
}


 std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
     string a  = fourConcat(pt1.sLatitude, pt1.sLongitude, pt2.sLatitude, pt2.sLongitude);
     string b = fourConcat(pt2.sLatitude, pt2.sLongitude, pt1.sLatitude, pt1.sLongitude);
     
     const string *c = streetNames.find(a);
     const string *d = streetNames.find(b);
     
     if(c != nullptr) return *c;
     if(d != nullptr) return *d;
     
     
    return "";
         
         
         

}



string GeoDatabase::fourConcat(string one, string two,string three, string four) const {
    
    return one + " " + two + " " + three + " " + four;
    
}



//void GeoDatabase::addGeoPoint(string temp) {
//
//    vector<string> v;
//    vector<GeoPoint> a;
//    string current;
//    for (char c : temp) {
//          if (c == ' ') {
//              v.push_back(current);
//              current.clear();
//          } else {
//              current += c;
//          }
//      }
//      v.push_back(current);
//    GeoPoint first(v[0],v[1]);
//    GeoPoint second(v[2],v[3]);
//    externalGeo.push_back(first);
//    externalGeo.push_back(second);
//
//
//
//}
