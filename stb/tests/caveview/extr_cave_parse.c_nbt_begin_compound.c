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
struct TYPE_3__ {scalar_t__* cur; int /*<<< orphan*/  nesting; } ;
typedef  TYPE_1__ nbt ;

/* Variables and functions */
 scalar_t__ TAG_Compound ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void nbt_begin_compound(nbt *n) // start a compound
{
   assert(*n->cur == TAG_Compound);
   // skip header
   n->cur += 3 + (n->cur[1]*256 + n->cur[2]);
   ++n->nesting;
}