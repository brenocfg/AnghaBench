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
struct TYPE_3__ {size_t nButtons; int /*<<< orphan*/ * prcButtons; } ;
typedef  TYPE_1__ tbsize_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void tbsize_addbutton(tbsize_result_t *tbsr, int left, int top, int right, int bottom) {
    SetRect(&tbsr->prcButtons[tbsr->nButtons], left, top, right, bottom);
    tbsr->nButtons++;
}