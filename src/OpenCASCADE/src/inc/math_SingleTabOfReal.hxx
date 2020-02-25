// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _math_SingleTabOfReal_HeaderFile
#define _math_SingleTabOfReal_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif



class math_SingleTabOfReal  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   math_SingleTabOfReal(const Standard_Integer LowerIndex,const Standard_Integer UpperIndex);
  
  Standard_EXPORT   math_SingleTabOfReal(const Standard_Real& Tab,const Standard_Integer LowerIndex,const Standard_Integer UpperIndex);
  
  Standard_EXPORT     void Init(const Standard_Real& InitValue) ;
  
  Standard_EXPORT   math_SingleTabOfReal(const math_SingleTabOfReal& Other);
  
        void Copy(math_SingleTabOfReal& Other) const;
  
  Standard_EXPORT     void SetLower(const Standard_Integer LowerIndex) ;
  
        Standard_Real& Value(const Standard_Integer Index) const;
      Standard_Real& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void Free() ;
~math_SingleTabOfReal()
{
  Free();
}





protected:





private:



Standard_Address Addr;
Standard_Boolean isAllocated;
Standard_Integer First;
Standard_Integer Last;


};

#define Item Standard_Real
#define Item_hxx <Standard_Real.hxx>
#define math_SingleTab math_SingleTabOfReal
#define math_SingleTab_hxx <math_SingleTabOfReal.hxx>

#include <math_SingleTab.lxx>

#undef Item
#undef Item_hxx
#undef math_SingleTab
#undef math_SingleTab_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif