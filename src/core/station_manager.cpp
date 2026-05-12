#include "../../include/core/station_manager.h"

//creates the number of stations depending on config file
//first station is empty station
StationManager::StationManager(){
    int id = 1;
    ReservationStation rsEmpty(0, RSClass(0)); //empty reservation station, to serve as no reservation station available

    for(int i = 1; i < 8; i++){ //skip empty reservation station
        for(int j = 0; j < reservation_station_num[i-1]; j++){
            ReservationStation rs(id, RSClass(i));
            stations.push_back(rs);
            if(j == 0)
                indices_by_type.insert({RSClass(i), std::vector<int>()}); //initialize at given location in map
            indices_by_type.at(RSClass(i)).push_back(id); //push back the id at the given RSClass
            id++; //increment id for all reservation stations (so that each has different id) 
        }  
    }
}

//finds a free station by the given RSClass type
ReservationStation* StationManager::find_free(RSClass type){
    std::vector<int> indicesList = indices_by_type.at(type);

    for(int index : indicesList){
        if(stations[index].is_free())
            return &(stations[index]);
    }

    return new ReservationStation(0, RSClass(0)); //empty reservation station

}

//gets the station by the given id
ReservationStation* StationManager::get_by_id(int id){
    if(id >= 0 && id < stations.size())
        return &stations[id];
    return &stations[0];
}

//gets all stations by RSClass type
std::vector<ReservationStation*> StationManager::get_stations_of_type(RSClass type){
    std::vector<ReservationStation*> new_stations;
    std::vector<int> stations_at_location = indices_by_type.at(type);
    for(int index : stations_at_location){
        new_stations.push_back(&(stations[index]));       
    }
    return new_stations;
}

//gets a list of all stations that are ready to write back from stations list
std::vector<ReservationStation*> StationManager::ready_to_write_back(){
    std::vector<ReservationStation*> new_stations;
    for (int i = 1; i < stations.size(); i++){
        if(stations[i].done())
            new_stations.push_back(&stations[i]);
    }
    return new_stations;

}