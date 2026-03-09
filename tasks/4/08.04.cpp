#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

const std::string TARGET = "methinksitislikeaweasel";
const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const int POPULATION_SIZE = 100;
const float MUTATION_RATE = 0.05f;

int calculate_divergence(const std::string& s) {
    int divergence = 0;
    for (size_t i = 0; i < TARGET.length(); ++i) {
        if (s[i] != TARGET[i]) {
            divergence++;
        }
    }
    return divergence;
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> char_dist(0, ALPHABET.length() - 1);
    std::uniform_real_distribution<float> mutation_dist(0.0f, 1.0f);

    std::string parent = "";
    for (size_t i = 0; i < TARGET.length(); ++i) {
        parent += ALPHABET[char_dist(engine)];
    }

    int generation = 0;
    while (true) {
        int divergence = calculate_divergence(parent);
        std::cout << "Gen " << generation << ": " << parent << " (Divergence: " << divergence << ")" << std::endl;

        if (divergence == 0) {
            break;
        }

        std::vector<std::string> population;
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            std::string child = parent;
            for (size_t j = 0; j < child.length(); ++j) {
                if (mutation_dist(engine) < MUTATION_RATE) {
                    child[j] = ALPHABET[char_dist(engine)];
                }
            }
            population.push_back(child);
        }

        int best_divergence = TARGET.length() + 1;
        for (const auto& child : population) {
            int score = calculate_divergence(child);
            if (score < best_divergence) {
                best_divergence = score;
                parent = child;
            }
        }
        generation++;
    }

    return 0;
}
