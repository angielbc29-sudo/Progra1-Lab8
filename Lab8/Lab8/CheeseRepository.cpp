#include "CheeseRepository.h"
#include <stdexcept>
#include <fstream>


CheeseRepository::CheeseRepository() {
    auto data = DataLoader::LoadFromFile("cheese.txt");
    data_ = std::move(data);
}

int CheeseRepository::GetAvailableQuantity(const std::string& cheeseType) const {
    auto it = data_.find(cheeseType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de queso desconocido: " + cheeseType);
    }
    return std::stoi(it->second[0]);
}

void CheeseRepository::UpdateQuantity(const std::string& cheeseType, int newQuantity) {
    auto it = data_.find(cheeseType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de queso desconocido: " + cheeseType);
    }
    it->second[0] = std::to_string(newQuantity);

    std::ofstream out("cheese.txt");
    for (const auto& par : data_) {
        out << par.first << ": " << par.second[0] << "\n";
    }
}