#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int info; } ;
struct TYPE_10__ {TYPE_2__ s; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
struct TYPE_11__ {TYPE_1__* bcbase; } ;
struct TYPE_8__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_4__ FuncState ;
typedef  TYPE_5__ ExpDesc ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbc_op (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void invertcond(FuncState *fs, ExpDesc *e)
{
  BCIns *ip = &fs->bcbase[e->u.s.info - 1].ins;
  setbc_op(ip, bc_op(*ip)^1);
}