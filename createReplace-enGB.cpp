#include <iostream>
#include <fstream>
#include <string>

int main() {
    const std::string input_path = "LocalizationPack.json";
    const std::string output_path = "anglais_seulement.json";
    const std::string pattern = "\"enGB\":";

    std::ifstream input_file(input_path);
    std::ofstream output_file(output_path);

    if (!input_file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier source " << input_path << std::endl;
        return 1;
    }

    if (!output_file) {
        std::cerr << "Erreur: Impossible de créer le fichier de sortie " << output_path << std::endl;
        return 1;
    }

    std::string line;
    long line_count = 0;
    long extracted_count = 0;

    std::cout << "Extraction en cours..." << std::endl;

    while (std::getline(input_file, line)) {
        line_count++;
        // On cherche le motif "enGB": dans la ligne
        if (line.find(pattern) != std::string::npos) {
            output_file << line << "\n";
            extracted_count++;
        }
    }

    input_file.close();
    output_file.close();

    std::cout << "Terminé !" << std::endl;
    std::cout << "- Lignes analysées : " << line_count << std::endl;
    std::cout << "- Lignes enGB extraites : " << extracted_count << std::endl;
    std::cout << "- Fichier créé : " << output_path << std::endl;

    return 0;
}
