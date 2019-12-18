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
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDM_DISCONNECT ; 
 int /*<<< orphan*/  IsCDRomDrive (int /*<<< orphan*/ ) ; 
 scalar_t__ IsRemoteDrive (int /*<<< orphan*/ ) ; 
 int MF_BYCOMMAND ; 
 int MF_ENABLED ; 
 int MF_GRAYED ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TB_ENABLEBUTTON ; 
 size_t cDrives ; 
 int /*<<< orphan*/  hwndFrame ; 
 int /*<<< orphan*/  hwndToolbar ; 
 int /*<<< orphan*/ * rgiDrive ; 

VOID
EnableDisconnectButton(void)
{
   INT i;

   for (i=0; i<cDrives; i++)
      if (!IsCDRomDrive(rgiDrive[i]) && IsRemoteDrive(rgiDrive[i]))
         break;

   SendMessage(hwndToolbar, TB_ENABLEBUTTON, IDM_DISCONNECT, i<cDrives);

   EnableMenuItem(GetMenu(hwndFrame), IDM_DISCONNECT, i<cDrives ?
      MF_BYCOMMAND | MF_ENABLED :
      MF_BYCOMMAND | MF_GRAYED );

}