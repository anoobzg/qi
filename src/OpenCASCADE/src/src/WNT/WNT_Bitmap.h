/*
 Copyright (c) 1999-2012 OPEN CASCADE SAS

 The content of this file is subject to the Open CASCADE Technology Public
 License Version 6.5 (the "License"). You may not use the content of this file
 except in compliance with the License. Please obtain a copy of the License
 at http://www.opencascade.org and read it completely before using this file.

 The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
 main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.

 The Original Code and all software distributed under the License is
 distributed on an "AS IS" basis, without warranty of any kind, and the
 Initial Developer hereby disclaims all such warranties, including without
 limitation, any warranties of merchantability, fitness for a particular
 purpose or non-infringement. Please see the License for the specific terms
 and conditions governing the rights and limitations under the License.

*/

#ifndef __WNT_BITMAP_H
# define __WNT_BITMAP_H

# ifndef __WINDOWS_H_INCLUDED
#  define __WINDOWS_H_INCLUDED
#  ifndef STRICT
#   define STRICT
#  endif  /* STRICT */
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>

#ifdef DrawText
#undef DrawText
#endif

#  ifdef THIS
#   undef THIS
#  endif  // THIS
# endif  // __WINDOWS_H_INCLUDED

typedef struct _wnt_bitmap {

                int     nUsed;
                HBITMAP hBmp;

               } WNT_Bitmap, *PWNT_Bitmap;

#endif  /* __WNT_SAFEBITMAP_H */