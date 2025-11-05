#include "CloudSystem.h"
#include <limits>
#include "RenderUtils.hpp"
#include <algorithm>

CloudSystem::CloudSystem(float minX, float maxX, float minZ, float maxZ)
    : _minX(minX), _maxX(maxX), _minZ(minZ), _maxZ(maxZ),
    _randX(minX, maxX), _randZ(minZ, maxZ),
    _randSize(5.0f, 20.0f), _randOffset(-2.0f, 2.0f)
{
    std::random_device rd;
    _mt.seed(rd());
}

CloudSystem::~CloudSystem()
{
    clear();
}

void CloudSystem::update(double t, const Vector3& playerPos)
{
    _spawnTimer += (float)t;

    float spawnRate = max(0.5f, 3.0f - (float)playerPos.y * 0.001f);
    if (_spawnTimer > spawnRate) {
        int newClouds = min(5, (int)(_clouds.size() / 10 + 2));
        for (int i = 0; i < newClouds; ++i)
            spawnCloudAbove(playerPos.y);
        _spawnTimer = 0.0f;
    }

    for (auto* c : _clouds) {
        Vector3 pos = c->getPos();
        pos.x += _randOffset(_mt) * 0.1f * (float)t * 0.001f;
        pos.z += _randOffset(_mt) * 0.1f * (float)t * 0.001f;
        c->setPos(pos);
    }

    removeBelow(playerPos.y);
}

void CloudSystem::spawnCloudAbove(float playerY)
{
    float x = _randX(_mt);
    float z = _randZ(_mt);
    float y = playerY + 200.0f + _randSize(_mt);
    float size = _randSize(_mt);

    Clouds* cl = new Clouds(Vector3(x, y, z), Vector4(1, 1, 1, 1), size);
    _clouds.push_back(cl);
}

void CloudSystem::removeBelow(float playerY)
{
    _clouds.erase(
        std::remove_if(_clouds.begin(), _clouds.end(),
            [playerY](Clouds* c) {
                if (c->getPos().y < playerY - 100.0f) { 
                    delete c;
                    return true;
                }
                return false;
            }),
        _clouds.end());
}

void CloudSystem::clear()
{
    for (auto* c : _clouds)
        delete c;
    _clouds.clear();
}