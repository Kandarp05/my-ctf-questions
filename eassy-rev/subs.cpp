#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>

// Function to generate a random substitution table
std::unordered_map<char, char> generateSubstitutionTable() {
    // Define the character set
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}_";

    // Create a shuffled version of the character set
    std::string shuffledCharacters = characters;
    std::shuffle(shuffledCharacters.begin(), shuffledCharacters.end(), std::mt19937(std::random_device{}()));

    // Build the substitution table
    std::unordered_map<char, char> substitutionTable;
    for (size_t i = 0; i < characters.size(); ++i) {
        substitutionTable[characters[i]] = shuffledCharacters[i];
    }

    return substitutionTable;
}

// Function to print the substitution table
void printSubstitutionTable(const std::unordered_map<char, char>& table) {
    for (const auto& pair : table) {
        std::cout << "'" << pair.first << "' -> '" << pair.second << "'" << std::endl;
    }
}

int main() {
    // Generate the substitution table
    std::unordered_map<char, char> substitutionTable = generateSubstitutionTable();

    // Print the substitution table
    std::cout << "Substitution Table:" << std::endl;
    printSubstitutionTable(substitutionTable);

    return 0;
}