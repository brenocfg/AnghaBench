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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_6__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  gc_marktrace (TYPE_2__*,int /*<<< orphan*/ ) ; 

void lj_gc_barriertrace(global_State *g, uint32_t traceno)
{
  if (g->gc.state == GCSpropagate || g->gc.state == GCSatomic)
    gc_marktrace(g, traceno);
}