#include <iostream>
#include <stdlib.h>
#include <string>
#include <limits>  // Pour std::numeric_limits

void drawGrid(int grid[7][6]);
bool playTurn(int grid[7][6], int column, int player);
bool checkWin(int grid[7][6], int player);
bool isFull(int grid[7][6]);

int main(int argc, char** argv) {
    int grid[7][6] = {};  // Grille initialisée à zéro
    std::string choix;
    std::string decision;
    int player = 1;
    drawGrid(grid);

        while (true){
                //Choix du mode de jeu
                std::cout << "\n";
                std::cout << "mode de jeu : \n 1 - Joueur_1 VS 2 \n 2 - Joueur_1 VS IA \n 3 - exit \n ";
                std::cout << "Décision -> ";
                std::cin >> decision;

                //Pour le mode J1 VS J2
        if(decision == "1"){

            while (true) {
                std::cout << "Player_" << player << ", choisissez une colonne (1-7 ou tapez 'exit' pour quitter) : ";
                std::cin >> choix;

                if (choix == "exit") {
                    break;
                }

                bool success = false;

                // Validation de l'entrée
                try {
                    int col = std::stoi(choix) - 1;  // Convertit en entier et ajuste pour être entre 0 et 6

                    if (col < 0 || col > 6) {
                        throw std::out_of_range("Colonne hors limites");
                    }

                    success = playTurn(grid, col, player);

                } catch (...) {
                    std::cout << "Entrée invalide, veuillez choisir un nombre entre 1 et 7.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                system("clear");  // Efface l'écran (Windows)

                if (!success) {
                    std::cout << "Cette colonne est pleine, choisissez une autre.\n";
                } else {
                    // Vérification de la victoire
                    if (checkWin(grid, player)) {
                        drawGrid(grid);
                        std::cout << "Le joueur " << player << " a gagné !\n";
                        break; // Sortie de la boucle de jeu
                    }

                    // Vérifie si la grille est pleine (match nul)
                    if (isFull(grid)) {
                        drawGrid(grid);
                        std::cout << "Match nul ! La grille est pleine.\n";
                        break;
                    }

                    // Changement du joueur
                    player = (player == 1) ? 2 : 1;
                }

                drawGrid(grid);
            }
        }
        else if (decision == "2") {
                //joueur 1 vs ia
                std:: cout << "option en cour de developpement" << std::endl;
            }
                    //Pour le choix de quitter le jeux
        else if(decision == "exit"){
                break;
            }
            //Choix invalide
        else{
                std::cout << "Opération invalide \n";
        }
            }
            return 0;
        }

    void drawGrid(int grid[7][6]) {
        for (int ligne = 0; ligne < 6; ligne++) {
            std::cout << "|";
            for (int col = 0; col < 7; col++) {
                if (grid[col][ligne] == 1) {
                    std::cout << "\033[31m*\033[37m";  // Rouge pour le joueur 1
                } else if (grid[col][ligne] == 2) {
                    std::cout << "\033[32m*\033[37m";  // Vert pour le joueur 2
                } else {
                    std::cout << " ";  // Espace pour une case vide
                }
                std::cout << "|";
            }
            std::cout << "\n";
        }
    }

    bool playTurn(int grid[7][6], int column, int player) {
        for (int line = 5; line >= 0; line--) {
            if (grid[column][line] == 0) {  // Vérifie si la case est vide
                grid[column][line] = player;  // Place le jeton
                return true;
            }
        }
        return false;  // Colonne pleine
    }

    bool checkWin(int grid[7][6], int player) {
        // Vérifie les lignes
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 4; col++) {
                if (grid[col][row] == player && grid[col + 1][row] == player &&
                    grid[col + 2][row] == player && grid[col + 3][row] == player) {
                    return true;
                }
            }
        }

        // Vérifie les colonnes
        for (int col = 0; col < 7; col++) {
            for (int row = 0; row < 3; row++) {
                if (grid[col][row] == player && grid[col][row + 1] == player &&
                    grid[col][row + 2] == player && grid[col][row + 3] == player) {
                    return true;
                }
            }
        }

        // Vérifie les diagonales (gauche à droite)
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 3; row++) {
                if (grid[col][row] == player && grid[col + 1][row + 1] == player &&
                    grid[col + 2][row + 2] == player && grid[col + 3][row + 3] == player) {
                    return true;
                }
            }
        }

        // Vérifie les diagonales (droite à gauche)
        for (int col = 3; col < 7; col++) {
            for (int row = 0; row < 3; row++) {
                if (grid[col][row] == player && grid[col - 1][row + 1] == player &&
                    grid[col - 2][row + 2] == player && grid[col - 3][row + 3] == player) {
                    return true;
                }
            }
        }

        return false;  // Pas de victoire
    }

    // Fonction pour vérifier si la grille est pleine
    bool isFull(int grid[7][6]) {
        for (int col = 0; col < 7; col++) {
            if (grid[col][0] == 0) {
                return false;
            }
        }
        return true;
    }
