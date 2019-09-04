#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  scalar_t__ WCHAR ;
struct TYPE_6__ {scalar_t__ dmPaperSize; scalar_t__ dmDefaultSource; } ;
struct TYPE_7__ {TYPE_1__ s1; } ;
struct TYPE_8__ {TYPE_2__ u1; } ;
typedef  TYPE_3__* LPDEVMODEW ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int DC_BINNAMES ; 
 int DC_BINS ; 
 int DC_PAPERNAMES ; 
 int DC_PAPERS ; 
 scalar_t__ DMPAPER_USER ; 
 int DeviceCapabilitiesW (scalar_t__ const*,scalar_t__ const*,int,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ SendDlgItemMessageA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int cmb2 ; 
 int cmb3 ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__ const*) ; 

__attribute__((used)) static BOOL PRINTDLG_SetUpPaperComboBoxW(HWND hDlg,
					int   nIDComboBox,
					const WCHAR* PrinterName,
					const WCHAR* PortName,
					LPDEVMODEW dm)
{
    int     i;
    int     NrOfEntries;
    WCHAR*  Names;
    WORD*   Words;
    DWORD   Sel, old_Sel;
    WORD    oldWord = 0, newWord = 0; /* DMPAPER_ and DMBIN_ start at 1 */
    int     NamesSize;
    int     fwCapability_Names;
    int     fwCapability_Words;

    TRACE(" Printer: %s, Port: %s, ComboID: %d\n",debugstr_w(PrinterName),debugstr_w(PortName),nIDComboBox);

    /* query the dialog box for the current selected value */
    Sel = SendDlgItemMessageW(hDlg, nIDComboBox, CB_GETCURSEL, 0, 0);
    if(Sel != CB_ERR) {
        /* we enter here only if a different printer is selected after
         * the Print Setup dialog is opened. The current settings are
         * stored into the newly selected printer.
         */
        oldWord = SendDlgItemMessageW(hDlg, nIDComboBox, CB_GETITEMDATA,
                                      Sel, 0);

        if(oldWord >= DMPAPER_USER) /* DMPAPER_USER == DMBIN_USER */
            oldWord = 0; /* There's no point in trying to keep custom
                            paper / bin sizes across printers */
    }

    if (dm)
        newWord = (nIDComboBox == cmb2) ? dm->u1.s1.dmPaperSize : dm->u1.s1.dmDefaultSource;

    if (nIDComboBox == cmb2) {
         NamesSize          = 64;
         fwCapability_Names = DC_PAPERNAMES;
         fwCapability_Words = DC_PAPERS;
    } else {
         nIDComboBox        = cmb3;
         NamesSize          = 24;
         fwCapability_Names = DC_BINNAMES;
         fwCapability_Words = DC_BINS;
    }

    NrOfEntries = DeviceCapabilitiesW(PrinterName, PortName,
                                      fwCapability_Names, NULL, dm);
    if (NrOfEntries == 0)
         WARN("no Name Entries found!\n");
    else if (NrOfEntries < 0)
         return FALSE;

    if(DeviceCapabilitiesW(PrinterName, PortName, fwCapability_Words, NULL, dm)
       != NrOfEntries) {
        ERR("Number of caps is different\n");
	NrOfEntries = 0;
    }

    Names = HeapAlloc(GetProcessHeap(),0, NrOfEntries*sizeof(WCHAR)*NamesSize);
    Words = HeapAlloc(GetProcessHeap(),0, NrOfEntries*sizeof(WORD));
    DeviceCapabilitiesW(PrinterName, PortName, fwCapability_Names, Names, dm);
    NrOfEntries = DeviceCapabilitiesW(PrinterName, PortName,
                                      fwCapability_Words, Words, dm);

    /* reset any current content in the combobox */
    SendDlgItemMessageW(hDlg, nIDComboBox, CB_RESETCONTENT, 0, 0);

    /* store new content */
    for (i = 0; i < NrOfEntries; i++) {
        DWORD pos = SendDlgItemMessageW(hDlg, nIDComboBox, CB_ADDSTRING, 0,
					(LPARAM)(&Names[i*NamesSize]) );
	SendDlgItemMessageW(hDlg, nIDComboBox, CB_SETITEMDATA, pos,
			    Words[i]);
    }

    /* Look for old selection or the new default.
       Can't do this is previous loop since item order will change as more items are added */
    Sel = 0;
    old_Sel = NrOfEntries;
    for (i = 0; i < NrOfEntries; i++) {
        if(SendDlgItemMessageW(hDlg, nIDComboBox, CB_GETITEMDATA, i, 0) ==
	   oldWord) {
	    old_Sel = i;
	    break;
	}
        if(SendDlgItemMessageA(hDlg, nIDComboBox, CB_GETITEMDATA, i, 0) == newWord)
            Sel = i;
    }

    if(old_Sel < NrOfEntries)
    {
        if (dm)
        {
            if(nIDComboBox == cmb2)
                dm->u1.s1.dmPaperSize = oldWord;
            else
                dm->u1.s1.dmDefaultSource = oldWord;
        }
        Sel = old_Sel;
    }

    SendDlgItemMessageW(hDlg, nIDComboBox, CB_SETCURSEL, Sel, 0);

    HeapFree(GetProcessHeap(),0,Words);
    HeapFree(GetProcessHeap(),0,Names);
    return TRUE;
}