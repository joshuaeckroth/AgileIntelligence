#include "State.h"

State* State::pinstance = 0;

State::State()
{}

State* State::instance()
{
    if(!pinstance)
        pinstance = new State;
    return pinstance;
}

void State::setQuery(Hypothesis* _query)
{
    query = _query;
}

void State::addAlternativeHypothesis(Hypothesis* h)
{
    alternatives.push_back(h);
}
