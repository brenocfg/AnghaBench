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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * child; scalar_t__ nActiveChildren; } ;
typedef  TYPE_1__ MDICLIENTINFO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HWND MDI_GetChildByID(HWND hwnd, UINT id, MDICLIENTINFO *ci)
{
    int i;

    for (i = 0; ci->nActiveChildren; i++)
    {
        if (GetWindowLongPtrW( ci->child[i], GWLP_ID ) == id)
            return ci->child[i];
    }
    return 0;
}