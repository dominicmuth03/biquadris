#ifndef _EFFECTDECORATOR_
#define _EFFECTDECORATOR_

#include <memory>
#include "abstractboard.h"

class EffectDecorator : public AbstractBoard
{
protected:
    virtual void apply() = 0;

public:
    EffectDecorator(std::unique_ptr<AbstractBoard> component);
    virtual ~EffectDecorator();
};

#endif
