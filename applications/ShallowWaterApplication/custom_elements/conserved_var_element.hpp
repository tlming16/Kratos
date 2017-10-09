//   
//   Project Name:        Kratos       
//   Last modified by:    Miguel Masó Sotomayor
//   Date:                July 3rd 2017
//   Revision:            1.2
//
//

#if !defined(KRATOS_CONSERVED_VAR_ELEM_H_INCLUDED)
#define  KRATOS_CONSERVED_VAR_ELEM_H_INCLUDED 

// System includes 


// External includes 
#include "boost/smart_ptr.hpp"


// Project includes
#include "includes/define.h"
#include "includes/element.h"
#include "includes/ublas_interface.h"
#include "includes/variables.h" 

namespace Kratos
{

  template< unsigned int TNumNodes >
  class ConservedVarElement : public Element
  {
  public:
     
    /// Counted pointer of ConservedVarElement
    KRATOS_CLASS_POINTER_DEFINITION( ConservedVarElement );

//----------------------------------------------------------------------

    /// Default constructor.
    ConservedVarElement() :
        Element()
    {}
    
    ConservedVarElement(IndexType NewId, GeometryType::Pointer pGeometry) :
        Element(NewId, pGeometry)
    {}
    
    ConservedVarElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties) :
        Element(NewId, pGeometry, pProperties)
    {}

    /// Destructor.
    virtual ~ ConservedVarElement() {};

//----------------------------------------------------------------------

    Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes,  PropertiesType::Pointer pProperties) const
    {
        KRATOS_TRY
        return Element::Pointer(new ConservedVarElement(NewId, GetGeometry().Create(ThisNodes), pProperties));
        KRATOS_CATCH("")
    }

    void EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& rCurrentProcessInfo);

    void GetDofList(DofsVectorType& rElementalDofList,ProcessInfo& rCurrentProcessInfo);

    void CalculateLocalSystem(MatrixType& rLeftHandSideMatrix, VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);

    void CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);

    void GetValueOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rValues, const ProcessInfo& rCurrentProcessInfo);

//----------------------------------------------------------------------

  protected:

    void CalculateGeometry(boost::numeric::ublas::bounded_matrix<double, TNumNodes, 2>& rDN_DX, double& rArea);

    double ComputeElemSize(boost::numeric::ublas::bounded_matrix<double, TNumNodes, 2>& rDN_DX);

    void GetNodalValues(array_1d<double,TNumNodes*3>& rDepth, array_1d<double,TNumNodes*3>& rRain, array_1d<double,TNumNodes*3>& rUnkn, array_1d<double,TNumNodes*3>& rProj);

    void GetElementValues(const boost::numeric::ublas::bounded_matrix<double,TNumNodes,2>& rDN_DX, const array_1d<double,TNumNodes*3>& rNodalVar, double& rHeight, array_1d<double,2>& rHeightGrad, double& rDivU);

    void ComputeStabilizationParameters(const double& rHeight, const array_1d<double,2>& rHeightGrad, const double& rElemSize, double& rTauU, double& rTauH, double& rKdc);

    void CalculateLumpedMassMatrix(boost::numeric::ublas::bounded_matrix<double, TNumNodes*3, TNumNodes*3>& rMassMatrix);

    double mGravity;
    double mHeightUnitConvert;

  private:

    friend class Serializer;


  }; // Class ConservedVarElement

}  // namespace Kratos.

#endif // KRATOS_CONSERVED_VAR_ELEM_H_INCLUDED  defined