#ifndef STATION_MANAGER_H
#define STATION_MANAGER_H

// Required headers
#include "config.h"
#include "reservation_station.h"
#include <unordered_map>
#include <vector>


// Class representing the manager of all reservation stations
class StationManager {
  // Properties
  std::vector<ReservationStation> stations;
  std::unordered_map<RSClass, std::vector<int>> indices_by_type;

  public:
  // Constructor
  StationManager();

  // Methods
  ReservationStation* find_free(RSClass type);
  ReservationStation* get_by_id(int id);
  std::vector<ReservationStation*> get_station_of_type(RSClass type);
  void reset();
  std::vector<ReservationStation*> ready_to_write_back() const;
};

#endif // STATION_MANAGER_H