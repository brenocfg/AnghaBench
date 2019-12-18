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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IPSFactoryBuffer_CreateStub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static IRpcStubBuffer *create_stub(IPSFactoryBuffer *ppsf, REFIID iid, IUnknown *obj, HRESULT expected_result)
{
    IRpcStubBuffer *pstub = NULL;
    HRESULT r;

    r = IPSFactoryBuffer_CreateStub(ppsf, iid, obj, &pstub);
    ok(r == expected_result, "CreateStub returned %08x expected %08x\n", r, expected_result);
    return pstub;
}