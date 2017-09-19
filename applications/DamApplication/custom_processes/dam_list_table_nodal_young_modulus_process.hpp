//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Lorenzo Gracia
//
//

#if !defined(KRATOS_DAM_LIST_TABLE_NODAL_YOUNG_MODULUS_PROCESS )
#define  KRATOS_DAM_LIST_TABLE_NODAL_YOUNG_MODULUS_PROCESS

#include <cmath>

// Project includes
#include "includes/kratos_flags.h"
#include "includes/kratos_parameters.h"
#include "processes/process.h"

// Application include
#include "dam_application_variables.h"

namespace Kratos
{

class DamListTableNodalYoungModulusProcess : public Process
{
    
public:

    KRATOS_CLASS_POINTER_DEFINITION(DamListTableNodalYoungModulusProcess);
    
    typedef Table<double,double> TableType;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    /// Constructor
    DamListTableNodalYoungModulusProcess(ModelPart& rModelPart, TableType& Table,
                                Parameters& rParameters
                                ) : Process(Flags()) , mrModelPart(rModelPart), mrTable(Table)
    {
        KRATOS_TRY
			 
        //only include validation with c++11 since raw_literals do not exist in c++03
        Parameters default_parameters( R"(
            {
                "model_part_name"  :"PLEASE_CHOOSE_MODEL_PART_NAME",
                "mesh_id"          : 0,
                "variable_name"    : "PLEASE_PRESCRIBE_VARIABLE_NAME",
                "is_fixed"         : false,
                "young_Modulus_min": 5.0,
                "young_Modulus_max": 50.0,
                "number_of_cases"  : 10            
            }  )" );
        
        // Some values need to be mandatorily prescribed since no meaningful default value exist. For this reason try accessing to them
        // So that an error is thrown if they don't exist
        rParameters["variable_name"];
        rParameters["model_part_name"];

        // Now validate agains defaults -- this also ensures no type mismatch
        rParameters.ValidateAndAssignDefaults(default_parameters);

        mMeshId = rParameters["mesh_id"].GetInt();
        mVariableName = rParameters["variable_name"].GetString();
        mIsFixed = rParameters["is_fixed"].GetBool();

        KRATOS_CATCH("");
    }

    ///------------------------------------------------------------------------------------
    
    /// Destructor
    virtual ~DamListTableNodalYoungModulusProcess() {}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void ExecuteInitializeSolutionStep()
    {
        
        KRATOS_TRY;
        
        Variable<double> var = KratosComponents< Variable<double> >::Get(mVariableName);
        const int nnodes = mrModelPart.GetMesh(mMeshId).Nodes().size();
        const double time_unit_converter = mrModelPart.GetProcessInfo()[TIME_UNIT_CONVERTER];

        double time = mrModelPart.GetProcessInfo()[TIME];
        time = time/time_unit_converter;
        mValue = mrTable.GetValue(time);
                
        if(nnodes != 0)
        {
            ModelPart::NodesContainerType::iterator it_begin = mrModelPart.GetMesh(mMeshId).NodesBegin();
        
            #pragma omp parallel for
            for(int i = 0; i<nnodes; i++)
            {
                ModelPart::NodesContainerType::iterator it = it_begin + i;
                
                if(mIsFixed)
                {
                    it->Fix(var);
                }
                
                it->FastGetSolutionStepValue(var) = mValue;
            }
        }
        
        KRATOS_CATCH("");
    }
    
    /// Turn back information as a string.
    std::string Info() const
    {
        return "DamListTableNodalYoungModulusProcess";
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << "DamListTableNodalYoungModulusProcess";
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const
    {
    }

///----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

protected:

    /// Member Variables

    ModelPart& mrModelPart;
    TableType& mrTable;
    std::size_t mMeshId;
    std::string mVariableName;
    bool mIsFixed;
    double mValue;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:

    /// Assignment operator.
    DamListTableNodalYoungModulusProcess& operator=(DamListTableNodalYoungModulusProcess const& rOther);

};//Class


/// input stream function
inline std::istream& operator >> (std::istream& rIStream,
                                 DamListTableNodalYoungModulusProcess& rThis);

/// output stream function
inline std::ostream& operator << (std::ostream& rOStream,
                                  const DamListTableNodalYoungModulusProcess& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}

} /* namespace Kratos.*/

#endif /* KRATOS_DAM_LIST_TABLE_NODAL_YOUNG_MODULUS_PROCESS defined */
