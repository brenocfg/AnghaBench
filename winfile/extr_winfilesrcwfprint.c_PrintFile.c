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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSelectedDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_WAIT ; 
 int IDS_ASSOCINCOMPLETE ; 
 int IDS_BADPATHMSG ; 
 int IDS_DDEFAIL ; 
 int IDS_FILENOTFOUNDMSG ; 
 int IDS_NOACCESSFILE ; 
 int IDS_NOASSOCMSG ; 
 int IDS_PRINTMEMORY ; 
 int IDS_SHAREERROR ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
#define  SE_ERR_ASSOCINCOMPLETE 133 
#define  SE_ERR_DDEBUSY 132 
#define  SE_ERR_DDEFAIL 131 
#define  SE_ERR_DDETIMEOUT 130 
#define  SE_ERR_NOASSOC 129 
#define  SE_ERR_SHARE 128 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetErrorMode (int) ; 
 scalar_t__ ShellExecute (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ShowCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  szNULL ; 

DWORD
PrintFile(HWND hwnd, LPTSTR szFile)
{
   DWORD          ret;
   INT           iCurCount;
   INT           i;
   HCURSOR       hCursor;
   WCHAR      szDir[MAXPATHLEN];

   ret = 0;

   hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
   iCurCount = ShowCursor(TRUE) - 1;

   //
   // This returns Ansi chars, and that's what ShellExecute expects
   //
   GetSelectedDirectory(0, szDir);

   //
   // open the object
   //
   SetErrorMode(0);
   ret = (DWORD)ShellExecute(hwnd, L"print", szFile, szNULL, szDir, SW_SHOWNORMAL);
   SetErrorMode(1);

   switch (ret) {
   case 0:
   case 8:
      ret = IDS_PRINTMEMORY;
      break;

   case 2:
      ret = IDS_FILENOTFOUNDMSG;
      break;

   case 3:
      ret = IDS_BADPATHMSG;
      break;

   case 5:
      ret = IDS_NOACCESSFILE;
      break;

   case SE_ERR_SHARE:
      ret = IDS_SHAREERROR;
      break;

   case SE_ERR_ASSOCINCOMPLETE:
      ret = IDS_ASSOCINCOMPLETE;
      break;

   case SE_ERR_DDETIMEOUT:
   case SE_ERR_DDEFAIL:
   case SE_ERR_DDEBUSY:
      ret = IDS_DDEFAIL;
      break;

   case SE_ERR_NOASSOC:
      ret = IDS_NOASSOCMSG;
      break;

   default:
      if (ret <= 32)
         goto EPExit;
      ret = 0;
   }

EPExit:
   i = ShowCursor(FALSE);

   //
   // Make sure that the cursor count is still balanced.
   //
   if (i != iCurCount)
      ShowCursor(TRUE);

   SetCursor(hCursor);

   return(ret);
}