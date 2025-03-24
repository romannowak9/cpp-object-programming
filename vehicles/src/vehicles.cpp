#include "vehicles.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <vector>

std::string to_string(const Vehicle& vehicle) {
    std::ostringstream oss;
    oss << vehicle.get_id() << " :  " << vehicle.get_brand();
    return oss.str();
}

std::string to_string(std::vector<Vehicle*>::const_iterator vehicles_begin,
                      std::vector<Vehicle*>::const_iterator vehicles_end) {

    std::string s;
    for (auto it = vehicles_begin; it != vehicles_end; ++it) {
        const auto& vehicle = *(*it);
        s += to_string(vehicle);
        s += "\n";
    }

//  Wersja z użyciem biblioteki standardowej - mniej czytelna...
//  std::string s = std::accumulate(vehicles_begin, vehicles_end, std::string(),
//      [](std::string &s, const Vehicle* vehicle_ptr) -> std::string& {
//    return s += to_string(*vehicle_ptr) + "\n"; });

    return s;
}

double compute_min_travel_duration(double distance, const Vehicle& vehicle) {
    return distance / vehicle.get_max_speed();
}

std::string compute_min_travel_duration_as_string(double distance, const Vehicle& vehicle) {
    std::ostringstream oss;
    oss << std::setprecision(3) << std::fixed
        << compute_min_travel_duration(distance, vehicle) << " h";
    return oss.str();
}

std::vector<Vehicle*> filter_vehicles(
        std::vector<Vehicle*>::const_iterator vehicles_begin,
        std::vector<Vehicle*>::const_iterator vehicles_end,
        std::function<bool(const Vehicle&)> predicate) {

    std::vector<Vehicle*> vehicles_filtered;
    std::copy_if(vehicles_begin, vehicles_end, std::back_inserter(vehicles_filtered),
                 [&predicate](const Vehicle* vehicle_ptr) { return predicate(*vehicle_ptr); });
    return vehicles_filtered;
}

void Driver::assign_vehicle(std::unique_ptr<Vehicle> vehicle_ptr){
    vehicle_ptr_ = std::move(vehicle_ptr);
}

std::string to_string(const Driver& driver) {
    std::ostringstream os;
    Vehicle* vehicle_ptr = driver.get_vehicle();
    os << driver.get_name() << " : " << '[' <<
       ((vehicle_ptr == nullptr) ? "no vehicle" : to_string(*vehicle_ptr)) << ']';
    return os.str();
}

Driver& Driver::operator=(Driver&& other){
    name_ = other.name_;
    vehicle_ptr_ = std::move(other.vehicle_ptr_);
    gender_ = other.gender_;
    return *this;
}

void assign_vehicle_to_driver(std::vector<std::unique_ptr<Vehicle>>& vehicles, Driver& owner){
    std::size_t n = vehicles.size();
    if(n == 0)
        owner.assign_vehicle(nullptr);
    else {
        owner.assign_vehicle(std::move(vehicles[n - 1]));
        vehicles.erase(vehicles.end() - 1);
    }
}
