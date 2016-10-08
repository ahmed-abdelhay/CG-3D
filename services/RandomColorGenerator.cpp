#include "RandomColorGenerator.h"
#include <random>

QColor RandomColorGenerator::generateRandomColor()
{
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_real_distribution<> randonDistribution(0, 255);

    int red = randonDistribution(mt);
    int green = randonDistribution(mt);
    int blue = randonDistribution(mt);

    QColor color(red, green, blue);
    return color;
}
