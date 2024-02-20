#include "GameEvent.h"

// Fonction permettant d'initialiser le fond d'écran
template<typename T>
std::pair<sf::Sprite, sf::Sprite> initBackground(T windowHeight, T windowWidth, sf::Sprite& backgroundSprite1, sf::Sprite& backgroundSprite2, sf::Texture& backgroundTexture)
{
    // Attribue une texture aux backgroundSprite 1 et 2
    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    // Positionne les sprites
    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(0, 0 - windowHeight);

    // Redimensionne les sprites de l'image de fond pour qu'ils correspondent à la taille de la fenêtre
    backgroundSprite1.setScale(static_cast<T>(windowWidth) / backgroundTexture.getSize().x, static_cast<T>(windowHeight) / backgroundTexture.getSize().y);
    backgroundSprite2.setScale(static_cast<T>(windowWidth) / backgroundTexture.getSize().x, static_cast<T>(windowHeight) / backgroundTexture.getSize().y);

    return std::make_pair(backgroundSprite1, backgroundSprite2);
}


// Fonction permettant de générer un nombre aléatoire
template<typename T>
T randomGenerator(T a, T b)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<T> distrib(a, b);
    T result = distrib(generator);

    return result;
}


// Fonction générant des ennemis
template<typename T>
std::vector<GameObject*> generateEntities(T windowHeight, Scene& scene)
{
    std::vector<GameObject*> enemyList;

    for (int i = 1; i <= 4; i++)
    {
        float column = 500.f;
        float deepness;
        std::string filePath;
        Maths::Vector2f scale;
        bool rotate = false;

        if (i <= 2)
        {
            column *= (i == 1 ? 1.0f : 1.475f);
            deepness = randomGenerator(-300.f, 0.f);
            filePath = (i == 1 ? "assets/bot1.png" : "assets/bot2.png");
            scale = (i == 1 ? Maths::Vector2f(1.f, 1.f) : Maths::Vector2f(1.15f, 1.2f));
            rotate = true;
        }
        else
        {
            column *= (i == 3 ? 1.725f : 2.225f);
            deepness = windowHeight + randomGenerator(0.f, 300.f);
            filePath = (i == 3 ? "assets/bot1.png" : "assets/bot2.png");
            scale = (i == 3 ? Maths::Vector2f(1.f, 1.f) : Maths::Vector2f(1.15f, 1.2f));
        }

        GameObject* enemy = scene.CreateMainGameObject("Enemy" + std::to_string(i), column, deepness, scale.x, scale.y, sf::Color::Red, filePath);
        if (rotate)
            enemy->SetRotation(180);
        enemyList.push_back(enemy);
    }

    return enemyList;
}


// Fonction gérant les contrôles du joueur
void playerMovementDetection(sf::Event event, sf::RenderWindow* window, bool& forwardPressed, bool& backwardPressed, bool& leftPressed, bool& rightPressed, GameObject* player)
{
    if (event.type == sf::Event::Closed) {
        window->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z) {
            forwardPressed = true;
        }

        if (event.key.code == sf::Keyboard::S) {
            backwardPressed = true;
        }

        if (event.key.code == sf::Keyboard::Q) {
            leftPressed = true;
        }

        if (event.key.code == sf::Keyboard::D) {
            rightPressed = true;      
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Z) {
            forwardPressed = false;
        }

        if (event.key.code == sf::Keyboard::S) {
            backwardPressed = false;
        }

        if (event.key.code == sf::Keyboard::Q) {
            leftPressed = false;
        }

        if (event.key.code == sf::Keyboard::D) {
            rightPressed = false;
        }
    }

    if (leftPressed)
        player->SetRotation(-5.f);
    else if (rightPressed)
        player->SetRotation(5.f);
    else
        player->SetRotation(0.f);

}


// Fonction permettant au Sprite du joueur de bouger lorsqu'il appuie sur les touches déplacement
template <typename T>
void playerMovement(sf::Time deltaTime, bool forwardPressed, bool backwardPressed, bool leftPressed, bool rightPressed, T windowHeight, T windowWidth, GameObject*& player)
{

    if (forwardPressed && player->GetPosition().GetY() > 0) {
        player->SetPosition(player->GetPosition() - Maths::Vector2f(0.f, 500.f * deltaTime.asSeconds()));
    }
    if (backwardPressed && player->GetPosition().GetY() < windowHeight - 200.f) {
        player->SetPosition(player->GetPosition() + Maths::Vector2f(0.f, 500.f * deltaTime.asSeconds()));
    }
    if (leftPressed && player->GetPosition().GetX() > 0 + windowWidth / 6.f) {
        player->SetPosition(player->GetPosition() - Maths::Vector2f(500.f * deltaTime.asSeconds(), 0.f));
    }
    if (rightPressed && player->GetPosition().GetX() < windowWidth - windowWidth / 4.25f) {
        player->SetPosition(player->GetPosition() + Maths::Vector2f(500.f * deltaTime.asSeconds(), 0.f));
    }
}


