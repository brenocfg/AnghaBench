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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  int /*<<< orphan*/ * HENHMETAFILE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ *) ; 
 int EMR_HEADER ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HENHMETAFILE_UserFree (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 unsigned char* HENHMETAFILE_UserMarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 int HENHMETAFILE_UserSize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 unsigned char* HENHMETAFILE_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_DIFFERENTMACHINE ; 
 int WDT_REMOTE_CALL ; 
 int /*<<< orphan*/ * create_emf () ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HENHMETAFILE(void)
{
    USER_MARSHAL_CB umcb;
    MIDL_STUB_MESSAGE stub_msg;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer, *buffer_end;
    ULONG size;
    HENHMETAFILE hemf;
    HENHMETAFILE hemf2 = NULL;
    unsigned char *wirehemf;

    hemf = create_emf();

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_DIFFERENTMACHINE);
    size = HENHMETAFILE_UserSize(&umcb.Flags, 1, &hemf);
    ok(size > 24, "size should be at least 24 bytes, not %d\n", size);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    buffer_end = HENHMETAFILE_UserMarshal(&umcb.Flags, buffer + 1, &hemf);
    ok(buffer_end == buffer + size, "got %p buffer %p\n", buffer_end, buffer);
    wirehemf = buffer + 4;
    ok(*(DWORD *)wirehemf == WDT_REMOTE_CALL, "wirestgm + 0x0 should be WDT_REMOTE_CALL instead of 0x%08x\n", *(DWORD *)wirehemf);
    wirehemf += sizeof(DWORD);
    ok(*(DWORD *)wirehemf == (DWORD)(DWORD_PTR)hemf, "wirestgm + 0x4 should be hemf instead of 0x%08x\n", *(DWORD *)wirehemf);
    wirehemf += sizeof(DWORD);
    ok(*(DWORD *)wirehemf == (size - 0x14), "wirestgm + 0x8 should be size - 0x14 instead of 0x%08x\n", *(DWORD *)wirehemf);
    wirehemf += sizeof(DWORD);
    ok(*(DWORD *)wirehemf == (size - 0x14), "wirestgm + 0xc should be size - 0x14 instead of 0x%08x\n", *(DWORD *)wirehemf);
    wirehemf += sizeof(DWORD);
    ok(*(DWORD *)wirehemf == EMR_HEADER, "wirestgm + 0x10 should be EMR_HEADER instead of %d\n", *(DWORD *)wirehemf);
    /* ... rest of data not tested - refer to tests for GetEnhMetaFileBits
     * at this point */

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    buffer_end = HENHMETAFILE_UserUnmarshal(&umcb.Flags, buffer + 1, &hemf2);
    ok(buffer_end == buffer + size, "got %p buffer %p\n", buffer_end, buffer);
    ok(hemf2 != NULL, "HENHMETAFILE didn't unmarshal\n");
    HeapFree(GetProcessHeap(), 0, buffer);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_DIFFERENTMACHINE);
    HENHMETAFILE_UserFree(&umcb.Flags, &hemf2);
    DeleteEnhMetaFile(hemf);

    /* test NULL emf */
    hemf = NULL;

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_DIFFERENTMACHINE);
    size = HENHMETAFILE_UserSize(&umcb.Flags, 1, &hemf);
    ok(size == 12, "size should be 12 bytes, not %d\n", size);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    buffer_end = HENHMETAFILE_UserMarshal(&umcb.Flags, buffer + 1, &hemf);
    ok(buffer_end == buffer + size, "got %p buffer %p\n", buffer_end, buffer);
    wirehemf = buffer + 4;
    ok(*(DWORD *)wirehemf == WDT_REMOTE_CALL, "wirestgm + 0x0 should be WDT_REMOTE_CALL instead of 0x%08x\n", *(DWORD *)wirehemf);
    wirehemf += sizeof(DWORD);
    ok(*(DWORD *)wirehemf == (DWORD)(DWORD_PTR)hemf, "wirestgm + 0x4 should be hemf instead of 0x%08x\n", *(DWORD *)wirehemf);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_DIFFERENTMACHINE);
    buffer_end = HENHMETAFILE_UserUnmarshal(&umcb.Flags, buffer + 1, &hemf2);
    ok(buffer_end == buffer + size, "got %p buffer %p\n", buffer_end, buffer);
    ok(hemf2 == NULL, "NULL HENHMETAFILE didn't unmarshal\n");
    HeapFree(GetProcessHeap(), 0, buffer);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_DIFFERENTMACHINE);
    HENHMETAFILE_UserFree(&umcb.Flags, &hemf2);
}