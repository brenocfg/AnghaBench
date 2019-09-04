#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int code; } ;
struct TYPE_17__ {int /*<<< orphan*/ * pszText; int /*<<< orphan*/  dwMask; } ;
struct TYPE_16__ {int /*<<< orphan*/ * pszText; } ;
struct TYPE_15__ {int /*<<< orphan*/  idNew; int /*<<< orphan*/  idOld; } ;
struct TYPE_10__ {int iBitmap; int idCommand; int dwData; int iString; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; } ;
struct TYPE_14__ {int iItem; int cButtons; int* pCurrent; int cbBytesPerRecord; TYPE_1__ tbButton; } ;
struct TYPE_13__ {int iItem; int cbData; int* pData; int* pCurrent; int /*<<< orphan*/  cButtons; } ;
struct TYPE_11__ {int idCommand; int iString; int /*<<< orphan*/  dwData; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; int /*<<< orphan*/  iBitmap; } ;
struct TYPE_12__ {int cchText; char* pszText; TYPE_2__ tbButton; int /*<<< orphan*/  iItem; } ;
typedef  TYPE_3__ NMTOOLBARA ;
typedef  TYPE_4__ NMTBSAVE ;
typedef  TYPE_5__ NMTBRESTORE ;
typedef  TYPE_6__ NMTBHOTITEM ;
typedef  TYPE_7__ NMTBGETINFOTIPA ;
typedef  TYPE_8__ NMTBDISPINFOA ;
typedef  TYPE_9__ NMHDR ;
typedef  int LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  void* INT_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BTNS_SEP ; 
 int /*<<< orphan*/  FALSE ; 
