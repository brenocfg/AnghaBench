#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {size_t* dwLines; scalar_t__* lpszRemoteNameMinusFour; } ;
typedef  scalar_t__ LPTSTR ;
typedef  size_t DWORD ;
typedef  size_t DRIVE ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_NEWLINE ; 
 scalar_t__ DRIVE_INFO_NAME_HEADER ; 
 scalar_t__ StrChr (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* aDriveInfo ; 

VOID
NetCon_UpdateLines(DRIVE drive, DWORD dwType)
{
   LPTSTR lpNext;
   DWORD dwLines=0;

   //
   // Scan for the number of \n in the text
   //

   lpNext = aDriveInfo[drive].lpszRemoteNameMinusFour[dwType] +
      DRIVE_INFO_NAME_HEADER;

   do
   {
      dwLines++;
      lpNext = StrChr(lpNext, CHAR_NEWLINE);
   } while (lpNext++);

   aDriveInfo[drive].dwLines[dwType] = dwLines;
}