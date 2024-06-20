#pragma once
#ifndef NETWORK_HPP
    #define NETWORK_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "types.h"

namespace bht {

class Network {
public:
    explicit Network(const std::string& directoryPath);
    std::unordered_map<std::string, Agency> agencies;
    std::vector<CalendarDate> calendarDates; // unfinished
    std::unordered_map<std::string, Calendar> calendars;
    std::unordered_map<std::string, Level> levels;
    std::unordered_map<std::string, Pathway> pathways;
    std::unordered_map<std::string, Route> routes;
    std::vector<Shape> shapes;
    std::vector<StopTime> stopTimes;
    std::unordered_map<std::string, Stop> stops;
    std::vector<Transfer> transfers;
    std::vector<Trip> trips;

private:
    void loadAgencies(const std::string& filePath);
    void loadCalendarDates(const std::string& filePath); 
    void loadCalendars(const std::string& filePath);
    void loadLevels(const std::string& filePath);
    void loadPathways(const std::string& filePath);
    void loadRoutes(const std::string& filePath);
    void loadShapes(const std::string& filePath);
    void loadStopTimes(const std::string& filePath);
      

};

} // namespace bht


#endif