#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * pFormatTypes; } ;
struct TYPE_10__ {int BufferLength; int BufferStart; int Buffer; TYPE_1__* RpcMsg; } ;
struct TYPE_9__ {int Buffer; } ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  TYPE_2__ MIDL_STUB_MESSAGE ;
typedef  TYPE_3__ MIDL_STUB_DESC ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LONG ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NdrClientInitializeNew (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdrSimpleTypeMarshall (TYPE_2__*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdrSimpleTypeUnmarshall (TYPE_2__*,unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ Object_StubDesc ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_ndr_simple_type(void)
{
    RPC_MESSAGE RpcMessage;
    MIDL_STUB_MESSAGE StubMsg;
    MIDL_STUB_DESC StubDesc;
    LONG l, l2 = 0;

    StubDesc = Object_StubDesc;
    StubDesc.pFormatTypes = NULL;

    NdrClientInitializeNew(
                           &RpcMessage,
                           &StubMsg,
                           &StubDesc,
                           0);

    StubMsg.BufferLength = 16;
    StubMsg.RpcMsg->Buffer = StubMsg.BufferStart = StubMsg.Buffer = HeapAlloc(GetProcessHeap(), 0, StubMsg.BufferLength);
    l = 0xcafebabe;
    NdrSimpleTypeMarshall(&StubMsg, (unsigned char*)&l, FC_LONG);
    ok(StubMsg.Buffer == StubMsg.BufferStart + 4, "%p %p\n", StubMsg.Buffer, StubMsg.BufferStart);
    ok(*(LONG*)StubMsg.BufferStart == l, "%d\n", *(LONG*)StubMsg.BufferStart);

    StubMsg.Buffer = StubMsg.BufferStart + 1;
    NdrSimpleTypeMarshall(&StubMsg, (unsigned char*)&l, FC_LONG);
    ok(StubMsg.Buffer == StubMsg.BufferStart + 8, "%p %p\n", StubMsg.Buffer, StubMsg.BufferStart);
    ok(*(LONG*)(StubMsg.BufferStart + 4) == l, "%d\n", *(LONG*)StubMsg.BufferStart);

    StubMsg.Buffer = StubMsg.BufferStart + 1;
    NdrSimpleTypeUnmarshall(&StubMsg, (unsigned char*)&l2, FC_LONG);
    ok(StubMsg.Buffer == StubMsg.BufferStart + 8, "%p %p\n", StubMsg.Buffer, StubMsg.BufferStart);
    ok(l2 == l, "%d\n", l2);

    HeapFree(GetProcessHeap(), 0, StubMsg.BufferStart);
}