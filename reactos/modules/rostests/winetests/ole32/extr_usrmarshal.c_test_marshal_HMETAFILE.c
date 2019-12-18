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
typedef  int WORD ;
struct TYPE_3__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ USER_MARSHAL_CB ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  int /*<<< orphan*/ * HMETAFILE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HMETAFILE_UserFree (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HMETAFILE_UserMarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 int HMETAFILE_UserSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HMETAFILE_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_DIFFERENTMACHINE ; 
 int WDT_REMOTE_CALL ; 
 int /*<<< orphan*/ * create_mf () ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HMETAFILE(void)
{
    USER_MARSHAL_CB umcb;
    MIDL_STUB_MESSAGE stub_msg;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer;
    ULONG size;
    HMETAFILE hmf;
    HMETAFILE hmf2 = NULL;
    unsigned char *wirehmf;

    hmf = create_mf();

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_DIFFERENTMACHINE);
    size = HMETAFILE_UserSize(&umcb.Flags, 0, &hmf);
    ok(size > 20, "size should be at least 20 bytes, not %d\n", size);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    HMETAFILE_UserMarshal(&umcb.Flags, buffer, &hmf);
    wirehmf = buffer;
    ok(*(DWORD *)wirehmf == WDT_REMOTE_CALL, "wirestgm + 0x0 should be WDT_REMOTE_CALL instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    ok(*(DWORD *)wirehmf == (DWORD)(DWORD_PTR)hmf, "wirestgm + 0x4 should be hmf instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    ok(*(DWORD *)wirehmf == (size - 0x10), "wirestgm + 0x8 should be size - 0x10 instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    ok(*(DWORD *)wirehmf == (size - 0x10), "wirestgm + 0xc should be size - 0x10 instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    ok(*(WORD *)wirehmf == 1, "wirestgm + 0x10 should be 1 instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    /* ... rest of data not tested - refer to tests for GetMetaFileBits
     * at this point */

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    HMETAFILE_UserUnmarshal(&umcb.Flags, buffer, &hmf2);
    ok(hmf2 != NULL, "HMETAFILE didn't unmarshal\n");
    HeapFree(GetProcessHeap(), 0, buffer);
    HMETAFILE_UserFree(&umcb.Flags, &hmf2);
    DeleteMetaFile(hmf);

    /* test NULL emf */
    hmf = NULL;

    size = HMETAFILE_UserSize(&umcb.Flags, 0, &hmf);
    ok(size == 8, "size should be 8 bytes, not %d\n", size);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    HMETAFILE_UserMarshal(&umcb.Flags, buffer, &hmf);
    wirehmf = buffer;
    ok(*(DWORD *)wirehmf == WDT_REMOTE_CALL, "wirestgm + 0x0 should be WDT_REMOTE_CALL instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);
    ok(*(DWORD *)wirehmf == (DWORD)(DWORD_PTR)hmf, "wirestgm + 0x4 should be hmf instead of 0x%08x\n", *(DWORD *)wirehmf);
    wirehmf += sizeof(DWORD);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    HMETAFILE_UserUnmarshal(&umcb.Flags, buffer, &hmf2);
    ok(hmf2 == NULL, "NULL HMETAFILE didn't unmarshal\n");
    HeapFree(GetProcessHeap(), 0, buffer);
    HMETAFILE_UserFree(&umcb.Flags, &hmf2);
}