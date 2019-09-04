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
typedef  scalar_t__ WORD ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DEVMODEW ;

/* Variables and functions */
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCOUNT ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ ) ; 
 int DM_IN_BUFFER ; 
 int DM_IN_PROMPT ; 
 int DM_OUT_BUFFER ; 
 int /*<<< orphan*/  DocumentPropertiesW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  OpenPrinterW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmb2 ; 
 int /*<<< orphan*/  pagesetup_change_preview (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pagesetup_get_devmode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_get_devname (int /*<<< orphan*/ *) ; 
 scalar_t__ pagesetup_get_papersize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_release_a_devname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagesetup_release_devmode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_set_devmode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_update_orientation_buttons (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagesetup_update_papersize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pagesetup_printer_properties(HWND hDlg, pagesetup_data *data)
{
    HANDLE hprn;
    LPWSTR devname;
    DEVMODEW *dm;
    LRESULT count;
    int i;

    devname = pagesetup_get_devname(data);

    if (!OpenPrinterW(devname, &hprn, NULL))
    {
        FIXME("Call to OpenPrinter did not succeed!\n");
        pagesetup_release_a_devname(data, devname);
        return;
    }

    dm = pagesetup_get_devmode(data);
    DocumentPropertiesW(hDlg, hprn, devname, dm, dm, DM_IN_BUFFER | DM_OUT_BUFFER | DM_IN_PROMPT);
    pagesetup_set_devmode(data, dm);
    pagesetup_release_devmode(data, dm);
    pagesetup_release_a_devname(data, devname);
    ClosePrinter(hprn);

    /* Changing paper */
    pagesetup_update_papersize(data);
    pagesetup_update_orientation_buttons(hDlg, data);

    /* Changing paper preview */
    pagesetup_change_preview(data);

    /* Selecting paper in combo */
    count = SendDlgItemMessageW(hDlg, cmb2, CB_GETCOUNT, 0, 0);
    if(count != CB_ERR)
    {
        WORD paperword = pagesetup_get_papersize(data);
        for(i = 0; i < count; i++)
        {
            if(SendDlgItemMessageW(hDlg, cmb2, CB_GETITEMDATA, i, 0) == paperword) {
                SendDlgItemMessageW(hDlg, cmb2, CB_SETCURSEL, i, 0);
                break;
            }
        }
    }
}