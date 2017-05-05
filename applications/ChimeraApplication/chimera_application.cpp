//
// ==============================================================================
//  ChimeraApplication
//
//  License:         BSD License
//                   license: ChimeraApplication/license.txt
//
//  Main authors:    Aditya Ghantasala, https://github.com/adityaghantasala
//                   Navaneeth K Narayanan
//
// ==============================================================================

// System includes


// External includes


// Project includes
#include "chimera_application.h"
#include "chimera_application_variables.h"


namespace Kratos {

KratosChimeraApplication::KratosChimeraApplication() {}

void KratosChimeraApplication::Register() {
 	// calling base class register to register Kratos components
 	KratosApplication::Register();
 	std::cout << "Initializing KratosChimeraApplication... " << std::endl;

  KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( CHIM_NEUMANN_COND )
   KRATOS_REGISTER_VARIABLE(MPC_POINTER);


}
}  // namespace Kratos.