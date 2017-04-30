//
//   Project Name:        KratosConstitutiveModelsApplication $
//   Created by:          $Author:                JMCarbonell $
//   Last modified by:    $Co-Author:                         $
//   Date:                $Date:                   April 2017 $
//   Revision:            $Revision:                      0.0 $
//
//

#if !defined(KRATOS_BAKER_JOHNSON_COOK_THERMAL_HARDENING_LAW_H_INCLUDED )
#define  KRATOS_BAKER_JOHNSON_COOK_THERMAL_HARDENING_LAW_H_INCLUDED

// System includes

// External includes

// Project includes
#include "custom_models/plasticity_models/hardening_laws/hardening_law.hpp"

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
  class KRATOS_API(CONSTITUTIVE_MODELS_APPLICATION) BakerJohnsonCookThermalHardeningLaw 
    : public HardeningLaw
  {
  public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of BakerJohnsonCookThermalHardeningLaw
    KRATOS_CLASS_POINTER_DEFINITION( BakerJohnsonCookThermalHardeningLaw );

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    BakerJohnsonCookThermalHardeningLaw();

    /// Copy constructor.
    BakerJohnsonCookThermalHardeningLaw(BakerJohnsonCookThermalHardeningLaw const& rOther);

    /// Assignment operator.
    BakerJohnsonCookThermalHardeningLaw& operator=(BakerJohnsonCookThermalHardeningLaw const& rOther);

    /// Clone.
    virtual HardeningLaw::Pointer Clone() const override;
    
    /// Destructor.
    ~BakerJohnsonCookThermalHardeningLaw();

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{

    
    /**
     * Calculate Hardening functions
     */

    virtual double& CalculateHardening(const PlasticDataType& rVariables, double& rHardening) override;
      
    /**
     * Calculate Hardening function derivatives
     */

    virtual double& CalculateDeltaHardening(const PlasticDataType& rVariables, double& rDeltaHardening) override;

    virtual double& CalculateDeltaThermalHardening(const PlasticDataType& rVariables, double& rDeltaThermalHardening) override;
    
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
    virtual std::string Info() const override
    {
      std::stringstream buffer;
      buffer << "BakerJohnsonCookThermalHardeningLaw" ;
      return buffer.str();
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const override
    {
      rOStream << "BakerJohnsonCookThermalHardeningLaw";
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const override
    {
      rOStream << "BakerJohnsonCookThermalHardeningLaw Data";
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


    virtual void save(Serializer& rSerializer) const override
    {
      KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, HardeningLaw )
    }
    
    virtual void load(Serializer& rSerializer) override
    {
      KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, HardeningLaw )
    }
    
    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{


    ///@}

  }; // Class BakerJohnsonCookThermalHardeningLaw

  ///@}

  ///@name Type Definitions
  ///@{


  ///@}
  ///@name Input and output
  ///@{


  ///@}

  ///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_BAKER_JOHNSON_COOK_THERMAL_HARDENING_LAW_H_INCLUDED  defined 

