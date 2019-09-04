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
typedef  int /*<<< orphan*/  LPLVITEMW ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_GetItemT (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline BOOL LISTVIEW_GetItemW(const LISTVIEW_INFO *infoPtr, LPLVITEMW lpLVItem)
{
    return LISTVIEW_GetItemT(infoPtr, lpLVItem, TRUE);
}