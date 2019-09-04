#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int TCHAR ;
typedef  int* LPTSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
#define  CHAR_DOT 130 
 int CHAR_NULL ; 
#define  CHAR_QUESTION 129 
#define  CHAR_STAR 128 
 int DOT ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  NO_ERROR ; 

WORD I_LFNEditName( LPTSTR lpSrc, LPTSTR lpEd, LPTSTR lpRes, INT iResBufSize )
{
   INT ResLen = 0;     // Length of result

// This is turned off until we agree
// that cmd operates in the same way

#ifdef USELASTDOT
   LPTSTR lpChar;

   //
   // We have a special case hack for the dot, since when we do a
   // rename from foo.bar.baz to *.txt, we want to use the last dot, not
   // the first one (desired result = foo.bar.txt, not foo.txt)
   //
   // We find the dot (GetExtension rets first char after last dot if there
   // is a dot), then if the delimiter for the '*' is a CHAR_DOT, we continue
   // copying until we get to the last dot instead of finding the first one.
   //

   lpChar = GetExtension(lpSrc);
   if (*lpChar) {
      lpChar--;
   } else {
      lpChar = NULL;
   }
#endif

   while (*lpEd) {

      if (ResLen < iResBufSize) {

         switch (*lpEd) {

         case CHAR_STAR:
            {
               TCHAR delimit = *(lpEd+1);

#ifdef USELASTDOT

               //
               // For all other delimiters, we use the first
               // occurrence (e.g., *f.txt).
               //
               if (CHAR_DOT != delimit)
                  lpChar = NULL;

               while ((ResLen < iResBufSize) && ( *lpSrc != CHAR_NULL ) &&
                  ( *lpSrc != delimit || (lpChar && lpChar != lpSrc ))) {
#else
               while ((ResLen < iResBufSize) &&
                  ( *lpSrc != CHAR_NULL ) && ( *lpSrc != delimit )) {
#endif

                  *(lpRes++) = *(lpSrc++);
                  ResLen++;

               }
            }
            break;


         case CHAR_QUESTION:
            if ((*lpSrc != DOT ) && (*lpSrc != CHAR_NULL)) {

               if (ResLen < iResBufSize) {

                  *(lpRes++) = *(lpSrc++);
                  ResLen++;
               }
               else
                  return ERROR_INVALID_PARAMETER ;
            }
            break;

         case CHAR_DOT:
            while ((*lpSrc != DOT ) && (*lpSrc != CHAR_NULL))
               lpSrc++;

            *(lpRes++) = DOT ;       // from EditMask, even if src doesn't
                                     // have one, so always put one.
            ResLen++;
            if (*lpSrc)              // point one past CHAR_DOT
               lpSrc++;
               break;

         default:
            if ((*lpSrc != DOT ) && (*lpSrc != CHAR_NULL)) {

               lpSrc++;
            }

            if (ResLen < iResBufSize) {

               *(lpRes++) = *lpEd;
               ResLen++;
            }
            else
               return ERROR_INVALID_PARAMETER ;
            break;
         }
         lpEd++;

      }
      else {

         return ERROR_INVALID_PARAMETER ;
      }
   }

   if ((ResLen) < iResBufSize) {
      *lpRes = CHAR_NULL;
      return NO_ERROR ;
   }
   else
      return ERROR_INVALID_PARAMETER ;
}