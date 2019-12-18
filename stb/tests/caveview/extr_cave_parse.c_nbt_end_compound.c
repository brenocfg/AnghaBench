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
struct TYPE_3__ {scalar_t__* cur; scalar_t__ nesting; } ;
typedef  TYPE_1__ nbt ;

/* Variables and functions */
 scalar_t__ TAG_End ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void nbt_end_compound(nbt *n) // end a compound
{
   assert(*n->cur == TAG_End);
   assert(n->nesting != 0);
   ++n->cur;
   --n->nesting;   
}