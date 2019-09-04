#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct regsvr_filter {int /*<<< orphan*/  category; int /*<<< orphan*/  name; scalar_t__ clsid; TYPE_4__* pins; int /*<<< orphan*/  merit; } ;
struct TYPE_11__ {int cPins2; TYPE_5__* rgPins2; } ;
struct TYPE_12__ {TYPE_1__ s2; } ;
struct TYPE_16__ {int dwVersion; TYPE_2__ u; int /*<<< orphan*/  dwMerit; } ;
struct TYPE_15__ {int dwFlags; int nMediaTypes; struct TYPE_15__* lpMediaType; int /*<<< orphan*/ * clsPinCategory; int /*<<< orphan*/ * lpMedium; scalar_t__ nMediums; scalar_t__ cInstances; int /*<<< orphan*/ * clsMinorType; int /*<<< orphan*/ * clsMajorType; } ;
struct TYPE_14__ {int flags; TYPE_3__* mediatypes; } ;
struct TYPE_13__ {int /*<<< orphan*/  fourcc; scalar_t__ majortype; scalar_t__ subtype; } ;
typedef  TYPE_5__ REGPINTYPES ;
typedef  TYPE_5__ REGFILTERPINS2 ;
typedef  TYPE_7__ REGFILTER2 ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IFilterMapper2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 TYPE_5__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_5__*) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFilterMapper2_RegisterFilter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  IFilterMapper2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFilterMapper2 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static HRESULT register_filters(struct regsvr_filter const *list)
{
    HRESULT hr;
    IFilterMapper2* pFM2 = NULL;

    CoInitialize(NULL);
    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER, &IID_IFilterMapper2, (LPVOID*)&pFM2);

    if (SUCCEEDED(hr)) {
	for (; SUCCEEDED(hr) && list->clsid; ++list) {
	    REGFILTER2 rf2;
	    REGFILTERPINS2* prfp2;
	    int i;

	    for (i = 0; list->pins[i].flags != 0xFFFFFFFF; i++) ;
	    rf2.dwVersion = 2;
	    rf2.dwMerit = list->merit;
	    rf2.u.s2.cPins2 = i;
	    rf2.u.s2.rgPins2 = prfp2 = CoTaskMemAlloc(i*sizeof(REGFILTERPINS2));
	    if (!prfp2) {
		hr = E_OUTOFMEMORY;
		break;
	    }
	    for (i = 0; list->pins[i].flags != 0xFFFFFFFF; i++) {
		REGPINTYPES* lpMediatype;
		CLSID* lpClsid;
		int j, nbmt;
                
		for (nbmt = 0; list->pins[i].mediatypes[nbmt].majortype; nbmt++) ;
		/* Allocate a single buffer for regpintypes struct and clsids */
		lpMediatype = CoTaskMemAlloc(nbmt*(sizeof(REGPINTYPES) + 2*sizeof(CLSID)));
		if (!lpMediatype) {
		    hr = E_OUTOFMEMORY;
		    break;
		}
		lpClsid = (CLSID*) (lpMediatype + nbmt);
		for (j = 0; j < nbmt; j++) {
		    (lpMediatype + j)->clsMajorType = lpClsid + j*2;
		    memcpy(lpClsid + j*2, list->pins[i].mediatypes[j].majortype, sizeof(CLSID));
		    (lpMediatype + j)->clsMinorType = lpClsid + j*2 + 1;
		    if (list->pins[i].mediatypes[j].subtype)
			memcpy(lpClsid + j*2 + 1, list->pins[i].mediatypes[j].subtype, sizeof(CLSID));
		    else {
                        /* Subtypes are often a combination of major type + fourcc/tag */
			memcpy(lpClsid + j*2 + 1, list->pins[i].mediatypes[j].majortype, sizeof(CLSID));
			*(DWORD*)(lpClsid + j*2 + 1) = list->pins[i].mediatypes[j].fourcc;
		    }
		}
		prfp2[i].dwFlags = list->pins[i].flags;
		prfp2[i].cInstances = 0;
		prfp2[i].nMediaTypes = j;
		prfp2[i].lpMediaType = lpMediatype;
		prfp2[i].nMediums = 0;
		prfp2[i].lpMedium = NULL;
		prfp2[i].clsPinCategory = NULL;
	    }

	    if (FAILED(hr)) {
		ERR("failed to register with hresult 0x%x\n", hr);
		CoTaskMemFree(prfp2);
		break;
	    }

	    hr = IFilterMapper2_RegisterFilter(pFM2, list->clsid, list->name, NULL, list->category, NULL, &rf2);

	    while (i) {
		CoTaskMemFree((REGPINTYPES*)prfp2[i-1].lpMediaType);
		i--;
	    }
	    CoTaskMemFree(prfp2);
	}
    }

    if (pFM2)
	IFilterMapper2_Release(pFM2);

    CoUninitialize();

    return hr;
}