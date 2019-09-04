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
struct TYPE_3__ {int /*<<< orphan*/  hwndTreeView; } ;
typedef  TYPE_1__ browse_info ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HTREEITEM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVGN_CARET ; 
 int /*<<< orphan*/  TVM_EDITLABELW ; 
 int /*<<< orphan*/  TVM_SELECTITEM ; 

__attribute__((used)) static HRESULT BrsFolder_Rename(browse_info *info, HTREEITEM rename)
{
    SendMessageW(info->hwndTreeView, TVM_SELECTITEM, TVGN_CARET, (LPARAM)rename);
    SendMessageW(info->hwndTreeView, TVM_EDITLABELW, 0, (LPARAM)rename);
    return S_OK;
}