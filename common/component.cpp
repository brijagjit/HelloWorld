#include <string>
#include "component.h"

const char* componentName(Component component)
{
    switch (component)
    {
        case Component::SYSTEM:
            return "System";

        case Component::COMPONENT1:
            return "Component 1";

        case Component::COMPONENT2:
            return "Component 2";

        case Component::COMPONENT3:
            return "Component 3";
    }

    return "Unknown Component";
}
