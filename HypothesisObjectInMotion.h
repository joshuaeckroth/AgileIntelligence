#ifndef HYPOTHESISOBJECTINMOTION_H
#define HYPOTHESISOBJECTINMOTION_H

#include "Hypothesis.h"

class HypothesisObjectInMotion : public Hypothesis
{
public:
    HypothesisObjectInMotion();
    double plausibility();
};

#endif // HYPOTHESISOBJECTINMOTION_H
