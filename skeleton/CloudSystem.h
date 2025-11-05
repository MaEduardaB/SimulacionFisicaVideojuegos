#pragma once
#include <vector>
#include <random>
#include "Clouds.h"

class CloudSystem {
public:
    CloudSystem(float minX, float maxX, float minZ, float maxZ);
    ~CloudSystem();

    void update(double t, const Vector3& playerPos);
    void clear();

private:
    void spawnCloudAbove(float playerY);
    void removeBelow(float playerY);

    std::vector<Clouds*> _clouds;
    std::mt19937 _mt;

    float _minX, _maxX;
    float _minZ, _maxZ;
    std::uniform_real_distribution<float> _randX, _randZ, _randSize, _randOffset;

    float _spawnTimer = 0.0f;
};
