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
typedef  void* PVOID ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IDS_FMIFSLOADERR ; 
 int /*<<< orphan*/  IDS_WINFILE ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int MB_SYSTEMMODAL ; 
 int /*<<< orphan*/  MyMessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * hfmifsDll ; 
 int /*<<< orphan*/  hwndFrame ; 
 void* lpfnDiskCopy ; 
 void* lpfnFormat ; 
 void* lpfnQuerySupportedMedia ; 
 void* lpfnSetLabel ; 
 int /*<<< orphan*/  szFmifsDll ; 

BOOL
FmifsLoaded()
{
   // Get a filename from the dialog...
   // Load the fmifs dll.

   if (hfmifsDll < (HANDLE)32) {
      hfmifsDll = LoadLibrary(szFmifsDll);
      if (hfmifsDll < (HANDLE)32) {
         /* FMIFS not available. */
         MyMessageBox(hwndFrame, IDS_WINFILE, IDS_FMIFSLOADERR, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
         hfmifsDll = NULL;
         return FALSE;
      }
      else {
         lpfnFormat = (PVOID)GetProcAddress(hfmifsDll, "Format");
         lpfnQuerySupportedMedia = (PVOID)GetProcAddress(hfmifsDll, "QuerySupportedMedia");

         lpfnSetLabel = (PVOID)GetProcAddress(hfmifsDll, "SetLabel");
         lpfnDiskCopy = (PVOID)GetProcAddress(hfmifsDll, "DiskCopy");
         if (!lpfnFormat || !lpfnQuerySupportedMedia ||
            !lpfnSetLabel || !lpfnDiskCopy) {

            MyMessageBox(hwndFrame, IDS_WINFILE, IDS_FMIFSLOADERR, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
            FreeLibrary(hfmifsDll);
            hfmifsDll = NULL;
            return FALSE;
         }
      }
   }
   return TRUE;
}