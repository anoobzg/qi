// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepTools_Substitution_HeaderFile
#define _BRepTools_Substitution_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopTools_DataMapOfShapeListOfShape_HeaderFile
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class TopoDS_Shape;
class TopTools_ListOfShape;


//! A tool to substitute subshapes by other shapes. <br>
//! <br>
//! <br>
//!          The user use the method Substitute to define the <br>
//!          modifications. <br>
//!          A set of shapes is designated to replace a initial <br>
//!          shape. <br>
//! <br>
//!          The method Build reconstructs a new Shape with the <br>
//!          modifications.The Shape and the new shape are <br>
//!          registered. <br>
//! <br>
class BRepTools_Substitution  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   BRepTools_Substitution();
  //! Reset all the fields. <br>
  Standard_EXPORT     void Clear() ;
  //! <Oldshape> will be replaced by <NewShapes>. <br>
//! <br>
//!          <NewShapes> can be empty , in this case <OldShape> <br>
//!          will disparate from its ancestors. <br>
//! <br>
//!          if an item of <NewShapes> is oriented FORWARD. <br>
//!          it will be oriented as <OldShape> in its ancestors. <br>
//!          else it will be reversed. <br>
  Standard_EXPORT     void Substitute(const TopoDS_Shape& OldShape,const TopTools_ListOfShape& NewShapes) ;
  //! Build NewShape from <S> if its subshapes has modified. <br>
//! <br>
//!          The methods <IsCopied> and <Copy> allows you to keep <br>
//!          the resul of <Build> <br>
  Standard_EXPORT     void Build(const TopoDS_Shape& S) ;
  //! Returns   True if <S> has   been  replaced . <br>
  Standard_EXPORT     Standard_Boolean IsCopied(const TopoDS_Shape& S) const;
  //! Returns the set of shapes  substitued to <S> . <br>
  Standard_EXPORT    const TopTools_ListOfShape& Copy(const TopoDS_Shape& S) const;





protected:





private:



TopTools_DataMapOfShapeListOfShape myMap;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
