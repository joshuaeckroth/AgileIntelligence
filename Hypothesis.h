#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

enum Requires {ObjectMotion};

class Hypothesis
{
public:
    Hypothesis(Requires _requires);
    virtual double plausibility();

private:
    Requires requires;
};

#endif // HYPOTHESIS_H
