#ifndef CONFIGURATION_CONTAINER_HPP
#define CONFIGURATION_CONTAINER_HPP

#include <gui_generated/containers/Configuration_ContainerBase.hpp>

class Configuration_Container : public Configuration_ContainerBase
{
public:
    Configuration_Container();
    virtual ~Configuration_Container() {}

    virtual void initialize();
    void update_Container();

protected:

};

#endif // CONFIGURATION_CONTAINER_HPP
