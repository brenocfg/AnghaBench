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
struct TYPE_12__ {int /*<<< orphan*/ * pszCaption; } ;
struct TYPE_9__ {scalar_t__ nStartPage; } ;
struct TYPE_11__ {int dwFlags; TYPE_1__ u2; int /*<<< orphan*/  nPages; int /*<<< orphan*/  pszCaption; scalar_t__ pfnCallback; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  dwSize; } ;
struct TYPE_10__ {int useCallback; scalar_t__ active_page; int /*<<< orphan*/  nPages; TYPE_4__ ppshheader; } ;
typedef  TYPE_2__ PropSheetInfo ;
typedef  int /*<<< orphan*/  PROPSHEETHEADERW ;
typedef  TYPE_3__* LPCPROPSHEETHEADERW ;
typedef  int DWORD ;

/* Variables and functions */
 int INTRNL_ANY_WIZARD ; 
 int /*<<< orphan*/  IS_INTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROPSHEET_CollectSheetInfoCommon (TYPE_2__*,int) ; 
 int PSH_USECALLBACK ; 
 int PSH_USEPSTARTPAGE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_3__*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PROPSHEET_CollectSheetInfoW(LPCPROPSHEETHEADERW lppsh,
                                       PropSheetInfo * psInfo)
{
  DWORD dwSize = min(lppsh->dwSize,sizeof(PROPSHEETHEADERW));
  DWORD dwFlags = lppsh->dwFlags;

  psInfo->useCallback = (dwFlags & PSH_USECALLBACK) && (lppsh->pfnCallback);

  memcpy(&psInfo->ppshheader,lppsh,dwSize);
  TRACE("\n** PROPSHEETHEADER **\ndwSize\t\t%d\ndwFlags\t\t%08x\nhwndParent\t%p\nhInstance\t%p\npszCaption\t%s\nnPages\t\t%d\npfnCallback\t%p\n",
      lppsh->dwSize, lppsh->dwFlags, lppsh->hwndParent, lppsh->hInstance, debugstr_w(lppsh->pszCaption), lppsh->nPages, lppsh->pfnCallback);

  if (lppsh->dwFlags & INTRNL_ANY_WIZARD)
     psInfo->ppshheader.pszCaption = NULL;
  else
  {
     if (!IS_INTRESOURCE(lppsh->pszCaption))
       psInfo->ppshheader.pszCaption = heap_strdupW( lppsh->pszCaption );
  }
  psInfo->nPages = lppsh->nPages;

  if (dwFlags & PSH_USEPSTARTPAGE)
  {
    TRACE("PSH_USEPSTARTPAGE is on\n");
    psInfo->active_page = 0;
  }
  else
    psInfo->active_page = lppsh->u2.nStartPage;

  PROPSHEET_CollectSheetInfoCommon(psInfo, dwFlags);
}