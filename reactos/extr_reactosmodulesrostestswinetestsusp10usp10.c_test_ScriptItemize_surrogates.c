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
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_4__ {int eScript; } ;
struct TYPE_5__ {TYPE_1__ a; } ;
typedef  TYPE_2__ SCRIPT_ITEM ;
typedef  int HRESULT ;

/* Variables and functions */
 int SCRIPT_UNDEFINED ; 
 int S_OK ; 
 int ScriptItemize (int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  make_surrogate (int,int*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_ScriptItemize_surrogates(void)
{
    HRESULT hr;
    WCHAR surrogate[2];
    WORD Script_Surrogates;
    SCRIPT_ITEM items[2];
    int num;

    /* Find Script_Surrogates */
    surrogate[0] = 0xd800;
    hr = ScriptItemize( surrogate, 1, 2, NULL, NULL, items, &num );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( num == 1, "got %d\n", num );
    ok( items[0].a.eScript != SCRIPT_UNDEFINED, "got script %x\n", items[0].a.eScript );
    Script_Surrogates = items[0].a.eScript;

    /* Show that an invalid character has script Script_Surrogates */
    make_surrogate( 0x01ffff, surrogate );
    hr = ScriptItemize( surrogate, 2, 2, NULL, NULL, items, &num );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( num == 1, "got %d\n", num );
    ok( items[0].a.eScript == Script_Surrogates, "got script %x\n", items[0].a.eScript );
}