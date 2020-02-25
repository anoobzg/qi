// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Aspect_InteriorStyle_HeaderFile
#define _Aspect_InteriorStyle_HeaderFile

//! Definition of interior types for primitive <br>
//!          faces. <br>
//! <br>
//!          IS_EMPTY    no interior. <br>
//!          IS_HOLLOW   display the boundaries of the surface. <br>
//!          IS_HATCH    display hatched with a hatch style. <br>
//!          IS_SOLID    display the interior entirely filled. <br>
//!          IS_HIDDENLINE       display in hidden lines removed. <br>
//! <br>
enum Aspect_InteriorStyle {
Aspect_IS_EMPTY,
Aspect_IS_HOLLOW,
Aspect_IS_HATCH,
Aspect_IS_SOLID,
Aspect_IS_HIDDENLINE
};

#ifndef _Standard_PrimitiveTypes_HeaderFile
#include <Standard_PrimitiveTypes.hxx>
#endif

#endif