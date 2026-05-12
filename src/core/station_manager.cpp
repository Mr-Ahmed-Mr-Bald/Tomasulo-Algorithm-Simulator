#include "core/station_manager.h"

// Constructor
StationManager::StationManager(Memory &memory) {
    stations.resize(Config::NUM_FUNCTIONAL_UNITS);
    for(int i = 0, k = 0; i < Config::NUM_FUNCTIONAL_UNITS; i++) {
        for(int j = 0; j < Config::get_reservation_station_num(i); j++, k++) {
            stations[i].push_back(
                ReservationStation(k, static_cast<Enums::RSClass>(i), memory)
            );
        }
    }
}

// Finds a free reservation station of the given type
ReservationStation* StationManager::find_free(Enums::RSClass type) {
    for (auto& station : stations[static_cast<int>(type)]) {
        if (station.is_free()) {
            return &station;
        }
    }
    return nullptr; // No free station found
}

// Gets a reservation station by its unique ID
ReservationStation* StationManager::get_by_id(int id) {
    for (auto& station_list : stations) {
        for (auto& station : station_list) {
            if (station.get_id() == id) {
                return &station;
            }
        }
    }
    return nullptr; // No station with the given ID found
}

// Gets all reservation stations of a specific type
std::vector<ReservationStation*> StationManager::get_stations_of_type(Enums::RSClass type) {
    std::vector<ReservationStation*> result;
    for (auto& station : stations[static_cast<int>(type)]) {
        result.push_back(&station);
    }
    return result;
}

// Resets all reservation stations to their initial state
void StationManager::reset() {
    for (auto& station_list : stations) {
        for (auto& station : station_list) {
            station.clear();
        }
    }
}