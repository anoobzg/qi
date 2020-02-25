// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _SelectMgr_DataMapOfIntegerSensitive_HeaderFile
#define _SelectMgr_DataMapOfIntegerSensitive_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMap_HeaderFile
#include <TCollection_BasicMap.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_SelectBasics_SensitiveEntity_HeaderFile
#include <Handle_SelectBasics_SensitiveEntity.hxx>
#endif
#ifndef _Handle_SelectMgr_DataMapNodeOfDataMapOfIntegerSensitive_HeaderFile
#include <Handle_SelectMgr_DataMapNodeOfDataMapOfIntegerSensitive.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
class Standard_DomainError;
class Standard_NoSuchObject;
class SelectBasics_SensitiveEntity;
class TColStd_MapIntegerHasher;
class SelectMgr_DataMapNodeOfDataMapOfIntegerSensitive;
class SelectMgr_DataMapIteratorOfDataMapOfIntegerSensitive;



class SelectMgr_DataMapOfIntegerSensitive  : public TCollection_BasicMap {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   SelectMgr_DataMapOfIntegerSensitive(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     SelectMgr_DataMapOfIntegerSensitive& Assign(const SelectMgr_DataMapOfIntegerSensitive& Other) ;
    SelectMgr_DataMapOfIntegerSensitive& operator =(const SelectMgr_DataMapOfIntegerSensitive& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~SelectMgr_DataMapOfIntegerSensitive()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const Standard_Integer& K,const Handle(SelectBasics_SensitiveEntity)& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const Standard_Integer& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const Standard_Integer& K) ;
  
  Standard_EXPORT    const Handle_SelectBasics_SensitiveEntity& Find(const Standard_Integer& K) const;
   const Handle_SelectBasics_SensitiveEntity& operator()(const Standard_Integer& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     Handle_SelectBasics_SensitiveEntity& ChangeFind(const Standard_Integer& K) ;
    Handle_SelectBasics_SensitiveEntity& operator()(const Standard_Integer& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const Standard_Integer& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const Standard_Integer& K) ;





protected:





private:

  
  Standard_EXPORT   SelectMgr_DataMapOfIntegerSensitive(const SelectMgr_DataMapOfIntegerSensitive& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif