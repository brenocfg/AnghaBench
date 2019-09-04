#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int Flags; scalar_t__ nMinPage; scalar_t__ nMaxPage; int nCopies; scalar_t__ nToPage; scalar_t__ nFromPage; } ;
struct TYPE_12__ {char* pPortName; } ;
struct TYPE_8__ {int dmCopies; int /*<<< orphan*/  dmPrintQuality; } ;
struct TYPE_9__ {TYPE_1__ s1; } ;
struct TYPE_11__ {int dmFields; int dmCollate; int /*<<< orphan*/  dmYResolution; TYPE_2__ u1; } ;
struct TYPE_10__ {TYPE_5__* lpPrinterInfo; TYPE_4__* lpDevMode; TYPE_6__* lpPrintDlg; } ;
typedef  TYPE_3__ PRINT_PTRA ;
typedef  TYPE_4__* PDEVMODEA ;
typedef  TYPE_5__* LPPRINTER_INFO_2A ;
typedef  TYPE_6__* LPPRINTDLGA ;
typedef  void* LONG ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 int DM_COLLATE ; 
 int DM_COPIES ; 
 int DM_PRINTQUALITY ; 
 int DM_YRESOLUTION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 void* GetDlgItemInt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (void*) ; 
 scalar_t__ IsDlgButtonChecked (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (void*) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PD32_INVALID_PAGE_RANGE ; 
 int /*<<< orphan*/  PD32_PRINT_TITLE ; 
 int PD_COLLATE ; 
 int PD_PAGENUMS ; 
 int PD_PRINTSETUP ; 
 int PD_PRINTTOFILE ; 
 int PD_SELECTION ; 
 int PD_USEDEVMODECOPIESANDCOLLATE ; 
 void* SendMessageA (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chx1 ; 
 int /*<<< orphan*/  chx2 ; 
 int /*<<< orphan*/  cmb1 ; 
 int /*<<< orphan*/  edt1 ; 
 int /*<<< orphan*/  edt2 ; 
 int /*<<< orphan*/  edt3 ; 
 int /*<<< orphan*/  rad2 ; 
 int /*<<< orphan*/  rad3 ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static BOOL PRINTDLG_UpdatePrintDlgA(HWND hDlg,
				    PRINT_PTRA* PrintStructures)
{
    LPPRINTDLGA       lppd = PrintStructures->lpPrintDlg;
    PDEVMODEA         lpdm = PrintStructures->lpDevMode;
    LPPRINTER_INFO_2A pi = PrintStructures->lpPrinterInfo;


    if(!lpdm) {
	FIXME("No lpdm ptr?\n");
	return FALSE;
    }


    if(!(lppd->Flags & PD_PRINTSETUP)) {
        /* check whether nFromPage and nToPage are within range defined by
	 * nMinPage and nMaxPage
	 */
        if (IsDlgButtonChecked(hDlg, rad3) == BST_CHECKED) { /* Pages */
	    WORD nToPage;
	    WORD nFromPage;
            BOOL translated;
	    nFromPage = GetDlgItemInt(hDlg, edt1, NULL, FALSE);
	    nToPage   = GetDlgItemInt(hDlg, edt2, &translated, FALSE);

	    /* if no ToPage value is entered, use the FromPage value */
	    if(!translated) nToPage = nFromPage;

	    if (nFromPage < lppd->nMinPage || nFromPage > lppd->nMaxPage ||
		nToPage < lppd->nMinPage || nToPage > lppd->nMaxPage) {
	        WCHAR resourcestr[256];
		WCHAR resultstr[256];
		LoadStringW(COMDLG32_hInstance, PD32_INVALID_PAGE_RANGE, resourcestr, 255);
		wsprintfW(resultstr,resourcestr, lppd->nMinPage, lppd->nMaxPage);
		LoadStringW(COMDLG32_hInstance, PD32_PRINT_TITLE, resourcestr, 255);
		MessageBoxW(hDlg, resultstr, resourcestr, MB_OK | MB_ICONWARNING);
		return FALSE;
	    }
	    lppd->nFromPage = nFromPage;
	    lppd->nToPage   = nToPage;
	    lppd->Flags |= PD_PAGENUMS;
	}
	else
	    lppd->Flags &= ~PD_PAGENUMS;

        if (IsDlgButtonChecked(hDlg, rad2) == BST_CHECKED) /* Selection */
            lppd->Flags |= PD_SELECTION;
        else
            lppd->Flags &= ~PD_SELECTION;

	if (IsDlgButtonChecked(hDlg, chx1) == BST_CHECKED) {/* Print to file */
	    static char file[] = "FILE:";
	    lppd->Flags |= PD_PRINTTOFILE;
	    pi->pPortName = file;
	}

	if (IsDlgButtonChecked(hDlg, chx2) == BST_CHECKED) { /* Collate */
	    FIXME("Collate lppd not yet implemented as output\n");
	}

	/* set PD_Collate and nCopies */
	if (lppd->Flags & PD_USEDEVMODECOPIESANDCOLLATE) {
	  /*  The application doesn't support multiple copies or collate...
	   */
	    lppd->Flags &= ~PD_COLLATE;
	    lppd->nCopies = 1;
	  /* if the printer driver supports it... store info there
	   * otherwise no collate & multiple copies !
	   */
	    if (lpdm->dmFields & DM_COLLATE)
	        lpdm->dmCollate =
		  (IsDlgButtonChecked(hDlg, chx2) == BST_CHECKED);
	    if (lpdm->dmFields & DM_COPIES)
	        lpdm->u1.s1.dmCopies = GetDlgItemInt(hDlg, edt3, NULL, FALSE);
	} else {
            /* Application is responsible for multiple copies */
	    if (IsDlgButtonChecked(hDlg, chx2) == BST_CHECKED)
	        lppd->Flags |= PD_COLLATE;
            else
               lppd->Flags &= ~PD_COLLATE;
            lppd->nCopies = GetDlgItemInt(hDlg, edt3, NULL, FALSE);
            /* multiple copies already included in the document. Driver must print only one copy */
            lpdm->u1.s1.dmCopies = 1;
	}

	/* Print quality, PrintDlg16 */
	if(GetDlgItem(hDlg, cmb1))
	{
	    HWND hQuality = GetDlgItem(hDlg, cmb1);
	    int Sel = SendMessageA(hQuality, CB_GETCURSEL, 0, 0);

	    if(Sel != CB_ERR)
	    {
		LONG dpi = SendMessageA(hQuality, CB_GETITEMDATA, Sel, 0);
		lpdm->dmFields |= DM_PRINTQUALITY | DM_YRESOLUTION;
		lpdm->u1.s1.dmPrintQuality = LOWORD(dpi);
		lpdm->dmYResolution = HIWORD(dpi);
	    }
	}
    }
    return TRUE;
}