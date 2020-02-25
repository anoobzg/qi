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

#include <StepGeom_PointOnCurve.ixx>


StepGeom_PointOnCurve::StepGeom_PointOnCurve ()  {}

void StepGeom_PointOnCurve::Init(
	const Handle(TCollection_HAsciiString)& aName)
{

	StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_PointOnCurve::Init(
	const Handle(TCollection_HAsciiString)& aName,
	const Handle(StepGeom_Curve)& aBasisCurve,
	const Standard_Real aPointParameter)
{
	// --- classe own fields ---
	basisCurve = aBasisCurve;
	pointParameter = aPointParameter;
	// --- classe inherited fields ---
	StepRepr_RepresentationItem::Init(aName);
}


void StepGeom_PointOnCurve::SetBasisCurve(const Handle(StepGeom_Curve)& aBasisCurve)
{
	basisCurve = aBasisCurve;
}

Handle(StepGeom_Curve) StepGeom_PointOnCurve::BasisCurve() const
{
	return basisCurve;
}

void StepGeom_PointOnCurve::SetPointParameter(const Standard_Real aPointParameter)
{
	pointParameter = aPointParameter;
}

Standard_Real StepGeom_PointOnCurve::PointParameter() const
{
	return pointParameter;
}