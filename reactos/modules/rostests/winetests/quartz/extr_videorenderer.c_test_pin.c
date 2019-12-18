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
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IID_IMemInputPin ; 
 scalar_t__ IMemInputPin_NotifyAllocator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IMemInputPin_ReceiveCanBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMemInputPin_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_pin(IPin *pin)
{
    IMemInputPin *mpin = NULL;

    IPin_QueryInterface(pin, &IID_IMemInputPin, (void **)&mpin);

    ok(mpin != NULL, "No IMemInputPin found!\n");
    if (mpin)
    {
        ok(IMemInputPin_ReceiveCanBlock(mpin) == S_OK, "Receive can't block for pin!\n");
        ok(IMemInputPin_NotifyAllocator(mpin, NULL, 0) == E_POINTER, "NotifyAllocator likes a NULL pointer argument\n");
        IMemInputPin_Release(mpin);
    }
    /* TODO */
}