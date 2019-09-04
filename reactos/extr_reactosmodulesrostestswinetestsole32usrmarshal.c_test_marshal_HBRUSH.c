#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wireHBRUSH ;
struct TYPE_9__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_3__ USER_MARSHAL_CB ;
typedef  int ULONG ;
struct TYPE_10__ {scalar_t__ lbHatch; int /*<<< orphan*/  lbColor; int /*<<< orphan*/  lbStyle; } ;
struct TYPE_7__ {scalar_t__ hInproc; int /*<<< orphan*/  hRemote; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  fContext; } ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  scalar_t__ LONG_PTR ;
typedef  TYPE_4__ LOGBRUSH ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  BS_SOLID ; 
 scalar_t__ CreateBrushIndirect (TYPE_4__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HBRUSH_UserFree (int /*<<< orphan*/ *,scalar_t__*) ; 
 unsigned char* HBRUSH_UserMarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 int HBRUSH_UserSize (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 unsigned char* HBRUSH_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDT_INPROC_CALL ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HBRUSH(void)
{
    MIDL_STUB_MESSAGE stub_msg;
    HBRUSH hBrush, hBrush2;
    USER_MARSHAL_CB umcb;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer, *buffer_end;
    LOGBRUSH logbrush;
    wireHBRUSH wirehbrush;
    ULONG size;

    logbrush.lbStyle = BS_SOLID;
    logbrush.lbColor = RGB(0, 0, 0);
    logbrush.lbHatch = 0;

    hBrush = CreateBrushIndirect(&logbrush);
    ok(hBrush != 0, "CreateBrushIndirect failed\n");

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    size = HBRUSH_UserSize(&umcb.Flags, 1, &hBrush);
    ok(size == 4 + sizeof(*wirehbrush), "Wrong size %d\n", size);

    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HBRUSH_UserMarshal(&umcb.Flags, buffer + 1, &hBrush);
    ok(buffer_end == buffer + 4 + sizeof(*wirehbrush), "got %p buffer %p\n", buffer_end, buffer);
    wirehbrush = (wireHBRUSH)(buffer + 4);
    ok(wirehbrush->fContext == WDT_INPROC_CALL, "Context should be WDT_INPROC_CALL instead of 0x%08x\n", wirehbrush->fContext);
    ok(wirehbrush->u.hInproc == (LONG_PTR)hBrush, "Marshaled value should be %p instead of %x\n", hBrush, wirehbrush->u.hRemote);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HBRUSH_UserUnmarshal(&umcb.Flags, buffer + 1, &hBrush2);
    ok(buffer_end == buffer + 4 + sizeof(*wirehbrush), "got %p buffer %p\n", buffer_end, buffer);
    ok(hBrush == hBrush2, "Didn't unmarshal properly\n");
    HeapFree(GetProcessHeap(), 0, buffer);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    HBRUSH_UserFree(&umcb.Flags, &hBrush2);
    DeleteObject(hBrush);
}