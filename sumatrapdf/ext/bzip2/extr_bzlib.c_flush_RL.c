#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state_in_ch; } ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  add_pair_to_block (TYPE_1__*) ; 
 int /*<<< orphan*/  init_RL (TYPE_1__*) ; 

__attribute__((used)) static
void flush_RL ( EState* s )
{
   if (s->state_in_ch < 256) add_pair_to_block ( s );
   init_RL ( s );
}