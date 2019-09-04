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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DEVMODEW ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTDLG_SetUpPaperComboBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINTDLG_SetUpPrinterListComboW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmb1 ; 
 int /*<<< orphan*/  cmb2 ; 
 int /*<<< orphan*/  cmb3 ; 
 int /*<<< orphan*/ * pagesetup_get_devmode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_devname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_portname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_release_a_devname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagesetup_release_devmode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pagesetup_init_combos(HWND hDlg, pagesetup_data *data)
{
    DEVMODEW *dm;
    LPWSTR devname, portname;

    dm       = pagesetup_get_devmode(data);
    devname  = pagesetup_get_devname(data);
    portname = pagesetup_get_portname(data);

    PRINTDLG_SetUpPrinterListComboW(hDlg, cmb1, devname);
    PRINTDLG_SetUpPaperComboBoxW(hDlg, cmb2, devname, portname, dm);
    PRINTDLG_SetUpPaperComboBoxW(hDlg, cmb3, devname, portname, dm);

    pagesetup_release_a_devname(data, portname);
    pagesetup_release_a_devname(data, devname);
    pagesetup_release_devmode(data, dm);
}