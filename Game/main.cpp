#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameEvent.h"
#include <fstream>
#include <iostream>

enum class GameState { Menu, Playing, Paused, Exiting };

int main() 
{
    // Initialise la scène
    Scene scene;

    //Initialise le Score
    int Score = 0;
    std::string Scoremax;
    std::string LastScore;
    std::string pseudo1;
    std::string pseudo2;
    std::string pseudo;

    //score enregistré dans un fichier txt
    std::fstream monFlux("assets/scores.txt");  //On ouvre le fichier

    if (monFlux)  //On teste si tout est OK
    {
        std::string txt;
        monFlux >> pseudo1;
        monFlux >> txt;
        monFlux >> Scoremax;

        std::string txt2;
        monFlux >> pseudo2;
        monFlux >> txt2;
        monFlux >> LastScore;

        monFlux.close();
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    // Crée une fenêtre
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Highway Racing");
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // Charge l'image de fond
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/Highway.png")) {
        // Gestion de l'erreur si le chargement de l'image échoue
        return 1;
    }

    // Initialise les images de fond
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    std::pair<sf::Sprite, sf::Sprite> backgroundSprites = initBackground(windowHeight, windowWidth, backgroundSprite1, backgroundSprite2, backgroundTexture);

    // Initialise le joueur et un vecteur d'ennemis
    GameObject* player = scene.CreateMainGameObject("Player", windowWidth / 2 - 75.f, windowHeight / 2 - 100.f, 1.0f, 1.0f, sf::Color::White, "assets/sprite_perso.png");
    std::vector<GameObject*> enemies = generateEntities(windowHeight, scene);

    // Variables pour suivre l'état des touches du joueur
    bool forwardPressed = false, backwardPressed = false, leftPressed = false, rightPressed = false;

    // Initialise des Horloges pour le joueur, les ennemis et le fond d'écran
    static sf::Clock clock;
    static sf::Clock clockEnemy;
    static sf::Clock clockBg;

    // Charge la musique de fond
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/background_music.ogg")) {
        // Gestion de l'erreur si le chargement de la musique échoue
        return 1;
    }
    // Charge le son du bouton
    sf::SoundBuffer buttonSoundBuffer;
    if (!buttonSoundBuffer.loadFromFile("assets/button_click.wav")) {
        // Gestion de l'erreur si le chargement du son échoue
        return 1;
    }
    // Charge le son de la pause
    sf::SoundBuffer pauseSoundBuffer;
    if (!pauseSoundBuffer.loadFromFile("assets/pause_sound.wav")) {
        // Gestion de l'erreur si le chargement du son échoue
        return 1;
    }

    sf::Sound pauseSound;
    pauseSound.setBuffer(pauseSoundBuffer);
    sf::Sound buttonSound;
    buttonSound.setBuffer(buttonSoundBuffer);

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50);
    backgroundMusic.play();

    // Charge la police de caractères
    sf::Font font;
    if (!font.loadFromFile("assets/Arial.ttf")) {
        return 1;
    }

    // Crée les textes pour les boutons du menu
    sf::Text playText("JOUER", font, 50);
    sf::Text optionsText("OPTIONS", font, 50);
    sf::Text quitText("QUITTER", font, 50);

    // Crée un texte pour le menu de pause
    sf::Text textPaused("JEU EN PAUSE", font, 50);
    sf::Text optionPaused("Options", font, 50);
    sf::Text resumeText("Continuer", font, 50);
    sf::Text quitGameText("Quitter", font, 50);

    textPaused.setFillColor(sf::Color::White);
    resumeText.setFillColor(sf::Color::White);
    quitGameText.setFillColor(sf::Color::White);

    textPaused.setPosition(windowWidth / 2 - textPaused.getGlobalBounds().width / 2, 100);
    resumeText.setPosition(windowWidth / 2 - resumeText.getGlobalBounds().width / 2, 300);
    optionPaused.setPosition(windowWidth / 2 - quitGameText.getGlobalBounds().width / 2, 400);
    quitGameText.setPosition(windowWidth / 2 - quitGameText.getGlobalBounds().width / 2, 500);

    // Configure les couleurs et positions des textes
    playText.setFillColor(sf::Color::White);
    optionsText.setFillColor(sf::Color::White);
    quitText.setFillColor(sf::Color::White);

    playText.setPosition(windowWidth / 2 - playText.getGlobalBounds().width / 2, 300);
    optionsText.setPosition(windowWidth / 2 - optionsText.getGlobalBounds().width / 2, 400);
    quitText.setPosition(windowWidth / 2 - quitText.getGlobalBounds().width / 2, 500);

    //Texte du Score
    sf::Text ScoreText("Meilleur Score :", font, 40);
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setPosition(windowWidth / 3.10f - ScoreText.getGlobalBounds().width / 2, 65);

    sf::Text ScoreText2(Scoremax, font, 40);
    ScoreText2.setFillColor(sf::Color::White);
    ScoreText2.setPosition(windowWidth / 2.3f - ScoreText2.getGlobalBounds().width / 2, 65);

    sf::Text ScoreText3("Dernier Score :", font, 40);
    ScoreText3.setFillColor(sf::Color::White);
    ScoreText3.setPosition(windowWidth / 1.60f - ScoreText.getGlobalBounds().width / 2, 65);

    sf::Text ScoreText4(LastScore, font, 40);
    ScoreText4.setFillColor(sf::Color::White);
    ScoreText4.setPosition(windowWidth / 1.35f - ScoreText2.getGlobalBounds().width / 2, 65);

    // Cadre autour du menu
    sf::RectangleShape menuFrame;
    menuFrame.setSize(sf::Vector2f(windowWidth - 600, 500)); // Ajustez la taille selon vos besoins
    menuFrame.setFillColor(sf::Color(10, 10, 10, 500)); // Couleur noire transparente
    menuFrame.setPosition(300, 200); // Position du cadre autour du menu

    // État initial du jeu
    GameState gameState = GameState::Menu;

    // Ajoutez une variable pour gérer l'état de pause
    bool isPaused = false;

    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (gameState == GameState::Menu) {
                // Si l'utilisateur clique
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    if (playText.getGlobalBounds().contains(mousePos)) {
                        // Joue le son du bouton
                        buttonSound.play();
                        gameState = GameState::Playing;
                        backgroundMusic.play();
                    }
                    else if (optionsText.getGlobalBounds().contains(mousePos)) {
                        // Gérez les options ici
                    }
                    else if (quitText.getGlobalBounds().contains(mousePos)) {
                        gameState = GameState::Exiting;
                    }
                }
            }
            else if (gameState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::P) {
                        isPaused = !isPaused;
                        // Joue le son de la pause
                        pauseSound.play();
                        if (isPaused) {
                            gameState = GameState::Paused;
                        }
                    }
                }

                if (!isPaused) {
                    playerMovementDetection(event, &window, forwardPressed, backwardPressed, leftPressed, rightPressed, player);
                }
            }
            else if (gameState == GameState::Paused) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    if (resumeText.getGlobalBounds().contains(mousePos)) {
                        isPaused = false;
                        gameState = GameState::Playing;
                    }
                    else if (quitGameText.getGlobalBounds().contains(mousePos)) {
                        gameState = GameState::Exiting;
                    }
                }
            }
        }

        // Gestion du temps pour le joueur et les ennemis
        sf::Time deltaTime = clock.restart();
        if (!isPaused) {
            playerMovement(deltaTime, forwardPressed, backwardPressed, leftPressed, rightPressed, windowHeight, windowWidth, player);
        }

        sf::Time elapsedTime = clockEnemy.getElapsedTime();
        sf::Time deltaEnemy = clockEnemy.restart();
        if (!isPaused) {
            enemiesMovement(elapsedTime, deltaEnemy, enemies);
            enemiesReset(windowHeight, enemies);
            if (ScoreActualizer(windowHeight, enemies) == 1)
            {
                Score += 1;
            }
            if (checkCollision(player, enemies) == 1)
            {
            }
        }

        // Gestion du fond d'écran
        sf::Time elapsedTimeBg = clockBg.getElapsedTime();
        sf::Time deltaBg = clockBg.restart();
        if (!isPaused) {
            backgroundMovement(windowHeight, elapsedTimeBg, deltaBg, backgroundSprite1, backgroundSprite2);
        }

        // Mise à jour des rendus à l'écran
        scene.Update();
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite2);
        window.draw(backgroundSprite1);

        if (gameState == GameState::Playing) {
            scene.Render(&window);
            //window.draw(ScoreText2);
        }
        else if (isPaused) {
            // Affichage du menu de pause
            window.draw(menuFrame);
            window.draw(textPaused);
            window.draw(resumeText);
            window.draw(optionPaused);
            window.draw(quitGameText);
        }
        else if (gameState == GameState::Menu) {
            // Affichage du cadre et des boutons du menu
            window.draw(menuFrame);
            window.draw(playText);
            window.draw(optionsText);
            window.draw(quitText);
            window.draw(ScoreText);
            window.draw(ScoreText2);
            window.draw(ScoreText3);
            window.draw(ScoreText4);
            Score = 0;
        }

        window.display();

        if (gameState == GameState::Exiting) {
            window.close();
        }
    }

    //score enregistré dans un fichier txt
    monFlux.open("assets/scores.txt");

    if (monFlux)  //On teste si tout est OK
    {
        //demande le pseudo du joueur si le score est superieur a 1
        if (Score > 1)
        {
            std::cout << "Quel est le pseudo du joueur ? ";
            std::cin >> pseudo;
        }

        //variable pour le calcul de la position du curseur
        int taille = pseudo1.size();
        int taille2 = Scoremax.size();
        int num = stoi(Scoremax);
        
        //ecriture du/des scores
        if (Score > num)
        {
            monFlux << pseudo << " : " << Score << std::endl;
            monFlux << pseudo << " : " << Score << std::endl;
        }
        else if (Score < num)
        {
            int nb_char = 4 + taille + taille2;
            monFlux.seekp(nb_char, std::ios::beg);
            monFlux << pseudo << " : " << Score << std::endl;
        }
        else if (Score == 0);
        {
            int nb_char = 4 + taille + taille2;
            monFlux.seekp(nb_char, std::ios::beg);
            monFlux << pseudo2 << " : " << LastScore << std::endl;
        }
        monFlux.close();

    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    // Arrête la musique de fond
    backgroundMusic.stop();

    return 0;
}
