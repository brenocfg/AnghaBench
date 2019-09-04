#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cfFormat; } ;
struct TYPE_11__ {size_t dwScratchSpace; TYPE_1__ fmtetc; } ;
struct TYPE_10__ {scalar_t__ cfFormat; } ;
struct TYPE_9__ {size_t cPasteEntries; TYPE_5__* arrPasteEntries; int /*<<< orphan*/  lpSrcDataObj; } ;
typedef  TYPE_2__ OLEUIPASTESPECIALW ;
typedef  int /*<<< orphan*/  IEnumFORMATETC ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ FORMATETC ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  DATADIR_GET ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PS_PASTE ; 
 int /*<<< orphan*/  IDC_PS_PASTELIST ; 
 int /*<<< orphan*/  IDataObject_EnumFormatEtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IEnumFORMATETC_Next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,size_t*) ; 
 int /*<<< orphan*/  IEnumFORMATETC_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  add_entry_to_lb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static DWORD init_pastelist(HWND hdlg, OLEUIPASTESPECIALW *ps)
{
    IEnumFORMATETC *penum;
    HRESULT hr;
    FORMATETC fmts[20];
    DWORD fetched, items_added = 0;

    hr = IDataObject_EnumFormatEtc(ps->lpSrcDataObj, DATADIR_GET, &penum);
    if(FAILED(hr))
    {
        WARN("Unable to create IEnumFORMATETC\n");
        return 0;
    }

    /* The native version grabs only the first 20 fmts and we do the same */
    hr = IEnumFORMATETC_Next(penum, ARRAY_SIZE(fmts), fmts, &fetched);
    TRACE("got %d formats hr %08x\n", fetched, hr);

    if(SUCCEEDED(hr))
    {
        DWORD src_fmt, req_fmt;
        for(req_fmt = 0; req_fmt < ps->cPasteEntries; req_fmt++)
        {
            /* This is used by update_structure() to set nSelectedIndex on exit */
            ps->arrPasteEntries[req_fmt].dwScratchSpace = req_fmt;
            TRACE("req_fmt %x\n", ps->arrPasteEntries[req_fmt].fmtetc.cfFormat);
            for(src_fmt = 0; src_fmt < fetched; src_fmt++)
            {
                TRACE("\tenum'ed fmt %x\n", fmts[src_fmt].cfFormat);
                if(ps->arrPasteEntries[req_fmt].fmtetc.cfFormat == fmts[src_fmt].cfFormat)
                {
                    add_entry_to_lb(hdlg, IDC_PS_PASTELIST, ps->arrPasteEntries + req_fmt);
                    items_added++;
                    break;
                }
            }
        }
    }

    IEnumFORMATETC_Release(penum);
    EnableWindow(GetDlgItem(hdlg, IDC_PS_PASTE), items_added != 0);
    return items_added;
}