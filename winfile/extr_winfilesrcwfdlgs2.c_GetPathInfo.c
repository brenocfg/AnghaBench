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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__* LPTSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_COLON ; 
 scalar_t__ CHAR_DQUOTE ; 
 scalar_t__ CHAR_SPACE ; 
 int FALSE ; 

VOID
GetPathInfo(LPTSTR szTemp, LPTSTR *ppDir, LPTSTR *ppFile, LPTSTR *ppPar)
{
   // handle quoted things
   BOOL bInQuotes=FALSE;

   // strip leading spaces

   for (*ppDir = szTemp; **ppDir == CHAR_SPACE; (*ppDir)++)
      ;

   // locate the parameters

   // Use bInQuotes and add if clause
   for (*ppPar = *ppDir; **ppPar && (**ppPar != CHAR_SPACE || bInQuotes) ; (*ppPar)++)
      if ( CHAR_DQUOTE == **ppPar ) bInQuotes = !bInQuotes;

   // locate the start of the filename and the extension.

   for (*ppFile = *ppPar; *ppFile > *ppDir; --(*ppFile)) {
      if (((*ppFile)[-1] == CHAR_COLON) || ((*ppFile)[-1] == CHAR_BACKSLASH))
         break;
   }
}