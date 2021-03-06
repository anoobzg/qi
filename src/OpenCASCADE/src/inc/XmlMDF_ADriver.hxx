// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XmlMDF_ADriver_HeaderFile
#define _XmlMDF_ADriver_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_XmlMDF_ADriver_HeaderFile
#include <Handle_XmlMDF_ADriver.hxx>
#endif

#ifndef _Handle_CDM_MessageDriver_HeaderFile
#include <Handle_CDM_MessageDriver.hxx>
#endif
#ifndef _TCollection_AsciiString_HeaderFile
#include <TCollection_AsciiString.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Standard_CString_HeaderFile
#include <Standard_CString.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_TDF_Attribute_HeaderFile
#include <Handle_TDF_Attribute.hxx>
#endif
#ifndef _Handle_Standard_Type_HeaderFile
#include <Handle_Standard_Type.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _XmlObjMgt_RRelocationTable_HeaderFile
#include <XmlObjMgt_RRelocationTable.hxx>
#endif
#ifndef _XmlObjMgt_SRelocationTable_HeaderFile
#include <XmlObjMgt_SRelocationTable.hxx>
#endif
class CDM_MessageDriver;
class TDF_Attribute;
class Standard_Type;
class TCollection_AsciiString;
class XmlObjMgt_Persistent;
class TCollection_ExtendedString;


//! Attribute Storage/Retrieval Driver. <br>
class XmlMDF_ADriver : public MMgt_TShared {

public:

  //! Returns the version number from which the driver <br>
//!          is available. <br>
  Standard_EXPORT   virtual  Standard_Integer VersionNumber() const;
  //! Creates a new attribute from TDF. <br>
  Standard_EXPORT   virtual  Handle_TDF_Attribute NewEmpty() const = 0;
  //! Returns the type of source object, <br>
//!          inheriting from Attribute from TDF. <br>
  Standard_EXPORT     Handle_Standard_Type SourceType() const;
  //! Returns the full XML tag name (including NS prefix) <br>
  Standard_EXPORT    const TCollection_AsciiString& TypeName() const;
  //! Translate the contents of <aSource> and put it <br>
//!          into <aTarget>, using the relocation table <br>
//!          <aRelocTable> to keep the sharings. <br>
  Standard_EXPORT   virtual  Standard_Boolean Paste(const XmlObjMgt_Persistent& aSource,const Handle(TDF_Attribute)& aTarget,XmlObjMgt_RRelocationTable& aRelocTable) const = 0;
  //! Translate the contents of <aSource> and put it <br>
//!          into <aTarget>, using the relocation table <br>
//!          <aRelocTable> to keep the sharings. <br>
  Standard_EXPORT   virtual  void Paste(const Handle(TDF_Attribute)& aSource,XmlObjMgt_Persistent& aTarget,XmlObjMgt_SRelocationTable& aRelocTable) const = 0;
  //! Send message to Application (usually when error occurres) <br>
  Standard_EXPORT     void WriteMessage(const TCollection_ExtendedString& theMessage) const;




  DEFINE_STANDARD_RTTI(XmlMDF_ADriver)

protected:

  
  Standard_EXPORT   XmlMDF_ADriver(const Handle(CDM_MessageDriver)& theMessageDriver,const Standard_CString theNamespace,const Standard_CString theName = NULL);

TCollection_AsciiString myTypeName;


private: 


Handle_CDM_MessageDriver myMessageDriver;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
