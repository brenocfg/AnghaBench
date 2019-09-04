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
typedef  scalar_t__ UINT ;
typedef  scalar_t__* LPTSTR ;

/* Variables and functions */
 scalar_t__ CHAR_BACKSLASH ; 
 scalar_t__ CHAR_COLON ; 
 scalar_t__ CHAR_NULL ; 

UINT
RemoveLast(LPTSTR pFile)
{
  LPTSTR pT;
  UINT uChars = 0;

  for (pT=pFile; *pFile; pFile++) {

     if (*pFile == CHAR_BACKSLASH) {

        pT = pFile;
        uChars = 0;

     } else if (*pFile == CHAR_COLON) {

        if (pFile[1] ==CHAR_BACKSLASH) {

           pFile++;

        }

        pT = pFile + 1;

        uChars = 0;
        continue;
     }
     uChars++;
  }

  *pT = CHAR_NULL;
  return uChars;
}