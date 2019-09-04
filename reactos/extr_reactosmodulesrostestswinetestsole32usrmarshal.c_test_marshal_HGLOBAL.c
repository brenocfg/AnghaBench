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
struct TYPE_3__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ USER_MARSHAL_CB ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 unsigned char* GlobalLock (int /*<<< orphan*/ *) ; 
 int GlobalSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HGLOBAL_UserFree (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HGLOBAL_UserMarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 int HGLOBAL_UserSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HGLOBAL_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int WDT_REMOTE_CALL ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HGLOBAL(void)
{
    USER_MARSHAL_CB umcb;
    MIDL_STUB_MESSAGE stub_msg;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer;
    ULONG size, block_size;
    HGLOBAL hglobal;
    HGLOBAL hglobal2;
    unsigned char *wirehglobal;
    int i;

    hglobal = NULL;
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    size = HGLOBAL_UserSize(&umcb.Flags, 0, &hglobal);
    /* native is poorly programmed and allocates 4/8 bytes more than it needs to
     * here - Wine doesn't have to emulate that */
    ok((size == 8) || broken(size == 12) || broken(size == 16), "Size should be 8, instead of %d\n", size);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    HGLOBAL_UserMarshal(&umcb.Flags, buffer, &hglobal);
    wirehglobal = buffer;
    ok(*(ULONG *)wirehglobal == WDT_REMOTE_CALL, "Context should be WDT_REMOTE_CALL instead of 0x%08x\n", *(ULONG *)wirehglobal);
    wirehglobal += sizeof(ULONG);
    ok(*(ULONG *)wirehglobal == 0, "buffer+4 should be HGLOBAL\n");
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    hglobal2 = NULL;
    HGLOBAL_UserUnmarshal(&umcb.Flags, buffer, &hglobal2);
    ok(hglobal2 == hglobal, "Didn't unmarshal properly\n");
    HeapFree(GetProcessHeap(), 0, buffer);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    HGLOBAL_UserFree(&umcb.Flags, &hglobal2);


    for(block_size = 0; block_size <= 17; block_size++)
    {
        ULONG actual_size, expected_size;

        hglobal = GlobalAlloc(0, block_size);
        buffer = GlobalLock(hglobal);
        for (i = 0; i < block_size; i++)
            buffer[i] = i;
        GlobalUnlock(hglobal);
        actual_size = GlobalSize(hglobal);
        expected_size = actual_size + 5 * sizeof(DWORD);
        init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
        size = HGLOBAL_UserSize(&umcb.Flags, 0, &hglobal);
        /* native is poorly programmed and allocates 4/8 bytes more than it needs to
         * here - Wine doesn't have to emulate that */
        ok(size == expected_size ||
           broken(size == expected_size + 4) ||
           broken(size == expected_size + 8),
           "%d: got size %d\n", block_size, size);
        buffer = HeapAlloc(GetProcessHeap(), 0, size);
        init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
        HGLOBAL_UserMarshal(&umcb.Flags, buffer, &hglobal);
        wirehglobal = buffer;
        ok(*(ULONG *)wirehglobal == WDT_REMOTE_CALL, "Context should be WDT_REMOTE_CALL instead of 0x%08x\n", *(ULONG *)wirehglobal);
        wirehglobal += sizeof(ULONG);
        ok(*(ULONG *)wirehglobal == (ULONG)(ULONG_PTR)hglobal, "buffer+0x4 should be HGLOBAL\n");
        wirehglobal += sizeof(ULONG);
        ok(*(ULONG *)wirehglobal == actual_size, "%d: buffer+0x8 %08x\n", block_size, *(ULONG *)wirehglobal);
        wirehglobal += sizeof(ULONG);
        ok(*(ULONG *)wirehglobal == (ULONG)(ULONG_PTR)hglobal, "buffer+0xc should be HGLOBAL\n");
        wirehglobal += sizeof(ULONG);
        ok(*(ULONG *)wirehglobal == actual_size, "%d: buffer+0x10 %08x\n", block_size, *(ULONG *)wirehglobal);
        wirehglobal += sizeof(ULONG);
        for (i = 0; i < block_size; i++)
            ok(wirehglobal[i] == i, "buffer+0x%x should be %d\n", 0x10 + i, i);

        init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
        hglobal2 = NULL;
        HGLOBAL_UserUnmarshal(&umcb.Flags, buffer, &hglobal2);
        ok(hglobal2 != NULL, "Didn't unmarshal properly\n");
        HeapFree(GetProcessHeap(), 0, buffer);
        init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
        HGLOBAL_UserFree(&umcb.Flags, &hglobal2);
        GlobalFree(hglobal);
    }
}