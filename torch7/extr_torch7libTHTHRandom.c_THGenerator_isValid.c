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
struct TYPE_3__ {int seeded; scalar_t__ left; scalar_t__ next; } ;
typedef  TYPE_1__ THGenerator ;

/* Variables and functions */
 scalar_t__ n ; 

int THGenerator_isValid(THGenerator *_generator)
{
  if ((_generator->seeded == 1) &&
    (_generator->left > 0 && _generator->left <= n) && (_generator->next <= n))
    return 1;

  return 0;
}