// Fonction permettant aux ennemis de se déplacer
void enemiesMovement(sf::Time elapsedTime, sf::Time deltaEnemy, std::vector<GameObject*>enemies)
{
    if (elapsedTime >= sf::milliseconds(.1f)) {
        enemies[0]->SetPosition(enemies[0]->GetPosition() + Maths::Vector2f(0.f, 500 * deltaEnemy.asSeconds()));
        enemies[1]->SetPosition(enemies[1]->GetPosition() + Maths::Vector2f(0.f, 500 * deltaEnemy.asSeconds()));
        enemies[2]->SetPosition(enemies[2]->GetPosition() - Maths::Vector2f(0.f, 500 * deltaEnemy.asSeconds()));
        enemies[3]->SetPosition(enemies[3]->GetPosition() - Maths::Vector2f(0.f, 500 * deltaEnemy.asSeconds()));
    }
}


// Fonction réinitialisant la position de l'ennemi lorsqu'il sort de l'écran
template <typename T>
void enemiesReset(T windowHeight, std::vector<GameObject*>enemies)
{
    if (enemies[0]->GetPosition().GetY() > windowHeight + 300.f) {
        enemies[0]->SetPosition(Maths::Vector2f(enemies[0]->GetPosition().GetX(), randomGenerator(-200.f, 0.f)));
    }
    if (enemies[1]->GetPosition().GetY() > windowHeight + 600.f) {
        enemies[1]->SetPosition(Maths::Vector2f(enemies[1]->GetPosition().GetX(), randomGenerator(-200.f, 0.f)));
    }
    if (enemies[2]->GetPosition().GetY() < -200.f) {
        enemies[2]->SetPosition(Maths::Vector2f(enemies[2]->GetPosition().GetX(), randomGenerator(windowHeight, windowHeight + 200.f)));
    }
    if (enemies[3]->GetPosition().GetY() < -400.f) {
        enemies[3]->SetPosition(Maths::Vector2f(enemies[3]->GetPosition().GetX(), randomGenerator(windowHeight, windowHeight + 200.f)));
    }
}


// Fonction permettant de vérifier les colisions entre le joueur et les ennemis
int checkCollision(GameObject*& player, std::vector<GameObject*>& enemies)
{
    SquareCollider* squareColliderA = player->GetComponent<SquareCollider>();
    for (int i = 0; i < enemies.size(); i++)
    {
        SquareCollider* squareColliderB = enemies[i]->GetComponent<SquareCollider>();

        if (squareColliderA && squareColliderB) {

            if (SquareCollider::IsColliding(*squareColliderA, *squareColliderB)) {
                return 1;

            }
        }
    }
    return 0;
}


// Fonction permettant au fond d'écran de bouger
template <typename T>
void backgroundMovement(T windowHeight, sf::Time elapsedTimeBg, sf::Time deltaBg, sf::Sprite& backgroundSprite1, sf::Sprite& backgroundSprite2)
{
    if (elapsedTimeBg >= sf::milliseconds(.0f)) {
        backgroundSprite1.setPosition(0, (backgroundSprite1.getPosition().y + 750.f * deltaBg.asSeconds()));
        backgroundSprite2.setPosition(0, (backgroundSprite2.getPosition().y + 750.f * deltaBg.asSeconds()));
    }

    if (backgroundSprite1.getPosition().y >= windowHeight) {
        backgroundSprite1.setPosition(0.f, 0.f - windowHeight);
    }
    if (backgroundSprite2.getPosition().y >= windowHeight) {
        backgroundSprite2.setPosition(0.f, 0.f - windowHeight);
    }
}

// Fonction permettant au score de s'actualiser
template <typename T>
int ScoreActualizer(T windowHeight, std::vector<GameObject*>enemies)
{
    if (enemies[0]->GetPosition().GetY() > windowHeight + 299.f) {
        return 1;
    }
    if (enemies[1]->GetPosition().GetY() > windowHeight + 599.f) {
        return 1;
    }
    if (enemies[2]->GetPosition().GetY() < -199.f) {
        return 1;
    }
    if (enemies[3]->GetPosition().GetY() < -399.f) {
        return 1;
    }
}


