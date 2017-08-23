// ==============================================================================
//  KratosShapeOptimizationApplication
//
//  License:         BSD License
//                   license: ShapeOptimizationApplication/license.txt
//
//  Main authors:    Fusseder Martin   
//                   martin.fusseder@tum.de
//	TODO: include this response type into the adjoint workflow
// ==============================================================================

#ifndef REWORK_STRAIN_ENERGY_RESPONSE_FUNCTION_H
#define REWORK_STRAIN_ENERGY_RESPONSE_FUNCTION_H

// ------------------------------------------------------------------------------
// System includes
// ------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <algorithm>

// ------------------------------------------------------------------------------
// External includes
// ------------------------------------------------------------------------------
#include <boost/python.hpp>
#include <boost/numeric/ublas/io.hpp>

// ------------------------------------------------------------------------------
// Project includes
// ------------------------------------------------------------------------------
#include "../../kratos/includes/define.h"
#include "../../kratos/processes/process.h"
#include "../../kratos/includes/node.h"
#include "../../kratos/includes/element.h"
#include "../../kratos/includes/model_part.h"
#include "../../kratos/includes/kratos_flags.h"
#include "structural_response_function.h"


#include "includes/kratos_parameters.h"
#include "includes/ublas_interface.h"
#include "utilities/openmp_utils.h"

// ==============================================================================

namespace Kratos
{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/// Short class definition.
/** Detail class definition.

 */

//template<class TDenseSpace>

class ReworkStrainEnergyResponseFunction : StructuralResponseFunction
{
public:
	///@name Type Definitions
	///@{

	typedef StructuralResponseFunction BaseType;
	typedef array_1d<double, 3> array_3d;

	

	/// Pointer definition of ReworkStrainEnergyResponseFunction
	KRATOS_CLASS_POINTER_DEFINITION(ReworkStrainEnergyResponseFunction);

	///@}
	///@name Life Cycle
	///@{

	/// Default constructor.
	ReworkStrainEnergyResponseFunction(ModelPart& model_part, Parameters& responseSettings)
	: StructuralResponseFunction(model_part, responseSettings)
	{
		// Set gradient mode
		std::string gradientMode = responseSettings["gradient_mode"].GetString();

		// Mode 1: semi-analytic sensitivities
		if (gradientMode.compare("semi_analytic") == 0)
		{
			mGradientMode = 1;
			double delta = responseSettings["step_size"].GetDouble();
			mDelta = delta;
		}
		else
			KRATOS_THROW_ERROR(std::invalid_argument, "Specified gradient_mode not recognized. The only option is: semi_analytic. Specified gradient_mode: ", gradientMode);


		// Initialize member variables to NULL
		m_initial_value = 0.0;
		m_initial_value_defined = false;
		m_current_response_value = 0.0;

	}

	/// Destructor.
	virtual ~ReworkStrainEnergyResponseFunction()
	{
	}

	///@}
	///@name Operators
	///@{

	///@}
	///@name Operations
	///@{

	void Initialize() override
	{
		KRATOS_TRY;

		BaseType::Initialize();

		KRATOS_CATCH("");
	}

	// ==============================================================================
	double CalculateValue(ModelPart& rModelPart) override
	{
		KRATOS_TRY;

		ModelPart& r_model_part = this->GetModelPart();
		ProcessInfo &CurrentProcessInfo = r_model_part.GetProcessInfo();
		m_current_response_value = 0.0;

		// Sum all elemental strain energy values calculated as: W_e = u_e^T K_e u_e
		for (ModelPart::ElementIterator elem_i = r_model_part.ElementsBegin(); elem_i != r_model_part.ElementsEnd(); ++elem_i)
		{
			Matrix LHS;
			Vector RHS;
			Vector u;

			// Get state solution relevant for energy calculation
			elem_i->GetValuesVector(u,0);

			elem_i->CalculateLocalSystem(LHS,RHS,CurrentProcessInfo);

			// Compute strain energy
			m_current_response_value += 0.5 * inner_prod(u,prod(LHS,u));
		}	

		// Set initial value if not done yet
		if(!m_initial_value_defined)
		{
			m_initial_value = m_current_response_value;
			m_initial_value_defined = true;
		}

		return m_current_response_value;

		KRATOS_CATCH("");
	}
	// --------------------------------------------------------------------------
	double GetInitialValue()
	{
		KRATOS_TRY;

		if(!m_initial_value_defined)
			KRATOS_THROW_ERROR(std::logi:error, "Initial value not yet defined! First compute it by calling \"CalculateValue()\"", m_initial_value_defined);

		return m_initial_value;

		KRATOS_CATCH("");
	}

	// --------------------------------------------------------------------------
	double GetValue()
	{
		KRATOS_TRY;

		return m_current_response_value;

		KRATOS_CATCH("");
	}

	// --------------------------------------------------------------------------
	/*boost::python::dict get_gradient()
	{
		KRATOS_TRY;

		// Dictionary to store all sensitivities along with Ids of corresponding nodes
		boost::python::dict dFdX;

		ModelPart& r_model_part = this->GetModelPart();

		// Fill dictionary with gradient information
		for (ModelPart::NodeIterator node_i = r_model_part.NodesBegin(); node_i != r_model_part.NodesEnd(); ++node_i)
			dFdX[node_i->Id()] = node_i->FastGetSolutionStepValue(LOCAL_STRESS_GRADIENT);

		return dFdX;

		KRATOS_CATCH("");
	}*/

	// ==============================================================================

	///@}
	///@name Access
	///@{

	///@}
	///@name Inquiry
	///@{

	///@}
	///@name Input and output
	///@{

	/// Turn back information as a string.
	virtual std::string Info() const
	{
		return "ReworkStrainEnergyResponseFunction";
	}

	/// Print information about this object.
	virtual void PrintInfo(std::ostream &rOStream) const
	{
		rOStream << "ReworkStrainEnergyResponseFunction";
	}

	/// Print object's data.
	virtual void PrintData(std::ostream &rOStream) const
	{
	}

	///@}
	///@name Friends
	///@{

	///@}

	// =============================================================================
	void UpdateSensitivities() override
	{
		KRATOS_TRY;

		BaseType::UpdateSensitivities();

		KRATOS_CATCH("");
	}


protected:
	///@name Protected static Member Variables
	///@{

	///@}
	///@name Protected member Variables
	///@{

	///@}
	///@name Protected Operators
	///@{

	///@}
	///@name Protected Operations
	///@{
	
	// ==============================================================================
	void CalculateSensitivityGradient(Element& rAdjointElem,
                                              const Variable<array_1d<double,3>>& rVariable,
                                              const Matrix& rDerivativesMatrix,
                                              Vector& rResponseGradient,
                                              ProcessInfo& rProcessInfo) override
    {
      	KRATOS_TRY

      	if (rResponseGradient.size() != rDerivativesMatrix.size1())
          	rResponseGradient.resize(rDerivativesMatrix.size1(), false);

		for (unsigned int k = 0; k < rResponseGradient.size(); ++k)
            rResponseGradient[k] = 0.0;

     	 KRATOS_CATCH("")
	}

	// ==============================================================================
	void CalculateSensitivityGradient(Element& rAdjointElem,
                                              const Variable<double>& rVariable,
                                              const Matrix& rDerivativesMatrix,
                                              Vector& rResponseGradient,
                                              ProcessInfo& rProcessInfo) override
    {
      	KRATOS_TRY

		if (rResponseGradient.size() != rDerivativesMatrix.size1())
          	rResponseGradient.resize(rDerivativesMatrix.size1(), false);

		for (unsigned int k = 0; k < rResponseGradient.size(); ++k)
            rResponseGradient[k] = 0.0;

        KRATOS_CATCH("")
	}

