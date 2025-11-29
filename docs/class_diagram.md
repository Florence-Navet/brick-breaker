# Class Diagram

```mermaid
classDiagram
    %% Classes principales
    class Game {
        +void run()
        -void processEvents()
        -void update(float dt)
        -void render()
        -std::vector<GameObject*> objects
        -InputManager input
        -CollisionManager collisionManager
    }

    class GameObject {
        +Vector2f position
        +Vector2f velocity
        +float rotation
        +Vector2f size
        +ShapeType shape
        +bool visible
        +void update(float dt)
        +void draw(sf::RenderWindow &window)
        +AABB getAABB()
        +void onCollision(GameObject *other)
    }

    class AABB {
        +Vector2f min
        +Vector2f max
        +bool intersects(const AABB &other)
    }

    class InputManager {
        +void bindAction(string actionName, std::function<void()> callback)
        +void unbindAction(string actionName)
        +void handleEvent(const sf::Event &event)
        +void pollRealtime()
    }

    class GameObjectManager {
        +void add(GameObject *obj)
        +void remove(GameObject *obj)
        +void updateAll(float dt)
        +void drawAll(sf::RenderWindow &window)
        +void checkCollisions()
    }

    class CollisionManager {
        +bool checkCollision(GameObject *a, GameObject *b)
        +std::vector<std::pair<GameObject*,GameObject*>> findAllCollisions()
    }

    %% specialization exemples
    class Paddle
    class Ball
    class Brick

    %% Relations
    Game "1" -- "*" GameObject : contains
    Game "1" o-- "1" InputManager : uses
    Game "1" o-- "1" CollisionManager : uses
    GameObject "1" o-- "1" AABB : has
    GameObjectManager "1" -- "*" GameObject : manages
    CollisionManager "1" -- "*" GameObject : checks

    GameObject <|-- Paddle
    GameObject <|-- Ball
    GameObject <|-- Brick

    %% Notes
%% - GameObject provides position, rotation, velocity and size.
%% - AABB is used for simple and fast collision detection (axis-aligned bounding box).
%% - InputManager allows binding callbacks to named actions (e.g. "shoot", "explode").
```

# Explanations

- Game / GameObject: contain update and rendering logic. Objects can be either a circle or a rectangle (via shape or derived classes) and expose an AABB for collision.

- AABB: axis-aligned bounding box used for intersection tests.

- CollisionManager / GameObjectManager: help detect and manage collisions between objects.

- InputManager: centralizes listening to SFML events and binding actions to callbacks (e.g. left click -> "shoot", key 'E' -> "explode").