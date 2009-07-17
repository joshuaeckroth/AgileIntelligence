#include "HypothesisObjectInMotion.h"
#include "State.h"

HypothesisObjectInMotion::HypothesisObjectInMotion()
        : Hypothesis(ObjectMotion)
{
}

double HypothesisObjectInMotion::plausibility()
{
    State* state = State::instance();
    return 0.0;
}
