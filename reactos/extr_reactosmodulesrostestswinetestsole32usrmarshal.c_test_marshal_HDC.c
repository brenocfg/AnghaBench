#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wireHDC ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_3__ USER_MARSHAL_CB ;
typedef  int ULONG ;
struct TYPE_5__ {scalar_t__ hInproc; int /*<<< orphan*/  hRemote; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  fContext; } ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  scalar_t__ LONG_PTR ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HDC_UserFree (int /*<<< orphan*/ *,scalar_t__*) ; 
 unsigned char* HDC_UserMarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 int HDC_UserSize (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 unsigned char* HDC_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WDT_INPROC_CALL ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HDC(void)
{
    MIDL_STUB_MESSAGE stub_msg;
    HDC hdc = GetDC(0), hdc2;
    USER_MARSHAL_CB umcb;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer, *buffer_end;
    wireHDC wirehdc;
    ULONG size;

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    size = HDC_UserSize(&umcb.Flags, 1, &hdc);
    ok(size == 4 + sizeof(*wirehdc), "Wrong size %d\n", size);

    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HDC_UserMarshal(&umcb.Flags, buffer + 1, &hdc);
    ok(buffer_end == buffer + 4 + sizeof(*wirehdc), "got %p buffer %p\n", buffer_end, buffer);
    wirehdc = (wireHDC)(buffer + 4);
    ok(wirehdc->fContext == WDT_INPROC_CALL, "Context should be WDT_INPROC_CALL instead of 0x%08x\n", wirehdc->fContext);
    ok(wirehdc->u.hInproc == (LONG_PTR)hdc, "Marshaled value should be %p instead of %x\n", hdc, wirehdc->u.hRemote);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HDC_UserUnmarshal(&umcb.Flags, buffer + 1, &hdc2);
    ok(buffer_end == buffer + 4 + sizeof(*wirehdc), "got %p buffer %p\n", buffer_end, buffer);
    ok(hdc == hdc2, "Didn't unmarshal properly\n");
    HeapFree(GetProcessHeap(), 0, buffer);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    HDC_UserFree(&umcb.Flags, &hdc2);
    ReleaseDC(0, hdc);
}