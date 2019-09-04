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
struct TYPE_3__ {int cyBarHeight; void* bands; scalar_t__ nBands; void* cyRowHeights; scalar_t__ nRows; int /*<<< orphan*/  rcClient; } ;
typedef  TYPE_1__ rbsize_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 void* heap_alloc_zero (int) ; 

__attribute__((used)) static rbsize_result_t rbsize_init(int cleft, int ctop, int cright, int cbottom, int cyBarHeight, int nRows, int nBands)
{
    rbsize_result_t ret;

    SetRect(&ret.rcClient, cleft, ctop, cright, cbottom);
    ret.cyBarHeight = cyBarHeight;
    ret.nRows = 0;
    ret.cyRowHeights = heap_alloc_zero(nRows * sizeof(int));
    ret.nBands = 0;
    ret.bands = heap_alloc_zero(nBands * sizeof(*ret.bands));

    return ret;
}