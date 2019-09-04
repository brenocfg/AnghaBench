#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* adns_query ;
struct TYPE_4__ {size_t preserved_allocd; } ;

/* Variables and functions */
 size_t MEM_ROUND (size_t) ; 
 void* adns__alloc_interim (TYPE_1__*,size_t) ; 

void *adns__alloc_preserved(adns_query qu, size_t sz) {
  void *rv;

  sz= MEM_ROUND(sz);
  rv= adns__alloc_interim(qu,sz);
  if (!rv) return 0;
  qu->preserved_allocd += sz;
  return rv;
}