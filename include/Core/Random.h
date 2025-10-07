#pragma once
#include <random>

namespace Core
{
class Random
{
public:
    static int getInt(int minInclusive, int maxInclusive)
    {
        std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);
        return dist(getEngine());
    }

    static float getFloat(float minInclusive, float maxInclusive)
    {
        std::uniform_real_distribution<float> dist(minInclusive, maxInclusive);
        return dist(getEngine());
    }

private:
    static std::mt19937& getEngine()
    {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        return engine;
    }
};
}
