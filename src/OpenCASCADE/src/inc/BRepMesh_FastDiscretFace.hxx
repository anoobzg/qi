// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepMesh_FastDiscretFace_HeaderFile
#define _BRepMesh_FastDiscretFace_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_BRepMesh_FastDiscretFace_HeaderFile
#include <Handle_BRepMesh_FastDiscretFace.hxx>
#endif

#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _BRepMesh_DataMapOfVertexInteger_HeaderFile
#include <BRepMesh_DataMapOfVertexInteger.hxx>
#endif
#ifndef _BRepMesh_DataMapOfShapePairOfPolygon_HeaderFile
#include <BRepMesh_DataMapOfShapePairOfPolygon.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _BRepMesh_DataMapOfIntegerPnt_HeaderFile
#include <BRepMesh_DataMapOfIntegerPnt.hxx>
#endif
#ifndef _Handle_BRepMesh_DataStructureOfDelaun_HeaderFile
#include <Handle_BRepMesh_DataStructureOfDelaun.hxx>
#endif
#ifndef _BRepMesh_ListOfVertex_HeaderFile
#include <BRepMesh_ListOfVertex.hxx>
#endif
#ifndef _TColStd_IndexedMapOfInteger_HeaderFile
#include <TColStd_IndexedMapOfInteger.hxx>
#endif
#ifndef _BRepMesh_DataMapOfIntegerListOfXY_HeaderFile
#include <BRepMesh_DataMapOfIntegerListOfXY.hxx>
#endif
#ifndef _Handle_BRepMesh_FaceAttribute_HeaderFile
#include <Handle_BRepMesh_FaceAttribute.hxx>
#endif
#ifndef _TColStd_IndexedMapOfReal_HeaderFile
#include <TColStd_IndexedMapOfReal.hxx>
#endif
#ifndef _BRepMesh_BaseAllocator_HeaderFile
#include <BRepMesh_BaseAllocator.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _TopTools_MutexForShapeProvider_HeaderFile
#include <TopTools_MutexForShapeProvider.hxx>
#endif
#ifndef _Handle_BRepAdaptor_HSurface_HeaderFile
#include <Handle_BRepAdaptor_HSurface.hxx>
#endif
#ifndef _Handle_Poly_Triangulation_HeaderFile
#include <Handle_Poly_Triangulation.hxx>
#endif
#ifndef _BRepMesh_ClassifierPtr_HeaderFile
#include <BRepMesh_ClassifierPtr.hxx>
#endif
class BRepMesh_DataStructureOfDelaun;
class BRepMesh_FaceAttribute;
class TopoDS_Face;
class TopTools_DataMapOfShapeReal;
class TopoDS_Vertex;
class BRepAdaptor_HSurface;
class TopoDS_Edge;
class Poly_Triangulation;
class TopLoc_Location;
class BRepMesh_ListOfVertex;
class TColStd_ListOfInteger;
class BRepMesh_Delaun;
class gp_XY;
class gp_Pnt2d;
class BRepMesh_DataMapOfIntegerListOfXY;
class BRepMesh_Triangle;
class BRepMesh_Edge;
class BRepMesh_Vertex;
class gp_Pnt;


//! Algorithm  to mesh  a face  with  respect of  the <br>
//!          frontier the deflection  and by option the  shared <br>
//!          components. <br>
class BRepMesh_FastDiscretFace : public MMgt_TShared {

public:

  
  Standard_EXPORT   BRepMesh_FastDiscretFace(const Standard_Real theAngle,const Standard_Boolean theWithShare = Standard_True);
  
  Standard_EXPORT     void Add(const TopoDS_Face& theFace,const Handle(BRepMesh_FaceAttribute)& theAttrib,const TopTools_DataMapOfShapeReal& theMapDefle,const TopTools_MutexForShapeProvider& theMutexProvider) ;
  
  Standard_EXPORT     Standard_Real Control(const Handle(BRepAdaptor_HSurface)& theCaro,const Standard_Real theDefFace,BRepMesh_ListOfVertex& theInternalV,TColStd_ListOfInteger& theBadTriangles,TColStd_ListOfInteger& theNulTriangles,BRepMesh_Delaun& theTrigu,const Standard_Boolean theIsFirst) ;
  
  Standard_EXPORT   static  gp_XY FindUV(const TopoDS_Vertex& theV,const gp_Pnt2d& theXY,const Standard_Integer theIp,const Handle(BRepAdaptor_HSurface)& theSFace,const Standard_Real theMinDist,const Handle(BRepMesh_FaceAttribute)& theFaceAttribute,BRepMesh_DataMapOfIntegerListOfXY& theLocation2dMap) ;
  //! Gives the triangle of <Index>. <br>
  Standard_EXPORT    const BRepMesh_Triangle& Triangle(const Standard_Integer theIndex) const;
  //! Gives the edge of index <Index>. <br>
  Standard_EXPORT    const BRepMesh_Edge& Edge(const Standard_Integer theIndex) const;
  //! Gives the vertex of <Index>. <br>
  Standard_EXPORT    const BRepMesh_Vertex& Vertex(const Standard_Integer theIndex) const;
  //! Gives the location3d of the vertex of <Index>. <br>
  Standard_EXPORT    const gp_Pnt& Pnt(const Standard_Integer theIndex) const;




  DEFINE_STANDARD_RTTI(BRepMesh_FastDiscretFace)

protected:

  
  Standard_EXPORT     Standard_Boolean RestoreStructureFromTriangulation(const TopoDS_Edge& theEdge,const TopoDS_Face& theFace,const Handle(BRepAdaptor_HSurface)& theSurf,const Handle(Poly_Triangulation)& theTrigu,const Standard_Real theDefEdge,const TopLoc_Location& theLoc,const TopTools_MutexForShapeProvider& theMutexProvider) ;



private: 

  
  Standard_EXPORT     void Add(const TopoDS_Vertex& theVert,const TopoDS_Face& theFace,const Handle(BRepAdaptor_HSurface)& theSFace) ;
  
  Standard_EXPORT     void InternalVertices(const Handle(BRepAdaptor_HSurface)& theCaro,BRepMesh_ListOfVertex& theInternalV,const Standard_Real theDefFace,const BRepMesh_ClassifierPtr& theClassifier) ;
  
  Standard_EXPORT     void AddInShape(const TopoDS_Face& theFace,const Standard_Real theDefFace,const TopTools_MutexForShapeProvider& theMutexProvider) ;

Standard_Real myAngle;
Standard_Boolean myWithShare;
BRepMesh_DataMapOfVertexInteger myVertices;
BRepMesh_DataMapOfShapePairOfPolygon myInternaledges;
Standard_Integer myNbLocat;
BRepMesh_DataMapOfIntegerPnt myLocation3d;
Handle_BRepMesh_DataStructureOfDelaun myStructure;
BRepMesh_ListOfVertex myListver;
TColStd_IndexedMapOfInteger myVemap;
BRepMesh_DataMapOfIntegerListOfXY myLocation2d;
Handle_BRepMesh_FaceAttribute myAttrib;
Standard_Boolean myInternalVerticesMode;
TColStd_IndexedMapOfReal myUParam;
TColStd_IndexedMapOfReal myVParam;
BRepMesh_BaseAllocator myAllocator;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif