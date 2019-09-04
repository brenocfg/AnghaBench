#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  hMetaFilePict; int /*<<< orphan*/  hBitmap; } ;
struct TYPE_16__ {scalar_t__ tymed; TYPE_1__ u; } ;
struct TYPE_15__ {scalar_t__ cfFormat; scalar_t__ tymed; } ;
struct TYPE_18__ {TYPE_3__ stgmedium; TYPE_2__ fmtetc; void* dirty; } ;
struct TYPE_17__ {scalar_t__ cfFormat; scalar_t__ tymed; } ;
typedef  TYPE_3__ STGMEDIUM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ FORMATETC ;
typedef  TYPE_5__ DataCacheEntry ;
typedef  void* BOOL ;

/* Variables and functions */
 scalar_t__ CF_BITMAP ; 
 scalar_t__ CF_ENHMETAFILE ; 
 scalar_t__ CF_METAFILEPICT ; 
 int /*<<< orphan*/  DV_E_FORMATETC ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_3__*) ; 
 int /*<<< orphan*/  S_OK ; 
 void* TRUE ; 
 scalar_t__ TYMED_NULL ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  copy_stg_medium (scalar_t__,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  synthesize_dib (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  synthesize_emf (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static HRESULT DataCacheEntry_SetData(DataCacheEntry *cache_entry,
                                      const FORMATETC *formatetc,
                                      STGMEDIUM *stgmedium,
                                      BOOL fRelease)
{
    STGMEDIUM copy;
    HRESULT hr;

    if ((!cache_entry->fmtetc.cfFormat && !formatetc->cfFormat) ||
        (cache_entry->fmtetc.tymed == TYMED_NULL && formatetc->tymed == TYMED_NULL) ||
        stgmedium->tymed == TYMED_NULL)
    {
        WARN("invalid formatetc\n");
        return DV_E_FORMATETC;
    }

    cache_entry->dirty = TRUE;
    ReleaseStgMedium(&cache_entry->stgmedium);

    if (formatetc->cfFormat == CF_BITMAP)
    {
        hr = synthesize_dib( stgmedium->u.hBitmap, &copy );
        if (FAILED(hr)) return hr;
        if (fRelease) ReleaseStgMedium(stgmedium);
        stgmedium = &copy;
        fRelease = TRUE;
    }
    else if (formatetc->cfFormat == CF_METAFILEPICT && cache_entry->fmtetc.cfFormat == CF_ENHMETAFILE)
    {
        hr = synthesize_emf( stgmedium->u.hMetaFilePict, &copy );
        if (FAILED(hr)) return hr;
        if (fRelease) ReleaseStgMedium(stgmedium);
        stgmedium = &copy;
        fRelease = TRUE;
    }

    if (fRelease)
    {
        cache_entry->stgmedium = *stgmedium;
        return S_OK;
    }
    else
        return copy_stg_medium(cache_entry->fmtetc.cfFormat, &cache_entry->stgmedium, stgmedium);
}