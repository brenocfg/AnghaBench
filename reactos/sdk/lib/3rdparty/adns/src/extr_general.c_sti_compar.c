#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stinfo {scalar_t__ stmax; } ;
typedef  scalar_t__ adns_status ;

/* Variables and functions */
 struct stinfo const* stinfos ; 

__attribute__((used)) static int sti_compar(const void *key, const void *elem) {
  const adns_status *st= key;
  const struct stinfo *sti= elem;

  adns_status here, min, max;

  here= *st;
  min= (sti==stinfos) ? 0 : sti[-1].stmax+1;
  max= sti->stmax;

  return here < min  ? -1 : here > max ? 1 : 0;
}