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
struct config {unsigned int dot; struct config* bp; TYPE_1__* rp; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */

unsigned statehash(struct config *a)
{
  unsigned h=0;
  while( a ){
    h = h*571 + a->rp->index*37 + a->dot;
    a = a->bp;
  }
  return h;
}