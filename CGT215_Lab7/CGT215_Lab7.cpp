#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    // Create our window and world with gravity 0,1
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    // Create the first ball on the right
    PhysicsCircle ball1;
    ball1.setCenter(Vector2f(200, 300));
    ball1.setRadius(20);
    ball1.applyImpulse(Vector2f(5, 5));
    world.AddPhysicsBody(ball1);

    // Create the second ball on the left
    PhysicsCircle ball2;
    ball2.setCenter(Vector2f(600, 300)); // Adjusted position to the left
    ball2.setRadius(20);
    ball2.applyImpulse(Vector2f(-5, 5)); // Adjusted initial velocity
    world.AddPhysicsBody(ball2);

    // Create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create the ceiling
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Create the left wall
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    // Create the right wall
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    // Create the obstacle in the center
    PhysicsRectangle centerObstacle;
    centerObstacle.setSize(Vector2f(100, 100));
    centerObstacle.setCenter(Vector2f(400, 300));
    centerObstacle.setStatic(true);
    int bangCount = 0;

    // Set up onCollision callback for the center obstacle
    centerObstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount << endl;
        bangCount++;

        // Exit the program if the center obstacle is hit thrice
        if (bangCount >= 3) {
            exit(0);
        }
    };

    world.AddPhysicsBody(centerObstacle);

    int thudCount = 0;
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        // calculate MS since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());

        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(0, 0, 0));
        window.draw(ball1);
        window.draw(ball2);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerObstacle);
        window.display();
    }

    return 0;
}