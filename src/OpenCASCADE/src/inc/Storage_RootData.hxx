// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Storage_RootData_HeaderFile
#define _Storage_RootData_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_Storage_RootData_HeaderFile
#include <Handle_Storage_RootData.hxx>
#endif

#ifndef _Storage_MapOfPers_HeaderFile
#include <Storage_MapOfPers.hxx>
#endif
#ifndef _Storage_Error_HeaderFile
#include <Storage_Error.hxx>
#endif
#ifndef _TCollection_AsciiString_HeaderFile
#include <TCollection_AsciiString.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Storage_Root_HeaderFile
#include <Handle_Storage_Root.hxx>
#endif
#ifndef _Handle_Storage_HSeqOfRoot_HeaderFile
#include <Handle_Storage_HSeqOfRoot.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Standard_Persistent_HeaderFile
#include <Handle_Standard_Persistent.hxx>
#endif
class Standard_NoSuchObject;
class Storage_Schema;
class Storage_Root;
class Storage_HSeqOfRoot;
class TCollection_AsciiString;
class Standard_Persistent;



class Storage_RootData : public MMgt_TShared {

public:

  
  Standard_EXPORT   Storage_RootData();
  //! returns the number of roots. <br>
  Standard_EXPORT     Standard_Integer NumberOfRoots() const;
  //! add a root to <me>. If a root with same name is present, it <br>
//!          will be replaced by <aRoot>. <br>
  Standard_EXPORT     void AddRoot(const Handle(Storage_Root)& aRoot) ;
  
  Standard_EXPORT     Handle_Storage_HSeqOfRoot Roots() const;
  //! find a root with name <aName>. <br>
  Standard_EXPORT     Handle_Storage_Root Find(const TCollection_AsciiString& aName) const;
  //! returns Standard_True if <me> contains a root named <aName> <br>
  Standard_EXPORT     Standard_Boolean IsRoot(const TCollection_AsciiString& aName) const;
  //! remove the root named <aName>. <br>
  Standard_EXPORT     void RemoveRoot(const TCollection_AsciiString& aName) ;
  
  Standard_EXPORT     Storage_Error ErrorStatus() const;
  
  Standard_EXPORT     TCollection_AsciiString ErrorStatusExtension() const;
  
  Standard_EXPORT     void ClearErrorStatus() ;


friend class Storage_Schema;


  DEFINE_STANDARD_RTTI(Storage_RootData)

protected:




private: 

  
  Standard_EXPORT     void UpdateRoot(const TCollection_AsciiString& aName,const Handle(Standard_Persistent)& aPers) ;
  
  Standard_EXPORT     void SetErrorStatus(const Storage_Error anError) ;
  
  Standard_EXPORT     void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt) ;

Storage_MapOfPers myObjects;
Storage_Error myErrorStatus;
TCollection_AsciiString myErrorStatusExt;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