	// ==============================================================================
	void CalculateSensitivityGradient(Condition& rAdjointCondition,
                                              const Variable<array_1d<double,3>>& rVariable,
                                              const Matrix& rDerivativesMatrix,
                                              Vector& rResponseGradient,
                                              ProcessInfo& rProcessInfo) override
    {
		KRATOS_TRY;

		Vector zero_adjoint_vector;
		zero_adjoint_vector = Vector(0);

		//Condition *help_condition = rAdjointCondition; // is there a better solution?

		rAdjointCondition.GetValuesVector(zero_adjoint_vector);

		//std::cout << (" size adjoint vector = ") << zero_adjoint_vector.size() << std::endl;
		//std::cout << (" size pseudo load = ") << rDerivativesMatrix.size2() << std::endl;

		if (zero_adjoint_vector.size() != rDerivativesMatrix.size2())
			KRATOS_ERROR << "Size of adjoint vector does not fit to the size of the pseudo load!" << std::endl;

		if (rResponseGradient.size() != rDerivativesMatrix.size2())
			rResponseGradient.resize(zero_adjoint_vector.size(), false);
	
		noalias(rResponseGradient) = prod(rDerivativesMatrix, 0.5 * zero_adjoint_vector);

		KRATOS_CATCH("");
	}

	// ==============================================================================
	void CalculateSensitivityGradient(Condition& rAdjointCondition,
                                              const Variable<double>& rVariable,
                                              const Matrix& rDerivativesMatrix,
                                              Vector& rResponseGradient,
                                              ProcessInfo& rProcessInfo) override
    {
		KRATOS_TRY;

		Vector zero_adjoint_vector;

		//Condition help_condition = rAdjointCondition; // is there a better solution?

		rAdjointCondition.GetValuesVector(zero_adjoint_vector);

		if (zero_adjoint_vector.size() != rDerivativesMatrix.size2())
			KRATOS_ERROR << "Size of adjoint vector does not fit to the size of the pseudo load!" << std::endl;

		if (rResponseGradient.size() != rDerivativesMatrix.size2())
			rResponseGradient.resize(zero_adjoint_vector.size(), false);	
	
		noalias(rResponseGradient) = prod(rDerivativesMatrix, 0.5 * zero_adjoint_vector);

		KRATOS_CATCH("");
	}

	// ==============================================================================
	void GetAdjointVariables(Element& rElem, Vector& rValues) override
    {
		KRATOS_TRY;

		rElem.GetValuesVector(rValues);
		rValues *= 0.5;

		KRATOS_CATCH("");
	}

	// ==============================================================================
	void GetAdjointVariables(Condition& rCond, Vector& rValues) override
    {
		KRATOS_TRY;

		rCond.GetValuesVector(rValues);
		rValues *= 0.5;

		KRATOS_CATCH("");
	}

	// ==============================================================================

	///@}
	///@name Protected  Access
	///@{

	///@}
	///@name Protected Inquiry
	///@{

	///@}
	///@name Protected LifeCycle
	///@{

	///@}

private:
	///@name Static Member Variables
	///@{

	///@}
	///@name Member Variables
	///@{
	unsigned int mGradientMode;
	double m_current_response_value; 
	double mDelta;
	double m_initial_value;
	bool m_initial_value_defined;

	///@}
///@name Private Operators
	///@{

	///@}
	///@name Private Operations
	///@{

	///@}
	///@name Private  Access
	///@{

	///@}
	///@name Private Inquiry
	///@{

	///@}
	///@name Un accessible methods
	///@{

	/// Assignment operator.
	//      ReworkStrainEnergyResponseFunction& operator=(SReworkStrainEnergyResponseFunction const& rOther);

	/// Copy constructor.
	//      ReworkStrainEnergyResponseFunction(ReworkStrainEnergyResponseFunction const& rOther);

	///@}

}; // Class ReworkStrainEnergyResponseFunction

///@}

///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

///@}

} // namespace Kratos.

#endif // REWORK_STRAIN_ENERGY_RESPONSE_FUNCTION_H