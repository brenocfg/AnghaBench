#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_7__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_6__ {void** szShare; void** szVolume; void** szPath; int /*<<< orphan*/  dwFreeSpace; int /*<<< orphan*/  dwTotalSpace; } ;
struct TYPE_5__ {void** szShare; void** szVolume; int /*<<< orphan*/  szPath; int /*<<< orphan*/  dwFreeSpace; int /*<<< orphan*/  dwTotalSpace; } ;
typedef  void** LPWSTR ;
typedef  TYPE_1__* LPFMS_GETDRIVEINFOW ;
typedef  TYPE_2__* LPFMS_GETDRIVEINFOA ;
typedef  scalar_t__ LPARAM ;
typedef  long LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ALTNAME_REG ; 
 void* CHAR_NULL ; 
 int /*<<< orphan*/  COUNTOF (void**) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DRIVEID (void**) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FM_GETDRIVEINFOW ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/  GetVolumeLabel (int /*<<< orphan*/ ,void***,int /*<<< orphan*/ ) ; 
 scalar_t__ ISUNCPATH (void**) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  StrNCpy (void**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripBackslash (void**) ; 
 int /*<<< orphan*/  U_NetCon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAITNET () ; 
 scalar_t__ WFGetConnection (int /*<<< orphan*/ ,void***,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,void**) ; 
 TYPE_4__ qFreeSpace ; 
 TYPE_3__ qTotalSpace ; 

LONG
GetDriveInfo(HWND hwnd, UINT uMsg, LPARAM lParam)
{
#define lpSelW ((LPFMS_GETDRIVEINFOW)lParam)
#define lpSelA ((LPFMS_GETDRIVEINFOA)lParam)

   WCHAR szPath[MAXPATHLEN];
   LPWSTR lpszVol;

   // this has to work for hwnd a tree or search window

   SendMessage(hwnd, FS_GETDIRECTORY, COUNTOF(szPath), (LPARAM)szPath);
   StripBackslash(szPath);

   if (FM_GETDRIVEINFOW == uMsg)
   {
      lpSelW->dwTotalSpace = qTotalSpace.LowPart;
      lpSelW->dwFreeSpace = qFreeSpace.LowPart;

      lstrcpy(lpSelW->szPath, szPath);

      if (ISUNCPATH(szPath))
      {
         lpSelW->szVolume[0] = CHAR_NULL;
      }
      else
      {
         GetVolumeLabel(DRIVEID(szPath), &lpszVol, FALSE);
         StrNCpy(lpSelW->szVolume, lpszVol, COUNTOF(lpSelW->szVolume)-1);
      }
   }
   else
   {
      lpSelA->dwTotalSpace = qTotalSpace.LowPart;
      lpSelA->dwFreeSpace = qFreeSpace.LowPart;

      if (!WideCharToMultiByte( CP_ACP,
                                0,
                                szPath,
                                -1,
                                lpSelA->szPath,
                                COUNTOF(lpSelA->szPath),
                                NULL,
                                NULL ))
      {
         lpSelA->szPath[0] = CHAR_NULL;
      }

      if (ISUNCPATH(szPath))
      {
         lpSelW->szVolume[0] = CHAR_NULL;
      }
      else
      {
         GetVolumeLabel(DRIVEID(szPath), &lpszVol, FALSE);

         if (!WideCharToMultiByte( CP_ACP,
                                   0,
                                   lpszVol,
                                   -1,
                                   lpSelA->szVolume,
                                   COUNTOF(lpSelA->szVolume),
                                   NULL,
                                   NULL ))
         {
            lpSelA->szVolume[0] = CHAR_NULL;
         }
         lpSelA->szVolume[COUNTOF(lpSelA->szVolume)-1] = CHAR_NULL;
      }
   }

   //
   // Force update
   //

   WAITNET();

   if (ISUNCPATH(szPath))
   {
       lpSelW->szShare[0] = CHAR_NULL;
       return (1L);
   }

   U_NetCon(DRIVEID(szPath));

   if (WFGetConnection(DRIVEID(szPath), &lpszVol, FALSE, ALTNAME_REG)) {
      lpSelW->szShare[0] = CHAR_NULL;
   } else {

      if (FM_GETDRIVEINFOW == uMsg) {

         StrNCpy(lpSelW->szShare, lpszVol, COUNTOF(lpSelW->szShare)-1);
         lpSelW->szShare[COUNTOF(lpSelW->szShare)-1] = CHAR_NULL;

      } else {

         if (!WideCharToMultiByte(CP_ACP, 0, lpszVol, -1,
            lpSelA->szShare, COUNTOF(lpSelA->szShare), NULL, NULL)) {

            lpSelA->szShare[0] = CHAR_NULL;
         }
         lpSelA->szShare[COUNTOF(lpSelA->szShare)-1] = CHAR_NULL;
      }
   }

   return (1L);
}