#define  TBN_GETBUTTONINFOA 134 
#define  TBN_GETDISPINFOA 133 
#define  TBN_GETDISPINFOW 132 
#define  TBN_GETINFOTIPA 131 
#define  TBN_HOTITEMCHANGE 130 
#define  TBN_RESTORE 129 
#define  TBN_SAVE 128 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TBSTATE_HIDDEN ; 
 int /*<<< orphan*/  TRUE ; 
 char* alloced_str ; 
 int /*<<< orphan*/  compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_ResetDispTextPtr ; 
 int /*<<< orphan*/  g_dwExpectedDispInfoMask ; 
 int /*<<< orphan*/  g_fBlockHotItemChange ; 
 int /*<<< orphan*/  g_fExpectedHotItemNew ; 
 int /*<<< orphan*/  g_fExpectedHotItemOld ; 
 int /*<<< orphan*/  g_fReceivedHotItemChange ; 
 int* heap_alloc (int) ; 
 char* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static LRESULT parent_wnd_notify(LPARAM lParam)
{
    NMHDR *hdr = (NMHDR *)lParam;
    NMTBHOTITEM *nmhi;
    NMTBDISPINFOA *nmdisp;
    switch (hdr->code)
    {
        case TBN_HOTITEMCHANGE:
            nmhi = (NMTBHOTITEM *)lParam;
            g_fReceivedHotItemChange = TRUE;
            if (g_fExpectedHotItemOld != g_fExpectedHotItemNew)
            {
                compare(nmhi->idOld, g_fExpectedHotItemOld, "%d");
                compare(nmhi->idNew, g_fExpectedHotItemNew, "%d");
            }
            if (g_fBlockHotItemChange)
                return 1;
            break;

        case TBN_GETDISPINFOA:
            ok(FALSE, "TBN_GETDISPINFOA received\n");
            break;

        case TBN_GETINFOTIPA:
        {
            NMTBGETINFOTIPA *tbgit = (NMTBGETINFOTIPA*)lParam;

            if (g_ResetDispTextPtr)
            {
                tbgit->pszText = NULL;
                return 0;
            }
            break;
        }
        case TBN_GETDISPINFOW:
            nmdisp = (NMTBDISPINFOA *)lParam;

            compare(nmdisp->dwMask, g_dwExpectedDispInfoMask, "%x");
            ok(nmdisp->pszText == NULL, "pszText is not NULL\n");
        break;
        case TBN_SAVE:
        {
            NMTBSAVE *save = (NMTBSAVE *)lParam;
            if (save->iItem == -1)
            {
                save->cbData = save->cbData * 2 + 11 * sizeof(DWORD);
                save->pData = heap_alloc( save->cbData );
                save->pData[0] = 0xcafe;
                save->pCurrent = save->pData + 1;
            }
            else
            {
                save->pCurrent[0] = 0xcafe0000 + save->iItem;
                save->pCurrent++;
            }

            /* Add on 5 more pseudo buttons. */
            if (save->iItem == save->cButtons - 1)
            {
                save->pCurrent[0] = 0xffffffff;
                save->pCurrent[1] = 0xcafe0007;
                save->pCurrent[2] = 0xfffffffe;
                save->pCurrent[3] = 0xcafe0008;
                save->pCurrent[4] = 0x80000000;
                save->pCurrent[5] = 0xcafe0009;
                save->pCurrent[6] = 0x7fffffff;
                save->pCurrent[7] = 0xcafe000a;
                save->pCurrent[8] = 0x100;
                save->pCurrent[9] = 0xcafe000b;
            }

            /* Return value is ignored */
            return 1;
        }
        case TBN_RESTORE:
        {
            NMTBRESTORE *restore = (NMTBRESTORE *)lParam;

            if (restore->iItem == -1)
            {
                ok( restore->cButtons == 25, "got %d\n", restore->cButtons );
                ok( *restore->pCurrent == 0xcafe, "got %08x\n", *restore->pCurrent );
                /* Skip the last one */
                restore->cButtons = 11;
                restore->pCurrent++;
                /* BytesPerRecord is ignored */
                restore->cbBytesPerRecord = 10;
            }
            else
            {
                ok( *restore->pCurrent == 0xcafe0000 + restore->iItem, "got %08x\n", *restore->pCurrent );
                if (restore->iItem < 7 || restore->iItem == 10)
                {
                    ok( restore->tbButton.iBitmap == -1, "got %08x\n", restore->tbButton.iBitmap );
                    if (restore->iItem < 7)
                        ok( restore->tbButton.idCommand == restore->iItem * 2 + 1, "%d: got %08x\n", restore->iItem, restore->tbButton.idCommand );
                    else
                        ok( restore->tbButton.idCommand == 0x7fffffff, "%d: got %08x\n", restore->iItem, restore->tbButton.idCommand );
                    ok( restore->tbButton.fsState == 0, "%d: got %02x\n", restore->iItem, restore->tbButton.fsState );
                    ok( restore->tbButton.fsStyle == 0, "%d: got %02x\n", restore->iItem, restore->tbButton.fsStyle );
                }
                else
                {
                    ok( restore->tbButton.iBitmap == 8, "got %08x\n", restore->tbButton.iBitmap );
                    ok( restore->tbButton.idCommand == 0, "%d: got %08x\n", restore->iItem, restore->tbButton.idCommand );
                    if (restore->iItem == 7)
                        ok( restore->tbButton.fsState == 0, "%d: got %02x\n", restore->iItem, restore->tbButton.fsState );
                    else
                        ok( restore->tbButton.fsState == TBSTATE_HIDDEN, "%d: got %02x\n", restore->iItem, restore->tbButton.fsState );
                    ok( restore->tbButton.fsStyle == BTNS_SEP, "%d: got %02x\n", restore->iItem, restore->tbButton.fsStyle );
                }

                ok( restore->tbButton.dwData == 0, "got %08lx\n", restore->tbButton.dwData );
                ok( restore->tbButton.iString == 0, "got %08lx\n", restore->tbButton.iString );

                restore->tbButton.iBitmap = 0;
                restore->tbButton.fsState = TBSTATE_ENABLED;
                restore->tbButton.fsStyle = 0;
                restore->tbButton.dwData = restore->iItem;

                if (restore->iItem == 0)
                {
                    restore->tbButton.iString = (INT_PTR)heap_alloc_zero( 8 );
                    strcpy( (char *)restore->tbButton.iString, "foo" );
                }
                else if (restore->iItem == 1)
                    restore->tbButton.iString = 2;
                else
                    restore->tbButton.iString = -1;

                restore->pCurrent++;
                /* Altering cButtons after the 1st call makes no difference. */
                restore->cButtons--;
            }

            /* Returning non-zero from the 1st call aborts the restore,
               otherwise the return value is ignored. */
            if (restore->iItem == -1) return 0;
            return 1;
        }
        case TBN_GETBUTTONINFOA:
        {
            NMTOOLBARA *tb = (NMTOOLBARA *)lParam;
            tb->tbButton.iBitmap = 0;
            tb->tbButton.fsState = 0;
            tb->tbButton.fsStyle = 0;
            tb->tbButton.dwData = 0;
            ok( tb->cchText == 128, "got %d\n", tb->cchText );
            switch (tb->iItem)
            {
            case 0:
                tb->tbButton.idCommand = 7;
                alloced_str = heap_alloc_zero( 8 );
                strcpy( alloced_str, "foo" );
                tb->tbButton.iString = (INT_PTR)alloced_str;
                return 1;
            case 1:
                tb->tbButton.idCommand = 9;
                tb->tbButton.iString = 0;
                /* tb->pszText is ignored */
                strcpy( tb->pszText, "foo" );
                return 1;
           case 2:
                tb->tbButton.idCommand = 11;
                tb->tbButton.iString = 3;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}