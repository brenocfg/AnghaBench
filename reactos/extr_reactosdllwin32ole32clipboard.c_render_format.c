#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cfFormat; int tymed; } ;
typedef  TYPE_1__* LPFORMATETC ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPBRD_E_CANT_SET ; 
 int /*<<< orphan*/  DV_E_FORMATETC ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClipboardData (scalar_t__,int /*<<< orphan*/ *) ; 
 int TYMED_ENHMF ; 
 int TYMED_GDI ; 
 int TYMED_HGLOBAL ; 
 int TYMED_ISTORAGE ; 
 int TYMED_ISTREAM ; 
 int TYMED_MFPICT ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ embed_source_clipboard_format ; 
 int /*<<< orphan*/  free_metafilepict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_data_from_bitmap (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_data_from_enhmetafile (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_data_from_global (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_data_from_metafilepict (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_data_from_storage (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_data_from_stream (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  render_embed_source_hack (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HRESULT render_format(IDataObject *data, LPFORMATETC fmt)
{
    HANDLE clip_data = NULL;  /* HGLOBAL unless otherwise specified */
    HRESULT hr;

    /* Embed source hack */
    if(fmt->cfFormat == embed_source_clipboard_format)
    {
        return render_embed_source_hack(data, fmt);
    }

    if(fmt->tymed & TYMED_ISTORAGE)
    {
        hr = get_data_from_storage(data, fmt, &clip_data);
    }
    else if(fmt->tymed & TYMED_ISTREAM)
    {
        hr = get_data_from_stream(data, fmt, &clip_data);
    }
    else if(fmt->tymed & TYMED_HGLOBAL)
    {
        hr = get_data_from_global(data, fmt, &clip_data);
    }
    else if(fmt->tymed & TYMED_ENHMF)
    {
        hr = get_data_from_enhmetafile(data, fmt, &clip_data);
    }
    else if(fmt->tymed & TYMED_MFPICT)
    {
        /* Returns global handle to METAFILEPICT, containing a copied HMETAFILE */
        hr = get_data_from_metafilepict(data, fmt, &clip_data);
    }
    else if(fmt->tymed & TYMED_GDI)
    {
        /* Returns HBITMAP not HGLOBAL */
        hr = get_data_from_bitmap(data, fmt, (HBITMAP *)&clip_data);
    }
    else
    {
        FIXME("Unhandled tymed %x\n", fmt->tymed);
        hr = DV_E_FORMATETC;
    }

    if(SUCCEEDED(hr))
    {
        if ( !SetClipboardData(fmt->cfFormat, clip_data) )
        {
            WARN("() : Failed to set rendered clipboard data into clipboard!\n");
            if(fmt->tymed & TYMED_MFPICT)
                free_metafilepict(clip_data);
            else if(fmt->tymed & TYMED_GDI)
                DeleteObject(clip_data);
            else
                GlobalFree(clip_data);
            hr = CLIPBRD_E_CANT_SET;
        }
    }

    return hr;
}