#pragma once

#include <random>

namespace Utility{
float randMToN(float M, float N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) );
}
}

