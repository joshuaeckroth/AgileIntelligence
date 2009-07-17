#ifndef STATE_H
#define STATE_H

#include "Hypothesis.h"
#include <vector>

class State
{
public:
    static State* instance();
    void setQuery(Hypothesis* _query);
    void addAlternativeHypothesis(Hypothesis* h);

private:
    State();
    static State* pinstance;
    Hypothesis* query;
    std::vector<Hypothesis*> alternatives;
};

#endif // STATE_H
