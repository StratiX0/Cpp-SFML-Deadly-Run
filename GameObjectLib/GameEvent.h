#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Scene.h"
#include "Components/SquareCollider.h"
#include <random>
#include <vector>
#include <SFML/Audio.hpp>
#include <string>


// Fonction permettant d'initialiser le fond d'�cran
template<typename T>
std::pair<sf::Sprite, sf::Sprite> initBackground(T windowHeight, T windowWidth, sf::Sprite& backgroundSprite1, sf::Sprite& backgroundSprite2, sf::Texture& backgroundTexture);

// Fonction permettant de g�n�rer un nombre al�atoire
template<typename T>
T randomGenerator(T a, T b);

// Fonction g�n�rant des ennemis
template<typename T>
std::vector<GameObject*> generateEntities(T windowHeight, Scene& scene);


// Fonction g�rant les contr�les du joueur
void playerMovementDetection(sf::Event event, sf::RenderWindow* window, bool& forwardPressed, bool& backwardPressed, bool& leftPressed, bool& rightPressed, GameObject* player);

// Fonction permettant au Sprite du joueur de bouger lorsqu'il appuie sur les touches d�placement
template <typename T>
void playerMovement(sf::Time deltaTime, bool forwardPressed, bool backwardPressed, bool leftPressed, bool rightPressed, T windowHeight, T windowWidth, GameObject*& player);

// Fonction permettant aux ennemis de se d�placer
void enemiesMovement(sf::Time elapsedTime, sf::Time deltaEnemy, std::vector<GameObject*>enemies);

// Fonction r�initialisant la position de l'ennemi lorsqu'il sort de l'�cran
template<typename T>
void enemiesReset(T windowHeight, std::vector<GameObject*>enemies);

// Fonction permettant de v�rifier les colisions entre le joueur et les ennemis
int checkCollision(GameObject*& player, std::vector<GameObject*>& enemies);

// Fonction permettant au fond d'�cran de bouger
template<typename T>
void backgroundMovement(T windowHeight, sf::Time elapsedTimeBg, sf::Time deltaBg, sf::Sprite& backgroundSprite1, sf::Sprite& backgroundSprite2);

#include "GameEvent.inl"
