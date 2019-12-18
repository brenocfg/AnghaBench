#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_2__ {int p2; } ;

/* Variables and functions */
 TYPE_1__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3VdbeChangeP2(Vdbe *p, u32 addr, int val){
  sqlite3VdbeGetOp(p,addr)->p2 = val;
}