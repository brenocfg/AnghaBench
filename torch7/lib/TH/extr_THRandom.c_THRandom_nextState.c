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
struct TYPE_3__ {unsigned long* state; int left; scalar_t__ next; } ;
typedef  TYPE_1__ THGenerator ;

/* Variables and functions */
 unsigned long TWIST (unsigned long,unsigned long) ; 
 int m ; 
 int n ; 

void THRandom_nextState(THGenerator *_generator)
{
  unsigned long *p = _generator->state;
  int j;

  _generator->left = n;
  _generator->next = 0;

  for(j = n-m+1; --j; p++)
    *p = p[m] ^ TWIST(p[0], p[1]);

  for(j = m; --j; p++)
    *p = p[m-n] ^ TWIST(p[0], p[1]);

  *p = p[m-n] ^ TWIST(p[0], _generator->state[0]);
}