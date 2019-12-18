#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IActiveScript_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ IActiveScript_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void close_script(IActiveScript *script)
{
    ULONG ref;
    HRESULT hres;

    hres = IActiveScript_Close(script);
    ok(hres == S_OK, "Close failed: %08x\n", hres);

    ref = IActiveScript_Release(script);
    ok(!ref, "ref=%u\n", ref);
}