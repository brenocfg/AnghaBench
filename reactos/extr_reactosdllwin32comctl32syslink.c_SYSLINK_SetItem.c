#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_12__ {int mask; int stateMask; int state; int /*<<< orphan*/  szUrl; int /*<<< orphan*/  szID; int /*<<< orphan*/  iLink; } ;
struct TYPE_9__ {void* szID; void* szUrl; int state; } ;
struct TYPE_10__ {TYPE_1__ Link; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  SYSLINK_INFO ;
typedef  void* PWSTR ;
typedef  TYPE_3__* PDOC_ITEM ;
typedef  int LRESULT ;
typedef  TYPE_4__ LITEM ;
typedef  int BOOL ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int FALSE ; 
 int /*<<< orphan*/  Free (void*) ; 
 int LIF_FLAGSMASK ; 
 int LIF_ITEMID ; 
 int LIF_ITEMINDEX ; 
 int LIF_STATE ; 
 int LIF_URL ; 
 int LIS_FOCUSED ; 
 int LIS_MASK ; 
 scalar_t__ L_MAX_URL_LENGTH ; 
 scalar_t__ MAX_LINKID_TEXT ; 
 TYPE_3__* SYSLINK_GetLinkItemByIndex (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSLINK_RepaintLink (int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  SYSLINK_SetFocusLink (int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  lstrcpynW (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static LRESULT SYSLINK_SetItem (const SYSLINK_INFO *infoPtr, const LITEM *Item)
{
    PDOC_ITEM di;
    int nc;
    PWSTR szId = NULL;
    PWSTR szUrl = NULL;
    BOOL Repaint = FALSE;

    if(!(Item->mask & LIF_ITEMINDEX) || !(Item->mask & (LIF_FLAGSMASK)))
    {
        ERR("Invalid Flags!\n");
        return FALSE;
    }

    di = SYSLINK_GetLinkItemByIndex(infoPtr, Item->iLink);
    if(di == NULL)
    {
        ERR("Link %d couldn't be found\n", Item->iLink);
        return FALSE;
    }

    if(Item->mask & LIF_ITEMID)
    {
        nc = min(lstrlenW(Item->szID), MAX_LINKID_TEXT - 1);
        szId = Alloc((nc + 1) * sizeof(WCHAR));
        if(szId)
        {
            lstrcpynW(szId, Item->szID, nc + 1);
        }
        else
        {
            ERR("Unable to allocate memory for link id\n");
            return FALSE;
        }
    }

    if(Item->mask & LIF_URL)
    {
        nc = min(lstrlenW(Item->szUrl), L_MAX_URL_LENGTH - 1);
        szUrl = Alloc((nc + 1) * sizeof(WCHAR));
        if(szUrl)
        {
            lstrcpynW(szUrl, Item->szUrl, nc + 1);
        }
        else
        {
            Free(szId);

            ERR("Unable to allocate memory for link url\n");
            return FALSE;
        }
    }

    if(Item->mask & LIF_ITEMID)
    {
        Free(di->u.Link.szID);
        di->u.Link.szID = szId;
    }

    if(Item->mask & LIF_URL)
    {
        Free(di->u.Link.szUrl);
        di->u.Link.szUrl = szUrl;
    }

    if(Item->mask & LIF_STATE)
    {
        UINT oldstate = di->u.Link.state;
        /* clear the masked bits */
        di->u.Link.state &= ~(Item->stateMask & LIS_MASK);
        /* copy the bits */
        di->u.Link.state |= (Item->state & Item->stateMask) & LIS_MASK;
        Repaint = (oldstate != di->u.Link.state);
        
        /* update the focus */
        SYSLINK_SetFocusLink(infoPtr, ((di->u.Link.state & LIS_FOCUSED) ? di : NULL));
    }
    
    if(Repaint)
    {
        SYSLINK_RepaintLink(infoPtr, di);
    }
    
    return TRUE;
}