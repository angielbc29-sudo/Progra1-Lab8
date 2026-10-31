#include "HerbsRepository.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    const std::string kHerbsFile = "herbs.txt";

    std::string Trim(const std::string& s) {
        const char* ws = " \t\r\n";
        size_t start = s.find_first_not_of(ws);
        if (start == std::string::npos) {
            return "";
        }
        size_t end = s.find_last_not_of(ws);
        return s.substr(start, end - start + 1);
    }

    // Reescribe herbs.txt cambiando solo la línea de la hierba indicada.
    void SaveQuantityToFile(const std::string& herbType, int newQuantity) {
        std::ifstream in(kHerbsFile);
        if (!in.is_open()) {
            throw std::runtime_error("No se pudo abrir " + kHerbsFile);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(in, line)) {
            size_t colon = line.find(':');
            if (colon != std::string::npos && Trim(line.substr(0, colon)) == herbType) {
                line = herbType + ": " + std::to_string(newQuantity);
            }
            lines.push_back(line);
        }
        in.close();

        std::ofstream out(kHerbsFile, std::ios::trunc);
        if (!out.is_open()) {
            throw std::runtime_error("No se pudo escribir " + kHerbsFile);
        }
        for (const auto& l : lines) {
            out << l << '\n';
        }
    }
}

HerbsRepository::HerbsRepository() {
    auto data = DataLoader::LoadFromFile(kHerbsFile);
    data_ = std::move(data);
}

int HerbsRepository::GetAvailableQuantity(const std::string& herbType) const {
    auto it = data_.find(herbType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }
    return std::stoi(it->second[0]);
}

void HerbsRepository::UpdateQuantity(const std::string& herbType, int newQuantity) {
    auto it = data_.find(herbType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }
    it->second[0] = std::to_string(newQuantity);
    SaveQuantityToFile(herbType, newQuantity);
}
