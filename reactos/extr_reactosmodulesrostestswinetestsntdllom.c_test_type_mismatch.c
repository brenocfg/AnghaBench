#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attr ;
struct TYPE_3__ {int Length; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; scalar_t__ Attributes; int /*<<< orphan*/ * ObjectName; scalar_t__ RootDirectory; } ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ STATUS_OBJECT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_type_mismatch(void)
{
    HANDLE h;
    NTSTATUS res;
    OBJECT_ATTRIBUTES attr;

    attr.Length                   = sizeof(attr);
    attr.RootDirectory            = 0;
    attr.ObjectName               = NULL;
    attr.Attributes               = 0;
    attr.SecurityDescriptor       = NULL;
    attr.SecurityQualityOfService = NULL;

    res = pNtCreateEvent( &h, 0, &attr, 0, 0 );
    ok(!res, "can't create event: %x\n", res);

    res = pNtReleaseSemaphore( h, 30, NULL );
    ok(res == STATUS_OBJECT_TYPE_MISMATCH, "expected 0xc0000024, got %x\n", res);

    pNtClose( h );
}