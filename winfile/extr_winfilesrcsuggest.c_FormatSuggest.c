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
typedef  int* PDWORD ;
typedef  size_t INT ;
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_EXE_MARKED_INVALID 136 
#define  ERROR_INFLOOP_IN_RELOC_CHAIN 135 
#define  ERROR_INVALID_MINALLOCSIZE 134 
#define  ERROR_INVALID_MODULETYPE 133 
 int ERROR_INVALID_ORDINAL ; 
#define  ERROR_INVALID_SEGDPL 132 
#define  ERROR_INVALID_STACKSEG 131 
#define  ERROR_INVALID_STARTING_CODESEG 130 
#define  ERROR_ITERATED_DATA_EXCEEDS_64k 129 
#define  ERROR_RELOC_CHAIN_XEEDS_SEGLIM 128 
 int** adwSuggest ; 

PDWORD
FormatSuggest( DWORD dwError )
{
   PDWORD pdwReturn = NULL;
   INT i;

   // If error == 0, just return...
   if (!dwError)
      return NULL;

   // scan through all suggests

   switch(dwError) {
   case ERROR_EXE_MARKED_INVALID:
   case ERROR_ITERATED_DATA_EXCEEDS_64k:
   case ERROR_INVALID_STACKSEG:
   case ERROR_INVALID_STARTING_CODESEG:
   case ERROR_INVALID_MODULETYPE:
   case ERROR_INVALID_MINALLOCSIZE:
   case ERROR_INVALID_SEGDPL:
   case ERROR_RELOC_CHAIN_XEEDS_SEGLIM:
   case ERROR_INFLOOP_IN_RELOC_CHAIN:
      dwError = ERROR_INVALID_ORDINAL;

      // no break

   default:
      for (i=0;adwSuggest[i][0]; i++) {
         if ( adwSuggest[i][0] == dwError ) {
            pdwReturn = adwSuggest[i];
            break;
         }
      }
   }
   return pdwReturn;
}