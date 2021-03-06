// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IFSelect_TSeqOfDispatch_HeaderFile
#define _IFSelect_TSeqOfDispatch_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BaseSequence_HeaderFile
#include <TCollection_BaseSequence.hxx>
#endif
#ifndef _Handle_IFSelect_Dispatch_HeaderFile
#include <Handle_IFSelect_Dispatch.hxx>
#endif
#ifndef _Handle_IFSelect_SequenceNodeOfTSeqOfDispatch_HeaderFile
#include <Handle_IFSelect_SequenceNodeOfTSeqOfDispatch.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class IFSelect_Dispatch;
class IFSelect_SequenceNodeOfTSeqOfDispatch;



class IFSelect_TSeqOfDispatch  : public TCollection_BaseSequence {
public:

  DEFINE_STANDARD_ALLOC

  
      IFSelect_TSeqOfDispatch();
  
  Standard_EXPORT     void Clear() ;
~IFSelect_TSeqOfDispatch()
{
  Clear();
}
  
  Standard_EXPORT    const IFSelect_TSeqOfDispatch& Assign(const IFSelect_TSeqOfDispatch& Other) ;
   const IFSelect_TSeqOfDispatch& operator =(const IFSelect_TSeqOfDispatch& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void Append(const Handle(IFSelect_Dispatch)& T) ;
  
        void Append(IFSelect_TSeqOfDispatch& S) ;
  
  Standard_EXPORT     void Prepend(const Handle(IFSelect_Dispatch)& T) ;
  
        void Prepend(IFSelect_TSeqOfDispatch& S) ;
  
        void InsertBefore(const Standard_Integer Index,const Handle(IFSelect_Dispatch)& T) ;
  
        void InsertBefore(const Standard_Integer Index,IFSelect_TSeqOfDispatch& S) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer Index,const Handle(IFSelect_Dispatch)& T) ;
  
        void InsertAfter(const Standard_Integer Index,IFSelect_TSeqOfDispatch& S) ;
  
  Standard_EXPORT    const Handle_IFSelect_Dispatch& First() const;
  
  Standard_EXPORT    const Handle_IFSelect_Dispatch& Last() const;
  
        void Split(const Standard_Integer Index,IFSelect_TSeqOfDispatch& Sub) ;
  
  Standard_EXPORT    const Handle_IFSelect_Dispatch& Value(const Standard_Integer Index) const;
   const Handle_IFSelect_Dispatch& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const Handle(IFSelect_Dispatch)& I) ;
  
  Standard_EXPORT     Handle_IFSelect_Dispatch& ChangeValue(const Standard_Integer Index) ;
    Handle_IFSelect_Dispatch& operator()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT     void Remove(const Standard_Integer Index) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;





protected:





private:

  
  Standard_EXPORT   IFSelect_TSeqOfDispatch(const IFSelect_TSeqOfDispatch& Other);




};

#define SeqItem Handle_IFSelect_Dispatch
#define SeqItem_hxx <IFSelect_Dispatch.hxx>
#define TCollection_SequenceNode IFSelect_SequenceNodeOfTSeqOfDispatch
#define TCollection_SequenceNode_hxx <IFSelect_SequenceNodeOfTSeqOfDispatch.hxx>
#define Handle_TCollection_SequenceNode Handle_IFSelect_SequenceNodeOfTSeqOfDispatch
#define TCollection_SequenceNode_Type_() IFSelect_SequenceNodeOfTSeqOfDispatch_Type_()
#define TCollection_Sequence IFSelect_TSeqOfDispatch
#define TCollection_Sequence_hxx <IFSelect_TSeqOfDispatch.hxx>

#include <TCollection_Sequence.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
