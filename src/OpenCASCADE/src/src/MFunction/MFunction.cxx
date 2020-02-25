// Created on: 1999-06-24
// Created by: Vladislav ROMASHKO
// Copyright (c) 1999-1999 Matra Datavision
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



#include <MFunction.ixx>

#include <MDF_ARDriverHSequence.hxx>
#include <MDF_ASDriverHSequence.hxx>
#include <CDM_MessageDriver.hxx>
#include <MFunction_FunctionStorageDriver.hxx>
#include <MFunction_FunctionRetrievalDriver.hxx>


//=======================================================================
//function : AddStorageDrivers
//purpose  : 
//=======================================================================

void MFunction::AddStorageDrivers(const Handle(MDF_ASDriverHSequence)& aDriverSeq, const Handle(CDM_MessageDriver)& theMsgDriver)
{ 
  aDriverSeq->Append(new MFunction_FunctionStorageDriver(theMsgDriver));
}

//=======================================================================
//function : AddRetrievalDrivers
//purpose  : 
//=======================================================================

void MFunction::AddRetrievalDrivers(const Handle(MDF_ARDriverHSequence)& aDriverSeq,const Handle(CDM_MessageDriver)& theMsgDriver)
{
  aDriverSeq->Append(new MFunction_FunctionRetrievalDriver(theMsgDriver));
}