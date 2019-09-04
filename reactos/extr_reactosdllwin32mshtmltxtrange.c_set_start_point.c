#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  off; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_6__ {int /*<<< orphan*/  nsrange; } ;
typedef  TYPE_2__ HTMLTxtRange ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMRange_SetStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_start_point(HTMLTxtRange *This, const rangepoint_t *start)
{
    nsresult nsres = nsIDOMRange_SetStart(This->nsrange, start->node, start->off);
    if(NS_FAILED(nsres))
        ERR("failed: %08x\n", nsres);
}