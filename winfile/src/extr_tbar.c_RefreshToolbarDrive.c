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
typedef  long LPARAM ;
typedef  int INT ;
typedef  size_t DRIVEIND ;
typedef  scalar_t__ DRIVE ;

/* Variables and functions */
 int /*<<< orphan*/  CB_DELETESTRING ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 scalar_t__ IsCDRomDrive (scalar_t__) ; 
 scalar_t__ IsRemovableDrive (scalar_t__) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  U_VolInfo (scalar_t__) ; 
 int /*<<< orphan*/  hwndDriveList ; 
 scalar_t__* rgiDrive ; 

VOID
RefreshToolbarDrive(DRIVEIND iDriveInd)
{
   INT iSel;
   DRIVE drive;

   iSel = (INT)SendMessage(hwndDriveList, CB_GETCURSEL, 0, 0L);

   SendMessage(hwndDriveList, CB_DELETESTRING, iDriveInd, 0L);

   drive = rgiDrive[iDriveInd];
   //
   // For floppy drives, when we refresh, we should pickup the
   // drive label.
   //

   if (IsRemovableDrive(drive) || IsCDRomDrive(drive))
      U_VolInfo(drive);

   //
   // We must tell ourselves which drive we are
   // working on.
   //
   SendMessage(hwndDriveList, CB_INSERTSTRING,iDriveInd, (LPARAM)drive);

   if (iSel!=-1) {

      SendMessage(hwndDriveList, CB_SETCURSEL, iSel, 0L);
   }
}