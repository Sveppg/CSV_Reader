//lib header
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
//custom Header
#include "network.hpp"
#include "CSVReader.hpp"
#include "types.h"


//function to read lines and columns of parsed file
void getLinesnColumns(const std::string& filePath){
    std::ifstream file(filePath);
    if(!file.is_open()){
        std::cerr << "Error opening the file: " << filePath << std::endl;
            return; 
    }

    std::string line;
    int lineCount = 0; 
    int columnCount = 0;

    while(std::getline(file, line)){
        lineCount++;
        columnCount += line.length();
    }
    std::cout <<filePath << " has" << ": " << lineCount << " lines with " << columnCount << " columns " << std::endl;
        file.close();
}


int main(int argc, char **argv){
    if(argc != 2){
        std::cerr << "Usage: " << "<file-path-to-file>" << std::endl;
        return EXIT_FAILURE;
    }else{
        getLinesnColumns(argv[1]);
    }
    //bht::Network network(argv[1]);//??

    // Network class used -> print file data
    
    std::string gtfsDirectory = argv[1];
    bht::Network network(gtfsDirectory);
    
    //for Agencies
    for (const auto& pair : network.agencies) {
        const auto& agency = pair.second;
        std::cout << "Agency ID: " << agency.id 
                  << ", Name: " << agency.name 
                  << ", URL: " << agency.url 
                  << ", Timezone: " << agency.timezone 
                  << ", Language: " << agency.language 
                  << ", Phone: " << agency.phone << std::endl;
    }


    
    //for calendar
    for (const auto& pair : network.calendars) {
        const auto& calendar = pair.second;
        std::cout << "Service ID: " << calendar.serviceId 
                  << ", Monday: " << static_cast<int>(calendar.monday)
                  << ", Tuesday: " << static_cast<int>(calendar.tuesday)
                  << ", Wednesday: " << static_cast<int>(calendar.wednesday)
                  << ", Thursday: " << static_cast<int>(calendar.thursday)
                  << ", Friday: " << static_cast<int>(calendar.friday)
                  << ", Saturday: " << static_cast<int>(calendar.saturday)
                  << ", Sunday: " << static_cast<int>(calendar.sunday)
                  << ", Start Date: " << calendar.startDate.year << "-" << static_cast<int>(calendar.startDate.month) << "-" << static_cast<int>(calendar.startDate.day)
                  << ", End Date: " << calendar.endDate.year << "-" << static_cast<int>(calendar.endDate.month) << "-" << static_cast<int>(calendar.endDate.day)
                  << std::endl;
    }
    //for levels
    for (const auto& pair : network.levels) {
        const bht::Level& level = pair.second;
        std::cout << "ID: " << level.id << ", Index: " << level.index << ", Name: " << level.name << std::endl;
    }

    for(const auto& pair : network.pathways){
        const bht::Pathway& pathways = pair.second;
        std::cout << "ID: " << pathways.id 
                << "to Stop ID: " << pathways.fromStopId
                << "from StopID: " << pathways.toStopId
                << "Mode: " << pathways.mode
                << "Directional: " << static_cast<bool>(pathways.isBidirectional)
                << "Length: " << static_cast<float>(pathways.length)
                << "Traversal Time: " << static_cast<unsigned int>(pathways.traversalTime)
                << "Stair Count: " << static_cast<unsigned int>(pathways.stairCount)
                << "Max. Slope: " << static_cast<float>(pathways.maxSlope)
                << "min. Width" << static_cast<float>(pathways.minWidth)
                << "posted Ads: " << pathways.signpostedAs
                << std::endl;
    }   

    for(const auto& pair : network.routes){
        const bht::Route& route = pair.second;
        std::cout <<"Route ID: " << route.id
                << "Agency_ID: " << route.agencyId  
                << "Route_Short-Name " << route.shortName
                << "Route_Long-Name " << route.longName
                << "Route-Description " << route.description
                << "Route_Type " << route.type
                << "Route-Colour " << route.color
                << "Route Text-Colour " << route.textColor
                << std::endl;
    }   

    for(const auto& pair : network.shapes){
        const bht::Shape& shape = pair.second; //not working type second not found
        std::cout << "Shape_ID " << shape.id
                << "Shape Latitide " << shape.latitide
                << "Shape longitude " << shape.longitude
                << "Shape Sequence " << shape.sequence
                << std::endl;
    }

    for(const auto& pair : network.stopTimes){
        const bht::StopTime& stopTime = pair.second; //not working type second not found
        
    }

    return 0; 
}