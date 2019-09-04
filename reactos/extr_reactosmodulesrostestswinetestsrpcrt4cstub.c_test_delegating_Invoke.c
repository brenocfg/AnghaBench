#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int iMethod; scalar_t__ Buffer; int /*<<< orphan*/  dataRepresentation; } ;
typedef  TYPE_1__ RPCOLEMESSAGE ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITypeLibVtbl ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  IRpcChannelBufferVtbl ;
typedef  int /*<<< orphan*/  IRpcChannelBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IID_if2 ; 
 scalar_t__ IRpcStubBuffer_Invoke (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRpcStubBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NDR_LOCAL_DATA_REPRESENTATION ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_stub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  delegating_invoke_test_obj_vtbl ; 
 int /*<<< orphan*/  delegating_invoke_test_rpc_chan_vtbl ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_delegating_Invoke(IPSFactoryBuffer *ppsf)
{
    ITypeLibVtbl *obj_vtbl = &delegating_invoke_test_obj_vtbl;
    IUnknown *obj = (IUnknown*)&obj_vtbl;
    IRpcStubBuffer *pstub = create_stub(ppsf, &IID_if2, obj, S_OK);
    IRpcChannelBufferVtbl *pchan_vtbl = &delegating_invoke_test_rpc_chan_vtbl;
    IRpcChannelBuffer *pchan = (IRpcChannelBuffer *)&pchan_vtbl;
    HRESULT r = E_FAIL;
    RPCOLEMESSAGE msg;

    memset(&msg, 0, sizeof(msg));
    msg.dataRepresentation = NDR_LOCAL_DATA_REPRESENTATION;
    msg.iMethod = 3;
    r = IRpcStubBuffer_Invoke(pstub, &msg, pchan);
    ok(r == S_OK, "ret %08x\n", r);
    if(r == S_OK)
    {
        ok(*(DWORD*)msg.Buffer == 0xabcdef, "buf[0] %08x\n", *(DWORD*)msg.Buffer);
        ok(*((DWORD*)msg.Buffer + 1) == S_OK, "buf[1] %08x\n", *((DWORD*)msg.Buffer + 1));
    }
    /* free the buffer allocated by delegating_invoke_chan_get_buffer */
    HeapFree(GetProcessHeap(), 0, msg.Buffer);
    IRpcStubBuffer_Release(pstub);
}