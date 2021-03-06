// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepBlend_AppSurface_HeaderFile
#define _BRepBlend_AppSurface_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Approx_SweepApproximation_HeaderFile
#include <Approx_SweepApproximation.hxx>
#endif
#ifndef _AppBlend_Approx_HeaderFile
#include <AppBlend_Approx.hxx>
#endif
#ifndef _Handle_Approx_SweepFunction_HeaderFile
#include <Handle_Approx_SweepFunction.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_OStream_HeaderFile
#include <Standard_OStream.hxx>
#endif
class StdFail_NotDone;
class Standard_DomainError;
class Standard_OutOfRange;
class Approx_SweepFunction;
class TColgp_Array2OfPnt;
class TColStd_Array2OfReal;
class TColStd_Array1OfReal;
class TColStd_Array1OfInteger;
class TColgp_Array1OfPnt2d;


//!Used to Approximate the blending surfaces. <br>
class BRepBlend_AppSurface  : public AppBlend_Approx {
public:

  DEFINE_STANDARD_ALLOC

  //! Approximation     of   the   new  Surface  (and <br>
//!          eventually the  2d    Curves   on the   support <br>
//!          surfaces). <br>
//!          Normaly     the  2d    curve are <br>
//!          approximated  with an  tolerance   given  by   the <br>
//!          resolution on   support surfaces,  but  if this <br>
//!          tolerance is too large Tol2d  is used. <br>
  Standard_EXPORT   BRepBlend_AppSurface(Handle(Approx_SweepFunction)& Funct,const Standard_Real First,const Standard_Real Last,const Standard_Real Tol3d,const Standard_Real Tol2d,const Standard_Real TolAngular,const GeomAbs_Shape Continuity = GeomAbs_C0,const Standard_Integer Degmax = 11,const Standard_Integer Segmax = 50);
  
        Standard_Boolean IsDone() const;
  
  Standard_EXPORT     void SurfShape(Standard_Integer& UDegree,Standard_Integer& VDegree,Standard_Integer& NbUPoles,Standard_Integer& NbVPoles,Standard_Integer& NbUKnots,Standard_Integer& NbVKnots) const;
  
  Standard_EXPORT     void Surface(TColgp_Array2OfPnt& TPoles,TColStd_Array2OfReal& TWeights,TColStd_Array1OfReal& TUKnots,TColStd_Array1OfReal& TVKnots,TColStd_Array1OfInteger& TUMults,TColStd_Array1OfInteger& TVMults) const;
  
        Standard_Integer UDegree() const;
  
        Standard_Integer VDegree() const;
  
       const TColgp_Array2OfPnt& SurfPoles() const;
  
       const TColStd_Array2OfReal& SurfWeights() const;
  
       const TColStd_Array1OfReal& SurfUKnots() const;
  
       const TColStd_Array1OfReal& SurfVKnots() const;
  
       const TColStd_Array1OfInteger& SurfUMults() const;
  
       const TColStd_Array1OfInteger& SurfVMults() const;
  //! returns the maximum error in the suface approximation. <br>
  Standard_EXPORT     Standard_Real MaxErrorOnSurf() const;
  
        Standard_Integer NbCurves2d() const;
  
  Standard_EXPORT     void Curves2dShape(Standard_Integer& Degree,Standard_Integer& NbPoles,Standard_Integer& NbKnots) const;
  
  Standard_EXPORT     void Curve2d(const Standard_Integer Index,TColgp_Array1OfPnt2d& TPoles,TColStd_Array1OfReal& TKnots,TColStd_Array1OfInteger& TMults) const;
  
        Standard_Integer Curves2dDegree() const;
  
       const TColgp_Array1OfPnt2d& Curve2dPoles(const Standard_Integer Index) const;
  
       const TColStd_Array1OfReal& Curves2dKnots() const;
  
       const TColStd_Array1OfInteger& Curves2dMults() const;
  
  Standard_EXPORT     void TolReached(Standard_Real& Tol3d,Standard_Real& Tol2d) const;
  //! returns the maximum error in the <Index> 2d curve approximation. <br>
  Standard_EXPORT     Standard_Real Max2dError(const Standard_Integer Index) const;
  
  Standard_EXPORT     Standard_Real TolCurveOnSurf(const Standard_Integer Index) const;
  //! diplay information on approximation. <br>
  Standard_EXPORT     void Dump(Standard_OStream& o) const;





protected:





private:



Approx_SweepApproximation approx;


};


#include <BRepBlend_AppSurface.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
