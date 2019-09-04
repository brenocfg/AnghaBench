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
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMemInputPin ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IMemInputPin ; 
 int /*<<< orphan*/  IMemInputPin_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_pin(IPin *pin)
{
    IMemInputPin *mpin = NULL;

    IPin_QueryInterface(pin, &IID_IMemInputPin, (void **)&mpin);

    ok(mpin == NULL, "IMemInputPin found!\n");
    if (mpin)
        IMemInputPin_Release(mpin);
    /* TODO */
}