#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {scalar_t__ dwSignature; } ;
struct TYPE_4__ {int /*<<< orphan*/  szwDarwinID; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IShellLinkW ;
typedef  int /*<<< orphan*/  IShellLinkDataList ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ EXP_DARWIN_LINK ;
typedef  int DWORD ;
typedef  TYPE_2__ DATABLOCK_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EXP_DARWIN_ID_SIG ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 scalar_t__ IShellLinkDataList_CopyDataBlock (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ IShellLinkDataList_GetFlags (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IShellLinkDataList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellLinkW_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellLinkW_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellLinkW_SetPath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int SLDF_HAS_DARWINID ; 
 int SLDF_HAS_LOGO3ID ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  _IID_IShellLinkDataList ; 
 scalar_t__ broken (int) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetLongPathNameA ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_datalink(void)
{
    static const WCHAR lnk[] = {
      ':',':','{','9','d','b','1','1','8','6','e','-','4','0','d','f','-','1',
      '1','d','1','-','a','a','8','c','-','0','0','c','0','4','f','b','6','7',
      '8','6','3','}',':','2','6',',','!','!','g','x','s','f','(','N','g',']',
      'q','F','`','H','{','L','s','A','C','C','E','S','S','F','i','l','e','s',
      '>','p','l','T',']','j','I','{','j','f','(','=','1','&','L','[','-','8',
      '1','-',']',':',':',0 };
    static const WCHAR comp[] = {
      '2','6',',','!','!','g','x','s','f','(','N','g',']','q','F','`','H','{',
      'L','s','A','C','C','E','S','S','F','i','l','e','s','>','p','l','T',']',
      'j','I','{','j','f','(','=','1','&','L','[','-','8','1','-',']',0 };
    IShellLinkDataList *dl = NULL;
    IShellLinkW *sl = NULL;
    HRESULT r;
    DWORD flags = 0;
    EXP_DARWIN_LINK *dar;

    r = CoCreateInstance( &CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            &IID_IShellLinkW, (LPVOID*)&sl );
    ok( r == S_OK ||
        broken(r == E_NOINTERFACE), /* Win9x */
        "CoCreateInstance failed (0x%08x)\n", r);
    if (!sl)
    {
        win_skip("no shelllink\n");
        return;
    }

    r = IShellLinkW_QueryInterface( sl, &_IID_IShellLinkDataList, (LPVOID*) &dl );
    ok( r == S_OK ||
        broken(r == E_NOINTERFACE), /* NT4 */
        "IShellLinkW_QueryInterface failed (0x%08x)\n", r);

    if (!dl)
    {
        win_skip("no datalink interface\n");
        IShellLinkW_Release( sl );
        return;
    }

    flags = 0;
    r = IShellLinkDataList_GetFlags( dl, &flags );
    ok( r == S_OK, "GetFlags failed\n");
    ok( flags == 0, "GetFlags returned wrong flags\n");

    dar = (void*)-1;
    r = IShellLinkDataList_CopyDataBlock( dl, EXP_DARWIN_ID_SIG, (LPVOID*) &dar );
    ok( r == E_FAIL, "CopyDataBlock failed\n");
    ok( dar == NULL, "should be null\n");

    if (!pGetLongPathNameA /* NT4 */)
        skip("SetPath with NULL parameter crashes on NT4\n");
    else
    {
        r = IShellLinkW_SetPath(sl, NULL);
        ok(r == E_INVALIDARG, "SetPath returned wrong error (0x%08x)\n", r);
    }

    r = IShellLinkW_SetPath(sl, lnk);
    ok(r == S_OK, "SetPath failed\n");

if (0)
{
    /* the following crashes */
    IShellLinkDataList_GetFlags( dl, NULL );
}

    flags = 0;
    r = IShellLinkDataList_GetFlags( dl, &flags );
    ok( r == S_OK, "GetFlags failed\n");
    /* SLDF_HAS_LOGO3ID is no longer supported on Vista+, filter it out */
    ok( (flags & (~ SLDF_HAS_LOGO3ID)) == SLDF_HAS_DARWINID,
        "GetFlags returned wrong flags\n");

    dar = NULL;
    r = IShellLinkDataList_CopyDataBlock( dl, EXP_DARWIN_ID_SIG, (LPVOID*) &dar );
    ok( r == S_OK, "CopyDataBlock failed\n");

    ok( dar && ((DATABLOCK_HEADER*)dar)->dwSignature == EXP_DARWIN_ID_SIG, "signature wrong\n");
    ok( dar && 0==lstrcmpW(dar->szwDarwinID, comp ), "signature wrong\n");

    LocalFree( dar );

    IShellLinkDataList_Release( dl );
    IShellLinkW_Release( sl );
}