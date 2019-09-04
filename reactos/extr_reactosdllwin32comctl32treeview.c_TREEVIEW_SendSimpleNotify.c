#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TREEVIEW_SendRealNotify (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
TREEVIEW_SendSimpleNotify(const TREEVIEW_INFO *infoPtr, UINT code)
{
    NMHDR hdr;
    return TREEVIEW_SendRealNotify(infoPtr, code, &hdr);
}