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
struct TYPE_3__ {int /*<<< orphan*/  plw; } ;
typedef  TYPE_1__ DLCollector ;

/* Variables and functions */
 int /*<<< orphan*/  plwAdd (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void dlcAddPos(DLCollector *pCollector, int iColumn, int iPos,
                      int iStartOffset, int iEndOffset){
  plwAdd(&pCollector->plw, iColumn, iPos, iStartOffset, iEndOffset);
}