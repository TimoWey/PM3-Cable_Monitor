#ifndef GAUGE_WITH_VALUES_HPP
#define GAUGE_WITH_VALUES_HPP

#include <gui_generated/containers/Gauge_with_ValuesBase.hpp>

class Gauge_with_Values : public Gauge_with_ValuesBase
{
public:
    Gauge_with_Values();
    virtual ~Gauge_with_Values() {}

    virtual void initialize();
protected:
};

#endif // GAUGE_WITH_VALUES_HPP
