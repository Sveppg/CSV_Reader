#include "network.hpp"
#include "CSVReader.hpp"
#include "types.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <type_traits>

namespace bht {

Network::Network(const std::string& directoryPath) {
    // Laden der Daten aus den Dateien
    loadAgencies(directoryPath + "/agency.txt");
    loadCalendars(directoryPath + "/calendar.txt");
    loadLevels(directoryPath + "/levels.txt");
    loadPathways(directoryPath + "/pathways.txt"); 
    loadRoutes(directoryPath + "/routes.txt");
    loadShapes(directoryPath +"/shapes.txt");

}


//load different maps for different file types
void Network::loadAgencies(const std::string& filePath) {
    CSVReader agencyReader(filePath);
    while (agencyReader.hasNext()) {
        if (agencyReader.next()) {
            Agency agency;
            agency.id = agencyReader.getField("agency_id");
            agency.name = agencyReader.getField("agency_name");
            agency.url = agencyReader.getField("agency_url");
            agency.timezone = agencyReader.getField("agency_timezone");
            agency.language = agencyReader.getField("agency_lang");
            agency.phone = agencyReader.getField("agency_phone");
            agencies[agency.id] = agency;
        }
    }
}

void loadCalendarDates(const std::string filePath){
    CSVReader calendarDatesReader(filePath);
    while(calendarDatesReader.hasNext()){
        if(calendarDatesReader.next()){
            CalendarDate calendarDate;
            calendarDate.serviceId = calendarDatesReader.getField("service_ID");
            calendarDate.date = static_cast<GTFSDate>(std::(calendarDatesReader.getField("")));
        }
    }
}

void Network::loadCalendars(const std::string& filePath) {
    CSVReader calendarReader(filePath);
    while (calendarReader.hasNext()) {
        if (calendarReader.next()) {
            Calendar calendar;
            calendar.serviceId = calendarReader.getField("service_id");
            calendar.monday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("monday")));
            calendar.tuesday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("tuesday")));
            calendar.wednesday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("wednesday")));
            calendar.thursday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("thursday")));
            calendar.friday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("friday")));
            calendar.saturday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("saturday")));
            calendar.sunday = static_cast<CalendarAvailability>(std::stoi(calendarReader.getField("sunday")));
            calendar.startDate = {
                static_cast<unsigned char>(std::stoi(calendarReader.getField("start_date").substr(6, 2))),
                static_cast<unsigned char>(std::stoi(calendarReader.getField("start_date").substr(4, 2))),
                static_cast<unsigned short>(std::stoi(calendarReader.getField("start_date").substr(0, 4)))
            };
            calendar.endDate = {
                static_cast<unsigned char>(std::stoi(calendarReader.getField("end_date").substr(6, 2))),
                static_cast<unsigned char>(std::stoi(calendarReader.getField("end_date").substr(4, 2))),
                static_cast<unsigned short>(std::stoi(calendarReader.getField("end_date").substr(0, 4)))
            };
            calendars[calendar.serviceId] = calendar;
        }
    }
}

void Network::loadLevels(const std::string& filePath){
    CSVReader levelReader(filePath);
    while(levelReader.hasNext()){
        if(levelReader.next()){
            Level level;
            level.id = levelReader.getField("levels_id");
            level.index = std::stoi(levelReader.getField("index_level"));
            level.name = levelReader.getField("level_name");
            levels[level.id] = level;

        }
    }
}

void Network::loadPathways(const std::string& filePath){
    CSVReader pathwaysReader(filePath);
    while(pathwaysReader.hasNext()){
        if(pathwaysReader.next()){
            Pathway pathway;
            pathway.id = pathwaysReader.getField("pathways_level");
            pathway.toStopId = pathwaysReader.getField("to_stop");
            pathway.fromStopId = pathwaysReader.getField("from_stop");
            pathway.mode = static_cast<PathwayMode>(std::stoi(pathwaysReader.getField("pathway_mode")));
            pathway.isBidirectional = std::stoi(pathwaysReader.getField("is_bidirectional"));
            pathway.length = static_cast<PathwayMode>(std::stof(pathwaysReader.getField("length")));
            pathway.traversalTime = static_cast<unsigned int>(std::stoi(pathwaysReader.getField("traversalTime")));
            pathway.stairCount = static_cast<unsigned int> (std::stoi(pathwaysReader.getField("stairCount")));
            pathway.maxSlope = static_cast<PathwayMode>(std::stof(pathwaysReader.getField("maxSlope")));
            pathway.minWidth = static_cast<PathwayMode>(std::stof(pathwaysReader.getField("minWidth")));
            pathway.signpostedAs = static_cast<PathwayMode>(std::stoi(pathwaysReader.getField("signpostedAds")));
            pathways[pathway.id] = pathway;
        }        
    }
}

void Network::loadRoutes(const std::string& filePath){
    CSVReader routesReader(filePath);
    while(routesReader.hasNext()){
        if(routesReader.next()){
            Route route;
            route.id = routesReader.getField("route_id");
            route.agencyId = routesReader.getField("agency_id");
            route.shortName = routesReader.getField("route_short_name");
            route.longName = routesReader.getField("route_long_name");
            route.description = routesReader.getField("route_desc");
            route.type = static_cast<RouteType>(std::stoi(routesReader.getField("route_type")));
            route.color = routesReader.getField("route_color");
            route.textColor = routesReader.getField("route_text_color");
            routes[route.id] = route;
        }
    }
}

void Network::loadShapes(const std::string& filePath){
    CSVReader shapesReader(filePath);
    while(shapesReader.hasNext()){
        if(shapesReader.next()){
            Shape shape;
            shape.id = shapesReader.getField("shape_id");
            shape.latitide = std::stod(shapesReader.getField("shape_pt_lat"));
            shape.longitude = std::stod(shapesReader.getField("shape_pt_lon"));
            shape.sequence = std::stoi(shapesReader.getField("shape_pt_sequence"));
            shapes[shape.id] = shape;
        }
    }
}

void Network::loadStopTimes(const std::string& filePath){
    CSVReader stopTimesReader(filePath);
    while(stopTimesReader.hasNext()){
        if(stopTimesReader.next()){
            StopTime stopTime;
            stopTime.tripId = stopTimesReader.getField("trip_id");
            stopTime.arrivalTime = stopTimesReader.getField("arrival_time"); // unfinished
            stopTime.departureTime = static_cast<GTFSTime>(std::stoi(stopTimesReader.getField("departure_time"))); // unfinished
            stopTime.stopId = stopTimesReader.getField("stop_id"); 
            stopTime.stopSequence = static_cast<unsigned int>(std::stoi(stopTimesReader.getField("stop_sequence")));
            stopTime.pickupType = static_cast<PickupType>(std::stoi(stopTimesReader.getField("pickup_type")));
            stopTime.dropOffType = static_cast<EDropOffType>(std::stoi(stopTimesReader.getField("drop_off_type"))); // finished
        }
    }//"trip_id","arrival_time","departure_time","stop_id","stop_sequence","pickup_type","drop_off_type","stop_headsign"
}

} 