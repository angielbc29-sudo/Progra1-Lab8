#include "MeatsRepository.h"
#include <stdexcept>
#include <fstream>

MeatsRepository::MeatsRepository() {
    auto data = DataLoader::LoadFromFile("meats.txt");
    data_ = std::move(data);
}

int MeatsRepository::GetAvailableQuantity(const std::string& meatType) const {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }
    return std::stoi(it->second[0]);
}

void MeatsRepository::UpdateQuantity(const std::string& meatType, int newQuantity) {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }
    it->second[0] = std::to_string(newQuantity);

    std::ofstream out("meats.txt");
    for (const auto& par : data_) {
        out << par.first << ": " << par.second[0] << "\n";
    }
}