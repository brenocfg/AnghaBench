#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  changed; TYPE_1__* section; } ;
struct TYPE_6__ {struct TYPE_6__* value; struct TYPE_6__* next; } ;
struct TYPE_5__ {struct TYPE_5__* next; TYPE_2__* key; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PROFILESECTION ;
typedef  TYPE_2__ PROFILEKEY ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 TYPE_4__* CurProfile ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PROFILE_DeleteAllKeys( LPCWSTR section_name)
{
    PROFILESECTION **section= &CurProfile->section;
    while (*section)
    {
        if (!strcmpiW( (*section)->name, section_name ))
        {
            PROFILEKEY **key = &(*section)->key;
            while (*key)
            {
                PROFILEKEY *to_del = *key;
		*key = to_del->next;
                HeapFree( GetProcessHeap(), 0, to_del->value);
		HeapFree( GetProcessHeap(), 0, to_del );
		CurProfile->changed =TRUE;
            }
        }
        section = &(*section)->next;
    }
}