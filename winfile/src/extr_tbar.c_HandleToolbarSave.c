#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  hdr ;
typedef  void* WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {scalar_t__ iStartBmp; scalar_t__ Delta; } ;
struct TYPE_8__ {scalar_t__ dwData; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; scalar_t__ idCommand; scalar_t__ iBitmap; } ;
struct TYPE_10__ {int iItem; int cButtons; scalar_t__* pCurrent; TYPE_1__ tbButton; scalar_t__ cbData; scalar_t__* pData; } ;
struct TYPE_9__ {int cButtons; void* iExtP1; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; void* idCommand; void* iBitmap; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ TBSAVEITEM ;
typedef  TYPE_2__ TBSAVEHDR ;
typedef  TYPE_4__* LPNMTBSAVE ;
typedef  size_t INT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__* LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TBHDR_MAGIC ; 
 int /*<<< orphan*/  TBHDR_VERSION ; 
 TYPE_6__* extensions ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,TYPE_2__*,int) ; 

VOID
HandleToolbarSave(LPNMTBSAVE lpnmtSave)
{
    if (lpnmtSave->iItem == -1)
    {
        lpnmtSave->cbData = lpnmtSave->cbData + sizeof(TBSAVEHDR) + sizeof(TBSAVEITEM) * lpnmtSave->cButtons;
        lpnmtSave->pCurrent = lpnmtSave->pData = LocalAlloc(LPTR, lpnmtSave->cbData);

        // save global values: magic number, version and cButtons
        TBSAVEHDR hdr;
        hdr.magic = TBHDR_MAGIC;
        hdr.version = TBHDR_VERSION;
        hdr.cButtons = lpnmtSave->cButtons;
        memcpy(lpnmtSave->pCurrent, &hdr, sizeof(hdr));
        lpnmtSave->pCurrent = (DWORD *)((BYTE *)lpnmtSave->pCurrent + sizeof(hdr));
    }
    else
    {
        TBSAVEITEM item;
        DWORD baseId = 0;
        DWORD baseIbm = 0;

        // for extension buttons, remove bias for both idCommand and iBitmap
        if (lpnmtSave->tbButton.dwData != 0)
        {
            INT iExt = lpnmtSave->tbButton.dwData - 1;
            baseId = extensions[iExt].Delta;
            baseIbm = extensions[iExt].iStartBmp;
        }

        item.iBitmap = (WORD)(lpnmtSave->tbButton.iBitmap - baseIbm);
        item.idCommand = (WORD)(lpnmtSave->tbButton.idCommand - baseId);
        item.fsState = lpnmtSave->tbButton.fsState;
        item.fsStyle = lpnmtSave->tbButton.fsStyle;
        item.iExtP1 = (WORD)lpnmtSave->tbButton.dwData;

        memcpy(lpnmtSave->pCurrent, &item, sizeof(item));
        lpnmtSave->pCurrent = (DWORD *)((BYTE *)lpnmtSave->pCurrent + sizeof(item));
    }
}