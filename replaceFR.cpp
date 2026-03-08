#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    const std::string source_path = "francais_seulement.json";
    const std::string target_path = "LocalizationPack.json";
    const std::string output_path = "LocalizationPack_final.json";
    const std::string pattern = "\"frFR\":";

    std::vector<std::string> source_entries;
    std::string line;

    // 1. Charger toutes les nouvelles traductions
    std::ifstream source_file(source_path);
    if (!source_file) {
        std::cerr << "Erreur: Impossible d'ouvrir " << source_path << std::endl;
        return 1;
    }
    while (std::getline(source_file, line)) {
        if (line.find(pattern) != std::string::npos) {
            source_entries.push_back(line);
        }
    }
    source_file.close();

    // 2. Traitement du fichier cible
    std::ifstream target_file(target_path);
    std::ofstream output_file(output_path);
    
    int current_line_num = 0;
    size_t source_ptr = 0;
    int first_error_line = -1;
    std::string first_error_content = "";

    while (std::getline(target_file, line)) {
        current_line_num++;
        
        if (line.find(pattern) != std::string::npos) {
            if (source_ptr < source_entries.size()) {
                output_file << source_entries[source_ptr] << "\n";
                source_ptr++;
            } else {
                // On a trouvé une ligne à remplacer dans la cible, 
                // mais on n'a plus rien dans la source !
                if (first_error_line == -1) {
                    first_error_line = current_line_num;
                    first_error_content = line;
                }
                output_file << line << "\n"; // On garde l'original par sécurité
            }
        } else {
            output_file << line << "\n";
        }
    }

    target_file.close();
    output_file.close();

    // 3. Analyse des résultats et rapport de désynchronisation
    if (first_error_line != -1) {
        std::cerr << "\n--- ERREUR DE DÉSYNCHRONISATION ---" << std::endl;
        std::cerr << "Le fichier CIBLE contient PLUS d'entrées que la SOURCE." << std::endl;
        std::cerr << "Première anomalie à la LIGNE " << first_error_line << " du pack global." << std::endl;
        std::cerr << "Contenu ignoré : " << first_error_content << std::endl;
        std::cerr << "Nombre total de traductions injectées : " << source_ptr << std::endl;
        fs::remove(output_path); // On supprime le fichier raté
        return 1;
    } 
    
    if (source_ptr < source_entries.size()) {
        std::cerr << "\n--- ERREUR DE DÉSYNCHRONISATION ---" << std::endl;
        std::cerr << "Le fichier SOURCE contient PLUS d'entrées que la CIBLE." << std::endl;
        std::cerr << "Il reste " << (source_entries.size() - source_ptr) << " traductions non utilisées." << std::endl;
        std::cerr << "La dernière injection a eu lieu avant la fin du fichier cible." << std::endl;
        fs::remove(output_path);
        return 1;
    }

    // 4. Succès
    try {
        fs::rename(output_path, target_path);
        std::cout << "Succès ! " << source_ptr << " lignes synchronisées parfaitement." << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Erreur finale : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
