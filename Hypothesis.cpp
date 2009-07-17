#include "Hypothesis.h"

Hypothesis::Hypothesis(Requires _requires)
{
    requires = _requires;
}

double Hypothesis::plausibility()
{
    return 0.0;
}
