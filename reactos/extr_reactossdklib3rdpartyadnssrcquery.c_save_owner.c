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
typedef  TYPE_1__* adns_query ;
struct TYPE_6__ {scalar_t__* owner; } ;
typedef  TYPE_2__ adns_answer ;
struct TYPE_5__ {TYPE_2__* answer; } ;

/* Variables and functions */
 scalar_t__* adns__alloc_preserved (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 

__attribute__((used)) static int save_owner(adns_query qu, const char *owner, int ol) {
  /* Returns 1 if OK, otherwise there was no memory. */
  adns_answer *ans;

  ans= qu->answer;
  assert(!ans->owner);

  ans->owner= adns__alloc_preserved(qu, (size_t) ol+1);  if (!ans->owner) return 0;

  memcpy(ans->owner,owner, (size_t) ol);
  ans->owner[ol]= 0;
  return 1;
}