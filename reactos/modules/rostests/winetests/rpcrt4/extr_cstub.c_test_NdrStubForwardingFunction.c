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
typedef  int /*<<< orphan*/  This ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  IRpcStubBufferVtbl ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  IRpcChannelBuffer ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  NdrStubForwardingFunction (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int base_buffer_invoke_called ; 
 int /*<<< orphan*/  base_buffer_vtbl ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_NdrStubForwardingFunction(void)
{
    void *This[5];
    void *real_this;
    IRpcChannelBuffer *channel = (IRpcChannelBuffer*)0xdeadbeef;
    RPC_MESSAGE *msg = (RPC_MESSAGE*)0xcafebabe;
    DWORD *phase = (DWORD*)0x12345678;
    IRpcStubBufferVtbl *base_buffer_vtbl_ptr = &base_buffer_vtbl;
    IRpcStubBuffer *base_stub_buffer = (IRpcStubBuffer*)&base_buffer_vtbl_ptr;

    memset(This, 0xcc, sizeof(This));
    This[0] = base_stub_buffer;
    real_this = &This[1];

    NdrStubForwardingFunction( real_this, channel, msg, phase );
    ok(base_buffer_invoke_called == 1, "base_buffer_invoke called %d times\n", base_buffer_invoke_called);

}