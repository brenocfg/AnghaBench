#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  b1 ;
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  hdrivebar; scalar_t__* drives; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hMainWnd; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int iBitmap; int /*<<< orphan*/  iString; int /*<<< orphan*/  idCommand; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ TBBUTTON ;
typedef  scalar_t__* PWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  BTNS_BUTTON ; 
 int BUFFER_LEN ; 
 int CCS_NOMOVEY ; 
 int /*<<< orphan*/  CreateToolbarEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
#define  DRIVE_CDROM 131 
#define  DRIVE_RAMDISK 130 
#define  DRIVE_REMOTE 129 
#define  DRIVE_REMOVABLE 128 
 int GetDriveTypeW (scalar_t__*) ; 
 int /*<<< orphan*/  GetLogicalDriveStringsW (int,scalar_t__*) ; 
 TYPE_3__ Globals ; 
 int /*<<< orphan*/  IDB_DRIVEBAR ; 
 int /*<<< orphan*/  IDS_SHELL ; 
 int /*<<< orphan*/  IDW_DRIVEBAR ; 
 int /*<<< orphan*/  ID_DRIVE_FIRST ; 
 int /*<<< orphan*/  ID_DRIVE_SHELL_NS ; 
 int /*<<< orphan*/  ID_DRIVE_UNIX_FS ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int TBSTYLE_LIST ; 
 int /*<<< orphan*/  TB_ADDSTRINGW ; 
 int /*<<< orphan*/  TB_INSERTBUTTONW ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  load_string (char*,int,int /*<<< orphan*/ ) ; 
 int lstrlenW (char*) ; 

__attribute__((used)) static void create_drive_bar(void)
{
	TBBUTTON drivebarBtn = {0, 0, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0};
	WCHAR b1[BUFFER_LEN];
	int btn = 1;
	PWSTR p;

	GetLogicalDriveStringsW(BUFFER_LEN, Globals.drives);

	Globals.hdrivebar = CreateToolbarEx(Globals.hMainWnd, WS_CHILD|WS_VISIBLE|CCS_NOMOVEY|TBSTYLE_LIST,
				IDW_DRIVEBAR, 2, Globals.hInstance, IDB_DRIVEBAR, &drivebarBtn,
				0, 16, 13, 16, 13, sizeof(TBBUTTON));

#ifdef __WINE__
	/* insert unix file system button */
	b1[0] = '/';
	b1[1] = '\0';
	b1[2] = '\0';
	SendMessageW(Globals.hdrivebar, TB_ADDSTRINGW, 0, (LPARAM)b1);

	drivebarBtn.idCommand = ID_DRIVE_UNIX_FS;
	SendMessageW(Globals.hdrivebar, TB_INSERTBUTTONW, btn++, (LPARAM)&drivebarBtn);
	drivebarBtn.iString++;
#endif
	/* insert shell namespace button */
	load_string(b1, sizeof(b1)/sizeof(b1[0]), IDS_SHELL);
	b1[lstrlenW(b1)+1] = '\0';
	SendMessageW(Globals.hdrivebar, TB_ADDSTRINGW, 0, (LPARAM)b1);

	drivebarBtn.idCommand = ID_DRIVE_SHELL_NS;
	SendMessageW(Globals.hdrivebar, TB_INSERTBUTTONW, btn++, (LPARAM)&drivebarBtn);
	drivebarBtn.iString++;

	/* register windows drive root strings */
	SendMessageW(Globals.hdrivebar, TB_ADDSTRINGW, 0, (LPARAM)Globals.drives);

	drivebarBtn.idCommand = ID_DRIVE_FIRST;

	for(p=Globals.drives; *p; ) {
		switch(GetDriveTypeW(p)) {
			case DRIVE_REMOVABLE:	drivebarBtn.iBitmap = 1;	break;
			case DRIVE_CDROM:		drivebarBtn.iBitmap = 3;	break;
			case DRIVE_REMOTE:		drivebarBtn.iBitmap = 4;	break;
			case DRIVE_RAMDISK:		drivebarBtn.iBitmap = 5;	break;
			default:/*DRIVE_FIXED*/	drivebarBtn.iBitmap = 2;
		}

		SendMessageW(Globals.hdrivebar, TB_INSERTBUTTONW, btn++, (LPARAM)&drivebarBtn);
		drivebarBtn.idCommand++;
		drivebarBtn.iString++;

		while(*p++);
	}
}