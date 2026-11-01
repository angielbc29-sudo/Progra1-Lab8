#include "CheeseRepository.h"
#include <stdexcept>


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
}