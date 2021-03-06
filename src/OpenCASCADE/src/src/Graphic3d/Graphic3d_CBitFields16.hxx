// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

/*============================================================================*/
/*==== Titre: Graphic3d_CBitFields16.hxx				      */
/*==== Role : The header file of primitive type "CBitFields16" from Graphic3d */
/*====									      */
/*==== Implementation:  This is a primitive type implemented with typedef     */
/*============================================================================*/

#ifndef _Graphic3d_CBitFields16_HeaderFile
#define _Graphic3d_CBitFields16_HeaderFile

typedef struct {

	unsigned bool1	:1;
	unsigned bool2	:1;
	unsigned bool3	:1;
	unsigned bool4	:1;

	unsigned bool5	:1;
	unsigned bool6	:1;
	unsigned bool7	:1;
	unsigned bool8	:1;

	unsigned bool9	:1;
	unsigned bool10	:1;
	unsigned bool11	:1;
	unsigned bool12	:1;

	unsigned bool13	:1;
	unsigned bool14	:1;
	unsigned bool15	:1;
	unsigned bool16	:1;

} Graphic3d_CBitFields16;

#if defined(__cplusplus) || defined(c_plusplus)
/*==== Definition de Type ====================================================*/
#include <Standard_Type.hxx> 
const Handle(Standard_Type)&  STANDARD_TYPE(Graphic3d_CBitFields16);
/*============================================================================*/

#endif
#endif /*Graphic3d_CBitFields16_HeaderFile*/
