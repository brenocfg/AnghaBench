#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prnt ;
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {scalar_t__ dmDriverExtra; scalar_t__ dmSize; } ;
struct TYPE_12__ {int wDriverOffset; int wDeviceOffset; int wOutputOffset; } ;
struct TYPE_11__ {int lStructSize; scalar_t__ hDevNames; scalar_t__ hDevMode; int /*<<< orphan*/  hwndOwner; scalar_t__ Flags; } ;
typedef  TYPE_1__ PRINTDLGW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ DEVNAMES ;
typedef  TYPE_3__ DEVMODEW ;

/* Variables and functions */
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 void* GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  PRINTDLG_CreateDevNamesW (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PrintDlgW (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* pagesetup_get_devmode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_devname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_drvname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_portname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_init_combos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_release_a_devname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagesetup_release_devmode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pagesetup_set_devmode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pagesetup_set_devnames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pagesetup_change_printer_dialog(HWND hDlg, pagesetup_data *data)
{
    PRINTDLGW prnt;
    LPWSTR drvname, devname, portname;
    DEVMODEW *tmp_dm, *dm;

    memset(&prnt, 0, sizeof(prnt));
    prnt.lStructSize = sizeof(prnt);
    prnt.Flags     = 0;
    prnt.hwndOwner = hDlg;

    drvname = pagesetup_get_drvname(data);
    devname = pagesetup_get_devname(data);
    portname = pagesetup_get_portname(data);
    prnt.hDevNames = 0;
    PRINTDLG_CreateDevNamesW(&prnt.hDevNames, drvname, devname, portname);
    pagesetup_release_a_devname(data, portname);
    pagesetup_release_a_devname(data, devname);
    pagesetup_release_a_devname(data, drvname);

    tmp_dm = pagesetup_get_devmode(data);
    prnt.hDevMode = GlobalAlloc(GMEM_MOVEABLE, tmp_dm->dmSize + tmp_dm->dmDriverExtra);
    dm = GlobalLock(prnt.hDevMode);
    memcpy(dm, tmp_dm, tmp_dm->dmSize + tmp_dm->dmDriverExtra);
    GlobalUnlock(prnt.hDevMode);
    pagesetup_release_devmode(data, tmp_dm);

    if (PrintDlgW(&prnt))
    {
        DEVMODEW *dm = GlobalLock(prnt.hDevMode);
        DEVNAMES *dn = GlobalLock(prnt.hDevNames);

        pagesetup_set_devnames(data, (WCHAR*)dn + dn->wDriverOffset,
                               (WCHAR*)dn + dn->wDeviceOffset, (WCHAR *)dn + dn->wOutputOffset);
        pagesetup_set_devmode(data, dm);
        GlobalUnlock(prnt.hDevNames);
        GlobalUnlock(prnt.hDevMode);
        pagesetup_init_combos(hDlg, data);
    }

    GlobalFree(prnt.hDevMode);
    GlobalFree(prnt.hDevNames);

}