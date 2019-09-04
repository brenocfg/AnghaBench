#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct recvd_message {size_t message; int flags; int wParam; int line; char* descr; scalar_t__* output; void* lParam; int /*<<< orphan*/  hwnd; } ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  hwndInsertAfter; } ;
typedef  TYPE_5__ WINDOWPOS ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_20__ {int CtlType; int CtlID; int itemID; int itemAction; int itemState; } ;
struct TYPE_12__ {int type; int ctl_id; int item_id; int action; int state; } ;
struct TYPE_13__ {void* lp; TYPE_1__ item; } ;
struct TYPE_19__ {TYPE_2__ u; } ;
struct TYPE_18__ {int CtlType; int CtlID; int itemID; scalar_t__ itemData; } ;
struct TYPE_14__ {int CtlType; int CtlID; int itemID; int wParam; } ;
struct TYPE_15__ {int wp; TYPE_3__ item; } ;
struct TYPE_17__ {TYPE_4__ u; } ;
struct TYPE_11__ {int CtlID; int itemID1; int itemID2; int CtlType; scalar_t__ itemData2; scalar_t__ itemData1; int /*<<< orphan*/  hwndItem; } ;
typedef  TYPE_6__ MEASURE_ITEM_STRUCT ;
typedef  TYPE_7__ MEASUREITEMSTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_8__ DRAW_ITEM_STRUCT ;
typedef  TYPE_9__ DRAWITEMSTRUCT ;
typedef  TYPE_10__ COMPAREITEMSTRUCT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t HCBT_SETFOCUS ; 
 struct recvd_message* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct recvd_message* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct recvd_message*,int) ; 
 int LBS_HASSTRINGS ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int ODT_COMBOBOX ; 
 int ODT_LISTBOX ; 
 int ODT_MENU ; 
 int SWP_NOZORDER ; 
 int TRUE ; 
#define  WM_COMPAREITEM 132 
#define  WM_DRAWITEM 131 
#define  WM_MEASUREITEM 130 
#define  WM_WINDOWPOSCHANGED 129 
#define  WM_WINDOWPOSCHANGING 128 
 int /*<<< orphan*/  assert (struct recvd_message*) ; 
 int beginpaint ; 
 int defwinproc ; 
 int /*<<< orphan*/  get_winpos_flags (int) ; 
 void* hash_Ly (char const*) ; 
 void* hash_Ly_W (int /*<<< orphan*/  const*) ; 
 int hook ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int parent ; 
 int posted ; 
 int sent ; 
 struct recvd_message* sequence ; 
 int sequence_cnt ; 
 int /*<<< orphan*/  sequence_cs ; 
 int sequence_size ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,...) ; 
 int strlen (scalar_t__*) ; 
 int winevent_hook ; 

