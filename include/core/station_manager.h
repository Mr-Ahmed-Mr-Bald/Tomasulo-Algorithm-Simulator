#ifndef STATION_MANAGER_H
#define STATION_MANAGER_H

// Required headers
#include "core/config.h"
#include "core/enums.h"
#include "core/memory.h"
#include "reservation_station.h"
#include <unordered_map>
#include <vector>


// Class representing the manager of all reservation stations
class StationManager {
  // Properties
  std::vector<std::vector<ReservationStation>> stations;

  public:
  // Constructor
  StationManager(Memory &memory);

  // Methods
  ReservationStation* find_free(Enums::RSClass type);
  ReservationStation* get_by_id(int id);
  ReservationStation* get_by_instruction_id(int instruction_id);
  std::vector<ReservationStation*> get_stations_of_type(Enums::RSClass type);
  std::vector<ReservationStation*> get_all_stations();
  std::vector<const ReservationStation*> get_stations_of_type(Enums::RSClass type) const;
  std::vector<const ReservationStation*> get_all_stations() const;
  void reset();
};

#endif // STATION_MANAGER_H
