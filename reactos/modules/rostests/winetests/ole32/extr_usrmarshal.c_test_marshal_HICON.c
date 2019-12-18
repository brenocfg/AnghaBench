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
typedef  TYPE_2__* wireHICON ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_3__ USER_MARSHAL_CB ;
typedef  int ULONG ;
struct TYPE_5__ {scalar_t__ hInproc; int /*<<< orphan*/  hRemote; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  fContext; } ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;
typedef  scalar_t__ LONG_PTR ;
typedef  scalar_t__ HICON ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CreateIcon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HICON_UserFree (int /*<<< orphan*/ *,scalar_t__*) ; 
 unsigned char* HICON_UserMarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 int HICON_UserSize (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 unsigned char* HICON_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,scalar_t__*) ; 
 unsigned char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  WDT_INPROC_CALL ; 
 int /*<<< orphan*/  init_user_marshal_cb (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_marshal_HICON(void)
{
    static const BYTE bmp_bits[1024];
    MIDL_STUB_MESSAGE stub_msg;
    HICON hIcon, hIcon2;
    USER_MARSHAL_CB umcb;
    RPC_MESSAGE rpc_msg;
    unsigned char *buffer, *buffer_end;
    wireHICON wirehicon;
    ULONG size;

    hIcon = CreateIcon(0, 16, 16, 1, 1, bmp_bits, bmp_bits);
    ok(hIcon != 0, "CreateIcon failed\n");

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    size = HICON_UserSize(&umcb.Flags, 1, &hIcon);
    ok(size == 4 + sizeof(*wirehicon), "Wrong size %d\n", size);

    buffer = HeapAlloc(GetProcessHeap(), 0, size);
    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HICON_UserMarshal(&umcb.Flags, buffer + 1, &hIcon);
    ok(buffer_end == buffer + 4 + sizeof(*wirehicon), "got %p buffer %p\n", buffer_end, buffer);
    wirehicon = (wireHICON)(buffer + 4);
    ok(wirehicon->fContext == WDT_INPROC_CALL, "Context should be WDT_INPROC_CALL instead of 0x%08x\n", wirehicon->fContext);
    ok(wirehicon->u.hInproc == (LONG_PTR)hIcon, "Marshaled value should be %p instead of %x\n", hIcon, wirehicon->u.hRemote);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, buffer, size, MSHCTX_LOCAL);
    buffer_end = HICON_UserUnmarshal(&umcb.Flags, buffer + 1, &hIcon2);
    ok(buffer_end == buffer + 4 + sizeof(*wirehicon), "got %p buffer %p\n", buffer_end, buffer);
    ok(hIcon == hIcon2, "Didn't unmarshal properly\n");
    HeapFree(GetProcessHeap(), 0, buffer);

    init_user_marshal_cb(&umcb, &stub_msg, &rpc_msg, NULL, 0, MSHCTX_LOCAL);
    HICON_UserFree(&umcb.Flags, &hIcon2);
    DestroyIcon(hIcon);
}