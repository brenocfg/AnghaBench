#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_10__ {int /*<<< orphan*/  proportional_font; int /*<<< orphan*/  fixed_font; int /*<<< orphan*/  description; int /*<<< orphan*/  family_codepage; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; int total; TYPE_2__ IEnumScript_iface; TYPE_1__* script_info; scalar_t__ pos; } ;
struct TYPE_7__ {size_t ScriptId; int /*<<< orphan*/  wszProportionalFont; int /*<<< orphan*/  wszFixedWidthFont; int /*<<< orphan*/  wszDescription; int /*<<< orphan*/  uiCodePage; } ;
typedef  int /*<<< orphan*/  SCRIPTINFO ;
typedef  int /*<<< orphan*/  MLang_impl ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  TYPE_2__ IEnumScript ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ EnumScript_impl ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEnumScript_vtbl ; 
 int /*<<< orphan*/  MAX_MIMEFACE_NAME ; 
 int /*<<< orphan*/  MAX_SCRIPT_NAME ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCRIPTCONTF_SCRIPT_HIDE ; 
 int SCRIPTCONTF_SCRIPT_SYSTEM ; 
 int SCRIPTCONTF_SCRIPT_USER ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int,...) ; 
 TYPE_4__* mlang_data ; 

__attribute__((used)) static HRESULT EnumScript_create( MLang_impl* mlang, DWORD dwFlags,
                     LANGID LangId, IEnumScript** ppEnumScript )
{
    EnumScript_impl *es;
    UINT i;

    TRACE("%p, %08x, %04x, %p\n", mlang, dwFlags, LangId, ppEnumScript);

    if (!dwFlags) /* enumerate all available scripts */
        dwFlags = SCRIPTCONTF_SCRIPT_USER | SCRIPTCONTF_SCRIPT_HIDE | SCRIPTCONTF_SCRIPT_SYSTEM;

    es = HeapAlloc( GetProcessHeap(), 0, sizeof (EnumScript_impl) );
    es->IEnumScript_iface.lpVtbl = &IEnumScript_vtbl;
    es->ref = 1;
    es->pos = 0;
    /* do not enumerate unicode flavours */
    es->total = ARRAY_SIZE(mlang_data) - 1;
    es->script_info = HeapAlloc(GetProcessHeap(), 0, sizeof(SCRIPTINFO) * es->total);

    for (i = 0; i < es->total; i++)
    {
        es->script_info[i].ScriptId = i;
        es->script_info[i].uiCodePage = mlang_data[i].family_codepage;
        MultiByteToWideChar(CP_ACP, 0, mlang_data[i].description, -1,
            es->script_info[i].wszDescription, MAX_SCRIPT_NAME);
        MultiByteToWideChar(CP_ACP, 0, mlang_data[i].fixed_font, -1,
            es->script_info[i].wszFixedWidthFont, MAX_MIMEFACE_NAME);
        MultiByteToWideChar(CP_ACP, 0, mlang_data[i].proportional_font, -1,
            es->script_info[i].wszProportionalFont, MAX_MIMEFACE_NAME);
    }

    TRACE("enumerated %d scripts with flags %08x\n", es->total, dwFlags);

    *ppEnumScript = &es->IEnumScript_iface;

    return S_OK;
}