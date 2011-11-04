#include "fluid_dynamics_application_variables.h"

namespace Kratos
{
    KRATOS_CREATE_VARIABLE(int,PATCH_INDEX)
    KRATOS_CREATE_VARIABLE(double,TAUONE)
    KRATOS_CREATE_VARIABLE(double,TAUTWO)
    KRATOS_CREATE_VARIABLE(double,Y_WALL)
//    KRATOS_CREATE_VARIABLE(double, C_SMAGORINSKY)
    KRATOS_CREATE_VARIABLE(PeriodicVariablesContainer,PERIODIC_VARIABLES)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(SUBSCALE)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(VORTICITY)
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(COARSE_VELOCITY)
}
