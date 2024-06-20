#pragma once
#include <string>

namespace bht {

// GTFS Date format is YYYYMMDD
typedef struct SGTFSDate {
	unsigned char	day;
	unsigned char	month;
	unsigned short year;
} GTFSDate;

// GTFS time format is HH:MM:SS
typedef struct SGTFSTime {
	unsigned char	hour;
	unsigned char	minute;
	unsigned char second;
} GTFSTime;

/**
 * Data imported from GTFS data - agency.txt
 * (https://gtfs.org/schedule/reference/#agencytxt)
 */
typedef struct SAgency {
  std::string id;
  std::string name;
  std::string url;
  std::string timezone;
  std::string language;
  std::string phone;
} Agency;

/**
 * Data imported from GTFS data - calendar_dates.txt
 * (https://gtfs.org/schedule/reference/#calendar_datestxt)
*/
typedef enum ECalendarDateException { CalendarDateException_AddedDate = 1, CalendarDateException_RemovedDate = 2 } CalendarDateException;
typedef struct SCalendarDate {
  std::string serviceId;
  GTFSDate date;
  CalendarDateException exception;
} CalendarDate;

/**
 * Data imported from GTFS data - calendar.txt
 * (https://gtfs.org/schedule/reference/#calendartxt)
*/
typedef enum ECalendarAvailability { CalendarAvailability_Available = 0, CalendarAvailability_NotAvailable = 1 } CalendarAvailability;
typedef struct SCalendar {
  std::string serviceId;
  CalendarAvailability monday;
  CalendarAvailability tuesday;
  CalendarAvailability wednesday;
  CalendarAvailability thursday;
  CalendarAvailability friday;
  CalendarAvailability saturday;
  CalendarAvailability sunday;
  GTFSDate startDate;
  GTFSDate endDate;
} Calendar;

/**
 * Describes levels in a station. Useful in conjunction with pathways.txt.
 * https://gtfs.org/schedule/reference/#levelstxt
 */
typedef struct SLevel {
  std::string id;
  unsigned int index;
  std::string name;
} Level;

/**
 * Files pathways.txt and levels.txt use a graph representation to describe subway or train stations, with nodes representing locations and edges representing pathways.
 * https://gtfs.org/schedule/reference/#pathwaystxt
 */
typedef enum EPathwayMode { PathwayMode_Walkway = 1, PathwayMode_Stairs = 2, PathwayMode_MovingSidewalk = 3, PathwayMode_Escalator = 4, PathwayMode_Elevator = 5, PathwayMode_FareGate = 6 } PathwayMode;
typedef struct SPathway {
  std::string id;
  std::string fromStopId;
  std::string toStopId;
  PathwayMode mode;
  bool isBidirectional;
  float length;
  unsigned int traversalTime;
  unsigned int stairCount;
  float maxSlope;
  float minWidth;
  std::string signpostedAs;
} Pathway;

/**
 * Description of routes in the network
 * https://gtfs.org/schedule/reference/#routestxt
 */
typedef enum ERouteType { RouteType_Tram = 0, RouteType_Subway = 1, RouteType_Rail = 2, RouteType_Bus = 3, RouteType_Ferry = 4, RouteType_CableTram = 5, RouteType_AerialLift = 6, RouteType_Funicular = 7, RouteType_Trolleybus = 11, RouteType_Monorail = 12 } RouteType;
typedef struct SRoute {
  std::string id;
  std::string agencyId;
  std::string shortName;
  std::string longName;
  std::string description;
  RouteType type;
  std::string color;
  std::string textColor;
} Route;

/**
 * Shapes describe the path that a vehicle travels along a route alignment
 * https://gtfs.org/schedule/reference/#shapestxt
 */
typedef struct SShape {
  std::string id;
  double latitide;
  double longitude;
  unsigned int sequence;
} Shape;

/**
 * Times for each trip they arrive at each stop
 * https://gtfs.org/schedule/reference/#stop_timestxt
*/
typedef enum EPickupType { PickupType_Regular = 0, PickupType_NoPickup = 1, PickupType_ByAgency = 2, PickupType_ByDriver = 3 } PickupType;
typedef enum EDropOffType { DropOffType_Regular = 0, DropOffType_NoDropOff = 1, DropOffType_ByAgency = 2, DropOffType_ByDriver = 3 } DropOffType;
typedef struct SStopTime {
  std::string tripId;
  GTFSTime arrivalTime;
  GTFSTime departureTime;
  std::string stopId;
  unsigned int stopSequence;
  PickupType pickupType;
  EDropOffType dropOffType;
  std::string stopHeadsign;
} StopTime;

/**
 * Description of stops inside the network
 * https://gtfs.org/schedule/reference/#stopstxt
 */
typedef enum ELocationType { LocationType_Stop = 0, LocationType_Station = 1, LocationType_EntranceOrExit = 2, LocationType_GenericNode = 3, LocationType_BoardingArea = 4 } LocationType;
typedef enum EWheelchairAccessibility { WheelchairAccessibility_NoInformation = 0, WheelchairAccessibility_Inherit = 0, WheelchairAccessibility_Available = 1, WheelchairAccessibility_NotAvailable = 2 } WheelchairAccessibility;
typedef struct SStop {
  std::string id;
  std::string code;
  std::string name;
  std::string description;
  double latitide;
  double longitude;
  LocationType locationType;
  std::string parentStation;
  WheelchairAccessibility wheelchairBoarding;
  std::string platformCode;
  std::string levelId;
  std::string zoneId;
} Stop;

/**
 * When calculating an itinerary, GTFS-consuming applications interpolate transfers based on allowable time and stop proximity
 * Transfers.txt specifies additional rules and overrides for selected transfers.
 * https://gtfs.org/schedule/reference/#transferstxt
 */
typedef enum ETransferType { TransferType_Recommended = 0, TransferType_Timed = 1, TransferType_MinTransferTime = 2, TransferType_NoTransfer = 3, TransferType_InSeatTransfer = 4, TransferType_ReBoard = 5 } TransferType;
typedef struct STransfer {
  std::string fromStopId;
  std::string toStopId;
  std::string fromRouteId;
  std::string toRouteId;
  std::string fromTripId;
  std::string toTripId;
  TransferType type;
  unsigned int minTransferTime;
} Transfer;

/**
 * Information about trips in the network
 * https://gtfs.org/schedule/reference/#tripstxt
 */
typedef enum ETripDirection { TripDirection_Inbound = 0, TripDirection_Outbound = 1 } TripDirection;
typedef struct STrip {
  std::string id;
  std::string routeId;
  std::string serviceId;
  std::string headsign;
  std::string shortName;
  TripDirection direction;
  std::string blockId;
  std::string shapeId;
  WheelchairAccessibility wheelchairAccessible;
  bool bikesAllowed;
} Trip;

}