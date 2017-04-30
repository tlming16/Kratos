//
//   Project Name:        KratosConstitutiveModelsApplication $
//   Created by:          $Author:                JMCarbonell $
//   Last modified by:    $Co-Author:                         $
//   Date:                $Date:                   April 2017 $
//   Revision:            $Revision:                      0.0 $
//
//

#if !defined(KRATOS_YIELD_CRITERION_H_INCLUDED )
#define  KRATOS_YIELD_CRITERION_H_INCLUDED

// System includes

// External includes

// Project includes
#include "custom_models/plasticity_models/hardening_laws/hardening_law.hpp"
#include "custom_utilities/constitutive_model_utilities.hpp"

namespace Kratos
{
  ///@addtogroup ConstitutiveModelsApplication
  ///@{

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
  template<class THardeningLaw>
  class KRATOS_API(CONSTITUTIVE_MODELS_APPLICATION) YieldCriterion
  {    
  public:
    
    ///@name Type Definitions
    ///@{

    typedef ConstitutiveModelData::MatrixType                          MatrixType;
    typedef ConstitutiveModelData::VectorType                          VectorType;
    typedef ConstitutiveModelData::ModelData                        ModelDataType;
    typedef ConstitutiveModelData::MaterialData                  MaterialDataType;
    
    typedef THardeningLaw                                        HardeningLawType;
    typedef typename THardeningLaw::PlasticDataType               PlasticDataType;   
    typedef typename THardeningLaw::InternalVariablesType   InternalVariablesType;
    
    /// Pointer definition of YieldCriterion
    KRATOS_CLASS_POINTER_DEFINITION( YieldCriterion );

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    YieldCriterion() {}

    /// Copy constructor.
    YieldCriterion(YieldCriterion const& rOther) : mHardeningLaw(rOther.mHardeningLaw) {}

    /// Assignment operator.
    YieldCriterion& operator=(YieldCriterion const& rOther)
    {
      mHardeningLaw = rOther.mHardeningLaw;
      return *this;
    }
    
    /// Clone.
    virtual YieldCriterion::Pointer Clone() const
    {
      return (YieldCriterion<THardeningLaw>::Pointer(new YieldCriterion(*this)));
    }

    /// Destructor.
    virtual ~YieldCriterion() {}


    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{

    /**
     * Calculate Yield Condition
     */

    virtual double& CalculateYieldCondition(const PlasticDataType& rVariables, double & rYieldCondition)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rYieldCondition;
	
      KRATOS_CATCH(" ")
    }

    /**
     * Calculate Yield Condition derivative
     */
      
    virtual double& CalculateDeltaYieldCondition(const PlasticDataType& rVariables, double & rDeltaYieldCondition)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rDeltaYieldCondition;
	
      KRATOS_CATCH(" ")
    }
      
    /**
     * Calculate State Function
     */
    
    virtual double& CalculateStateFunction(const PlasticDataType& rVariables, double & rStateFunction)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rStateFunction;
	
      KRATOS_CATCH(" ")
    }

    /**
     * Calculate State Function derivative
     */

    virtual double& CalculateDeltaStateFunction(const PlasticDataType& rVariables, double & rDeltaStateFunction)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rDeltaStateFunction;
	
      KRATOS_CATCH(" ")
    }

    /**
     * Calculate Plastic Dissipation
     */
      
    virtual double& CalculatePlasticDissipation(const PlasticDataType& rVariables, double & rPlasticDissipation)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rPlasticDissipation;
	
      KRATOS_CATCH(" ")
    }
    
    /**
     * Calculate Plastic Dissipation derivative
     */
 
    virtual double& CalculateDeltaPlasticDissipation(const PlasticDataType& rVariables, double & rDeltaPlasticDissipation)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rDeltaPlasticDissipation;
	
      KRATOS_CATCH(" ")
    }

    /**
     * Calculate Implex Plastic Dissipation
     */

    virtual double& CalculateImplexPlasticDissipation(const PlasticDataType& rVariables, double & rPlasticDissipation)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rPlasticDissipation;
	
      KRATOS_CATCH(" ")
    }

    /**
     * Calculate Implex Plastic Dissipation derivative
     */
    
    virtual double& CalculateImplexDeltaPlasticDissipation(const PlasticDataType& rVariables, double & rDeltaPlasticDissipation)
    {
      KRATOS_TRY
	
      KRATOS_ERROR << "calling the YieldCriterion base class ... illegal operation" << std::endl;	

      return rDeltaPlasticDissipation;
	
      KRATOS_CATCH(" ")
    }


    ///@}
    ///@name Access
    ///@{

    HardeningLawType& GetHardeningLaw() { return mHardeningLaw; };
    
    ///@}
    ///@name Inquiry
    ///@{


    ///@}
    ///@name Input and output
    ///@{

    
    /// Turn back information as a string.
    virtual std::string Info() const
    {
      std::stringstream buffer;
      buffer << "YieldCriterion" ;
      return buffer.str();
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const
    {
      rOStream << "YieldCriterion";
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const
    {
      rOStream << "YieldCriterion Data";
    }


    ///@}
    ///@name Friends
    ///@{


    ///@}

  protected:
    ///@name Protected static Member Variables
    ///@{


    ///@}
    ///@name Protected member Variables
    ///@{
	
    HardeningLawType mHardeningLaw;
    
    ///@}
    ///@name Protected Operators
    ///@{


    ///@}
    ///@name Protected Operations
    ///@{


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
    ///@name Serialization
    ///@{
    friend class Serializer;


    virtual void save(Serializer& rSerializer) const
    {
      rSerializer.save("mpHardeningLaw", mHardeningLaw);
    }

    virtual void load(Serializer& rSerializer)
    {
      rSerializer.load("mpHardeningLaw", mHardeningLaw);
    }

    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{

    ///@}

  }; // Class YieldCriterion

  ///@}

  ///@name Type Definitions
  ///@{


  ///@}
  ///@name Input and output
  ///@{


  ///@}

  ///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_YIELD_CRITERION_H_INCLUDED  defined 

