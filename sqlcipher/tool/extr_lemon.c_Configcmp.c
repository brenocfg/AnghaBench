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
struct config {int dot; TYPE_1__* rp; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */

int Configcmp(const char *_a,const char *_b)
{
  const struct config *a = (struct config *) _a;
  const struct config *b = (struct config *) _b;
  int x;
  x = a->rp->index - b->rp->index;
  if( x==0 ) x = a->dot - b->dot;
  return x;
}