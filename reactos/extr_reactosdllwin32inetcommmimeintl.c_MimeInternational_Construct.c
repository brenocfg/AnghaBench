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
struct TYPE_11__ {TYPE_1__* DebugInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_2__ IMimeInternational_iface; int /*<<< orphan*/ * default_charset; scalar_t__ next_charset_handle; int /*<<< orphan*/  charsets; TYPE_5__ cs; scalar_t__ refs; } ;
struct TYPE_8__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ IMimeInternational ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMimeInternational_AddRef (TYPE_2__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* global_internat ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mime_internat_vtbl ; 

HRESULT MimeInternational_Construct(IMimeInternational **internat)
{
    global_internat = HeapAlloc(GetProcessHeap(), 0, sizeof(*global_internat));
    global_internat->IMimeInternational_iface.lpVtbl = &mime_internat_vtbl;
    global_internat->refs = 0;
    InitializeCriticalSection(&global_internat->cs);
    global_internat->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": global_internat.cs");

    list_init(&global_internat->charsets);
    global_internat->next_charset_handle = 0;
    global_internat->default_charset = NULL;

    *internat = &global_internat->IMimeInternational_iface;

    IMimeInternational_AddRef(*internat);
    return S_OK;
}