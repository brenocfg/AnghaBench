#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {scalar_t__ iBitmap; void* fsState; void* fsStyle; int /*<<< orphan*/  idCommand; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  scalar_t__ HIMAGELIST ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 void* BTNS_AUTOSIZE ; 
 int /*<<< orphan*/  CreateIconFromResourceEx (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned char* GetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_HASH ; 
 scalar_t__ IDC_HASH_TOOLBAR ; 
 int /*<<< orphan*/  IDC_SAVE ; 
 scalar_t__ IDC_SAVE_TOOLBAR ; 
 scalar_t__ IDI_HASH_16 ; 
 scalar_t__ IDI_SAVE_16 ; 
 int ILC_COLOR32 ; 
 int ILC_HIGHQUALITYSCALE ; 
 int ILC_MIRROR ; 
 int /*<<< orphan*/  ImageList_AddIcon (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ImageList_Create (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (scalar_t__) ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TB_ADDBUTTONS ; 
 int /*<<< orphan*/  TB_BUTTONSTRUCTSIZE ; 
 int /*<<< orphan*/  TB_SETIMAGELIST ; 
 int /*<<< orphan*/  TOOLBARCLASSNAME ; 
 int /*<<< orphan*/  TOOLBAR_STYLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _RT_RCDATA ; 
 int /*<<< orphan*/  hHashToolbar ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  hMainInstance ; 
 int /*<<< orphan*/  hSaveToolbar ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void CreateSmallButtons(HWND hDlg)
{
	HIMAGELIST hImageList;
	HICON hIconSave, hIconHash;
	int icon_offset = 0, i16 = GetSystemMetrics(SM_CXSMICON);
	TBBUTTON tbToolbarButtons[1];
	unsigned char* buffer;
	DWORD bufsize;

	if (i16 >= 28)
		icon_offset = 20;
	else if (i16 >= 20)
		icon_offset = 10;

	hSaveToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, TOOLBAR_STYLE,
		0, 0, 0, 0, hMainDialog, (HMENU)IDC_SAVE_TOOLBAR, hMainInstance, NULL);
	hImageList = ImageList_Create(i16, i16, ILC_COLOR32 | ILC_HIGHQUALITYSCALE | ILC_MIRROR, 1, 0);
	buffer = GetResource(hMainInstance, MAKEINTRESOURCEA(IDI_SAVE_16 + icon_offset), _RT_RCDATA, "save icon", &bufsize, FALSE);
	hIconSave = CreateIconFromResourceEx(buffer, bufsize, TRUE, 0x30000, 0, 0, 0);
	ImageList_AddIcon(hImageList, hIconSave);
	DestroyIcon(hIconSave);
	SendMessage(hSaveToolbar, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)hImageList);
	SendMessage(hSaveToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	memset(tbToolbarButtons, 0, sizeof(TBBUTTON));
	tbToolbarButtons[0].idCommand = IDC_SAVE;
	tbToolbarButtons[0].fsStyle = BTNS_AUTOSIZE;
	tbToolbarButtons[0].fsState = TBSTATE_ENABLED;
	tbToolbarButtons[0].iBitmap = 0;
	SendMessage(hSaveToolbar, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbToolbarButtons);

	hHashToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, TOOLBAR_STYLE,
		0, 0, 0, 0, hMainDialog, (HMENU)IDC_HASH_TOOLBAR, hMainInstance, NULL);
	hImageList = ImageList_Create(i16, i16, ILC_COLOR32 | ILC_HIGHQUALITYSCALE | ILC_MIRROR, 1, 0);
	buffer = GetResource(hMainInstance, MAKEINTRESOURCEA(IDI_HASH_16 + icon_offset), _RT_RCDATA, "hash icon", &bufsize, FALSE);
	hIconHash = CreateIconFromResourceEx(buffer, bufsize, TRUE, 0x30000, 0, 0, 0);
	ImageList_AddIcon(hImageList, hIconHash);
	DestroyIcon(hIconHash);
	SendMessage(hHashToolbar, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)hImageList);
	SendMessage(hHashToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	memset(tbToolbarButtons, 0, sizeof(TBBUTTON));
	tbToolbarButtons[0].idCommand = IDC_HASH;
	tbToolbarButtons[0].fsStyle = BTNS_AUTOSIZE;
	tbToolbarButtons[0].fsState = TBSTATE_ENABLED;
	tbToolbarButtons[0].iBitmap = 0;
	SendMessage(hHashToolbar, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbToolbarButtons);
}