__attribute__((used)) static void add_message_(int line, const struct recvd_message *msg)
{
    struct recvd_message *seq;

    EnterCriticalSection( &sequence_cs );
    if (!sequence)
    {
	sequence_size = 10;
	sequence = HeapAlloc( GetProcessHeap(), 0, sequence_size * sizeof(*sequence) );
    }
    if (sequence_cnt == sequence_size) 
    {
	sequence_size *= 2;
	sequence = HeapReAlloc( GetProcessHeap(), 0, sequence, sequence_size * sizeof(*sequence) );
    }
    assert(sequence);

    seq = &sequence[sequence_cnt++];
    seq->hwnd = msg->hwnd;
    seq->message = msg->message;
    seq->flags = msg->flags;
    seq->wParam = msg->wParam;
    seq->lParam = msg->lParam;
    seq->line   = line;
    seq->descr  = msg->descr;
    seq->output[0] = 0;
    LeaveCriticalSection( &sequence_cs );

    if (msg->descr)
    {
        if (msg->flags & hook)
        {
            static const char * const CBT_code_name[10] =
            {
                "HCBT_MOVESIZE",
                "HCBT_MINMAX",
                "HCBT_QS",
                "HCBT_CREATEWND",
                "HCBT_DESTROYWND",
                "HCBT_ACTIVATE",
                "HCBT_CLICKSKIPPED",
                "HCBT_KEYSKIPPED",
                "HCBT_SYSCOMMAND",
                "HCBT_SETFOCUS"
            };
            const char *code_name = (msg->message <= HCBT_SETFOCUS) ? CBT_code_name[msg->message] : "Unknown";

            sprintf( seq->output, "%s: hook %d (%s) wp %08lx lp %08lx",
                     msg->descr, msg->message, code_name, msg->wParam, msg->lParam );
        }
        else if (msg->flags & winevent_hook)
        {
            sprintf( seq->output, "%s: winevent %p %08x %08lx %08lx",
                     msg->descr, msg->hwnd, msg->message, msg->wParam, msg->lParam );
        }
        else
        {
            switch (msg->message)
            {
            case WM_WINDOWPOSCHANGING:
            case WM_WINDOWPOSCHANGED:
            {
                WINDOWPOS *winpos = (WINDOWPOS *)msg->lParam;

                sprintf( seq->output, "%s: %p WM_WINDOWPOS%s wp %08lx lp %08lx after %p x %d y %d cx %d cy %d flags %s",
                          msg->descr, msg->hwnd,
                          (msg->message == WM_WINDOWPOSCHANGING) ? "CHANGING" : "CHANGED",
                          msg->wParam, msg->lParam, winpos->hwndInsertAfter,
                          winpos->x, winpos->y, winpos->cx, winpos->cy,
                          get_winpos_flags(winpos->flags) );

                /* Log only documented flags, win2k uses 0x1000 and 0x2000
                 * in the high word for internal purposes
                 */
                seq->wParam = winpos->flags & 0xffff;
                /* We are not interested in the flags that don't match under XP and Win9x */
                seq->wParam &= ~SWP_NOZORDER;
                break;
            }

            case WM_DRAWITEM:
            {
                DRAW_ITEM_STRUCT di;
                DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT *)msg->lParam;

                sprintf( seq->output, "%s: %p WM_DRAWITEM: type %x, ctl_id %x, item_id %x, action %x, state %x",
                         msg->descr, msg->hwnd, dis->CtlType, dis->CtlID,
                         dis->itemID, dis->itemAction, dis->itemState);

                di.u.lp = 0;
                di.u.item.type = dis->CtlType;
                di.u.item.ctl_id = dis->CtlID;
                if (dis->CtlType == ODT_LISTBOX ||
                    dis->CtlType == ODT_COMBOBOX ||
                    dis->CtlType == ODT_MENU)
                    di.u.item.item_id = dis->itemID;
                di.u.item.action = dis->itemAction;
                di.u.item.state = dis->itemState;

                seq->lParam = di.u.lp;
                break;
            }

            case WM_MEASUREITEM:
            {
                MEASURE_ITEM_STRUCT mi;
                MEASUREITEMSTRUCT *mis = (MEASUREITEMSTRUCT *)msg->lParam;
                BOOL is_unicode_data = TRUE;

                sprintf( seq->output, "%s: %p WM_MEASUREITEM: CtlType %#x, CtlID %#x, itemID %#x, itemData %#lx",
                         msg->descr, msg->hwnd, mis->CtlType, mis->CtlID,
                         mis->itemID, mis->itemData);

                if (mis->CtlType == ODT_LISTBOX)
                {
                    HWND ctrl = GetDlgItem(msg->hwnd, mis->CtlID);
                    is_unicode_data = GetWindowLongA(ctrl, GWL_STYLE) & LBS_HASSTRINGS;
                }

                mi.u.wp = 0;
                mi.u.item.CtlType = mis->CtlType;
                mi.u.item.CtlID = mis->CtlID;
                mi.u.item.itemID = mis->itemID;
                mi.u.item.wParam = msg->wParam;
                seq->wParam = mi.u.wp;
                if (is_unicode_data)
                    seq->lParam = mis->itemData ? hash_Ly_W((const WCHAR *)mis->itemData) : 0;
                else
                    seq->lParam = mis->itemData ? hash_Ly((const char *)mis->itemData) : 0;
                break;
            }

            case WM_COMPAREITEM:
            {
                COMPAREITEMSTRUCT *cis = (COMPAREITEMSTRUCT *)msg->lParam;
                HWND ctrl = GetDlgItem(msg->hwnd, cis->CtlID);
                BOOL is_unicode_data = TRUE;

                ok(msg->wParam == cis->CtlID, "expected %#x, got %#lx\n", cis->CtlID, msg->wParam);
                ok(cis->hwndItem == ctrl, "expected %p, got %p\n", ctrl, cis->hwndItem);
                ok((int)cis->itemID1 >= 0, "expected >= 0, got %d\n", cis->itemID1);
                ok((int)cis->itemID2 == -1, "expected -1, got %d\n", cis->itemID2);

                sprintf( seq->output, "%s: %p WM_COMPAREITEM: CtlType %#x, CtlID %#x, itemID1 %#x, itemData1 %#lx, itemID2 %#x, itemData2 %#lx",
                         msg->descr, msg->hwnd, cis->CtlType, cis->CtlID,
                         cis->itemID1, cis->itemData1, cis->itemID2, cis->itemData2);

                if (cis->CtlType == ODT_LISTBOX)
                    is_unicode_data = GetWindowLongA(ctrl, GWL_STYLE) & LBS_HASSTRINGS;

                if (is_unicode_data)
                {
                    seq->wParam = cis->itemData1 ? hash_Ly_W((const WCHAR *)cis->itemData1) : 0;
                    seq->lParam = cis->itemData2 ? hash_Ly_W((const WCHAR *)cis->itemData2) : 0;
                }
                else
                {
                    seq->wParam = cis->itemData1 ? hash_Ly((const char *)cis->itemData1) : 0;
                    seq->lParam = cis->itemData2 ? hash_Ly((const char *)cis->itemData2) : 0;
                }
                break;
            }

            default:
                if (msg->message >= 0xc000) return;  /* ignore registered messages */
                sprintf( seq->output, "%s: %p %04x wp %08lx lp %08lx",
                         msg->descr, msg->hwnd, msg->message, msg->wParam, msg->lParam );
            }
            if (msg->flags & (sent|posted|parent|defwinproc|beginpaint))
                sprintf( seq->output + strlen(seq->output), " (flags %x)", msg->flags );
        }
    }
}