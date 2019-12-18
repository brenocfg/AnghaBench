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

/* Variables and functions */
 int /*<<< orphan*/  CLOSEHANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CriticalSectionPath ; 
 int /*<<< orphan*/  D_Info () ; 
 int /*<<< orphan*/  D_NetCon () ; 
 int /*<<< orphan*/  D_Space () ; 
 int /*<<< orphan*/  D_Type () ; 
 int /*<<< orphan*/  D_VolInfo () ; 
 int /*<<< orphan*/  DeleteBitmaps () ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyDirRead () ; 
 int /*<<< orphan*/  DestroyWatchList () ; 
 int /*<<< orphan*/  DocDestruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 int /*<<< orphan*/  UpdateWaitQuit () ; 
 scalar_t__ bJAPAN ; 
 scalar_t__ bUpdateRun ; 
 int /*<<< orphan*/  hEventAcledit ; 
 int /*<<< orphan*/  hEventNetLoad ; 
 int /*<<< orphan*/  hEventUpdate ; 
 int /*<<< orphan*/  hEventUpdatePartial ; 
 scalar_t__ hFont ; 
 scalar_t__ hFontStatus ; 
 scalar_t__ hMPR ; 
 scalar_t__ hNTLanman ; 
 scalar_t__ hThreadUpdate ; 
 scalar_t__ hVersion ; 
 scalar_t__ hfmifsDll ; 
 scalar_t__ hfontDriveList ; 
 int /*<<< orphan*/  lpfnRegisterPenApp (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppDocBucket ; 
 int /*<<< orphan*/  ppProgBucket ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

VOID
FreeFileManager()
{
   if (hThreadUpdate && bUpdateRun) {
      UpdateWaitQuit();
      CloseHandle(hThreadUpdate);
   }

   DeleteCriticalSection(&CriticalSectionPath);

#define CLOSEHANDLE(handle) if (handle) CloseHandle(handle)

   CLOSEHANDLE(hEventNetLoad);
   CLOSEHANDLE(hEventAcledit);
   CLOSEHANDLE(hEventUpdate);
   CLOSEHANDLE(hEventUpdatePartial);

   DestroyWatchList();
   DestroyDirRead();

   D_Info();

   D_Type();
   D_Space();
   D_NetCon();
   D_VolInfo();

   DocDestruct(ppDocBucket);
   DocDestruct(ppProgBucket);

   if (lpfnRegisterPenApp)
      (*lpfnRegisterPenApp)(1, FALSE);

   DeleteBitmaps();

   if (hFont)
      DeleteObject(hFont);

   if (hfontDriveList)
      DeleteObject(hfontDriveList);

    // use the smaller font for Status bar so that messages fix in it.
    if( bJAPAN ) {
        if (hFontStatus)
            DeleteObject(hFontStatus);
    }

   //
   // Free the fmifs junk
   //
   if (hfmifsDll)
      FreeLibrary(hfmifsDll);

   if (hNTLanman)
      FreeLibrary(hNTLanman);

   if (hMPR)
      FreeLibrary(hMPR);

   if (hVersion)
      FreeLibrary(hVersion);

	OleUninitialize();

#undef CLOSEHANDLE
}