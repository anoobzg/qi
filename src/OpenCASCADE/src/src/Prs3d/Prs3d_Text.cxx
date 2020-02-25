// Created on: 1993-09-14
// Created by: Jean-Louis FRENKEL
// Copyright (c) 1993-1999 Matra Datavision
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



#include <Prs3d_Text.ixx>
#include <Graphic3d_Vertex.hxx>
#include <Prs3d_TextAspect.hxx>
#include <TCollection_AsciiString.hxx>
#include <Graphic3d_Group.hxx>

void Prs3d_Text::Draw (
		       const Handle(Prs3d_Presentation)& aPresentation,
		       const Handle(Prs3d_TextAspect)& anAspect,
		       const TCollection_ExtendedString& aText,
		       const gp_Pnt& AttachmentPoint) {


  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(anAspect->Aspect());
  Standard_Real x,y,z;
  AttachmentPoint.Coord(x,y,z);

  
// POP Graphic3d_Grup accepte de l'extended
  Prs3d_Root::CurrentGroup(aPresentation)->Text(
//                     TCollection_AsciiString(aText).ToCString(),
		      aText,
	             Graphic3d_Vertex(x,y,z),
                     anAspect->Height(),
                     anAspect->Angle(),
                     anAspect->Orientation(),
                     anAspect->HorizontalJustification(),
                     anAspect->VerticalJustification());
}


void Prs3d_Text::Draw (
		       const Handle(Prs3d_Presentation)& aPresentation,
		       const Handle(Prs3d_Drawer)& aDrawer,
		       const TCollection_ExtendedString& aText,
		       const gp_Pnt& AttachmentPoint) {

  
  Prs3d_Text::Draw(aPresentation,aDrawer->TextAspect(),aText,AttachmentPoint);
  }