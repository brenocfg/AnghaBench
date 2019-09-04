#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t numProviders; struct TYPE_5__* entireNetwork; TYPE_1__* table; } ;
struct TYPE_4__ {int /*<<< orphan*/  hLib; TYPE_2__* name; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FreeModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* providerTable ; 

void wnetFree(void)
{
    if (providerTable)
    {
        DWORD i;

        for (i = 0; i < providerTable->numProviders; i++)
        {
            HeapFree(GetProcessHeap(), 0, providerTable->table[i].name);
            FreeModule(providerTable->table[i].hLib);
        }
        HeapFree(GetProcessHeap(), 0, providerTable->entireNetwork);
        HeapFree(GetProcessHeap(), 0, providerTable);
        providerTable = NULL;
    }
}