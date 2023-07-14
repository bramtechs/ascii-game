#include <memory>
#include <curses.h>

#include "collision.hpp"
#include "common.hpp"
#include "entity.hpp"
#include "input.hpp"
#include "player.hpp"
#include "stats.hpp"

using namespace std;

static Player* instance = nullptr;

Player::Player(Point pos) : Entity(pos, CHARACTER, 1)
{
    instance = this;
}

Player& Player::get()
{
    return *instance;
}

void Player::draw(Point& camera)
{
    static Point lastPos = pos;
    static Point lastCamera = { 0 };

    lastPos = pos;
    lastCamera = camera;

    if (isKeyPressed(Keys::STATS)) {
        while (isKeyReleased(Keys::QUIT) && isKeyReleased(Keys::STATS)) {
            erase();
            drawStatWin();
        }
        timeout(30);
    }

    int CAMERA_PADDING = std::max(WIDTH / 3, HEIGHT / 3);

    // PLAYER MOVEMENT
    if (isKeyPressed(Keys::UP)) {
        if (pos.y - CAMERA_PADDING <= 0 && camera.y > 0) {
            camera.y--;
        } else {
            pos.y--;
        }
    }
    if (isKeyPressed(Keys::DOWN)) {
        if (pos.y + CAMERA_PADDING >= HEIGHT) {
            camera.y++;
        } else {
            pos.y++;
        }
    }
    if (isKeyPressed(Keys::RIGHT)) {
        if (pos.x + CAMERA_PADDING >= WIDTH) {
            camera.x++;
        } else {
            pos.x++;
        }
    }
    if (isKeyPressed(Keys::LEFT)) {
        if (pos.x - CAMERA_PADDING <= 0 && camera.x > 0) {
            camera.x--;
        } else {
            pos.x--;
        }
    }

    if ((lastCamera.x != camera.y || lastCamera.x != camera.x) || (lastPos.y != pos.y || lastPos.x != pos.x)) {
        if (colCheck(camera.y + pos.y, camera.x + pos.x) || (pos.y < 0 || pos.x < 0)) {
            pos = lastPos;
            camera = lastCamera;
        }
    }

    Entity::draw(camera);
}
