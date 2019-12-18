#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  adns_status ;
typedef  TYPE_2__* adns_query ;
struct TYPE_7__ {TYPE_1__* answer; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__query_done (TYPE_2__*) ; 
 int /*<<< orphan*/  adns__reset_preserved (TYPE_2__*) ; 

void adns__query_fail(adns_query qu, adns_status stat) {
  adns__reset_preserved(qu);
  qu->answer->status= stat;
  adns__query_done(qu);
}