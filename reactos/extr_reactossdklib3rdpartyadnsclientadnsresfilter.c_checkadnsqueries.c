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
struct treething {scalar_t__ qu; int /*<<< orphan*/ * ans; } ;
typedef  scalar_t__ adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;

/* Variables and functions */
 int EAGAIN ; 
 int ESRCH ; 
 int adns_check (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  ads ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void checkadnsqueries(void) {
  adns_query qu;
  adns_answer *ans;
  void *context;
  struct treething *foundthing;
  int r;

  for (;;) {
    qu= 0; context= 0; ans= 0;
    r= adns_check(ads,&qu,&ans,&context);
    if (r == ESRCH || r == EAGAIN) break;
    assert(!r);
    foundthing= context;
    foundthing->ans= ans;
    foundthing->qu= 0;
  }
}