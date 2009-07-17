#include "Query1.h"
#include "State.h"

Query1::Query1()
        : Hypothesis(ObjectMotion)
{
}

double Query1::plausibility()
{
    State* state = State::instance();
    return 0.0;
}
