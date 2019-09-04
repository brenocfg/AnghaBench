#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_17__ {scalar_t__ number_of_cp; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {size_t total_scripts; int ref; TYPE_6__ IMultiLanguage_iface; scalar_t__ total_cp; TYPE_4__ IMLangLineBreakConsole_iface; TYPE_3__ IMLangFontLink2_iface; TYPE_2__ IMultiLanguage3_iface; TYPE_1__ IMLangFontLink_iface; } ;
typedef  TYPE_5__ MLang_impl ;
typedef  TYPE_6__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_7__*) ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMLangFontLink2_vtbl ; 
 int /*<<< orphan*/  IMLangFontLink_vtbl ; 
 int /*<<< orphan*/  IMLangLineBreakConsole_vtbl ; 
 int /*<<< orphan*/  IMultiLanguage3_vtbl ; 
 int /*<<< orphan*/  IMultiLanguage_vtbl ; 
 int /*<<< orphan*/  LockModule () ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_7__* mlang_data ; 

__attribute__((used)) static HRESULT MultiLanguage_create(IUnknown *pUnkOuter, LPVOID *ppObj)
{
    MLang_impl *mlang;
    UINT i;

    TRACE("Creating MultiLanguage object\n");

    if( pUnkOuter )
        return CLASS_E_NOAGGREGATION;

    mlang = HeapAlloc( GetProcessHeap(), 0, sizeof (MLang_impl) );
    mlang->IMLangFontLink_iface.lpVtbl = &IMLangFontLink_vtbl;
    mlang->IMultiLanguage_iface.lpVtbl = &IMultiLanguage_vtbl;
    mlang->IMultiLanguage3_iface.lpVtbl = &IMultiLanguage3_vtbl;
    mlang->IMLangFontLink2_iface.lpVtbl = &IMLangFontLink2_vtbl;
    mlang->IMLangLineBreakConsole_iface.lpVtbl = &IMLangLineBreakConsole_vtbl;

    mlang->total_cp = 0;
    for (i = 0; i < ARRAY_SIZE(mlang_data); i++)
        mlang->total_cp += mlang_data[i].number_of_cp;

    /* do not enumerate unicode flavours */
    mlang->total_scripts = ARRAY_SIZE(mlang_data) - 1;

    mlang->ref = 1;
    *ppObj = &mlang->IMultiLanguage_iface;
    TRACE("returning %p\n", mlang);

    LockModule();

    return S_OK;
}