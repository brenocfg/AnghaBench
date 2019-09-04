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
struct query_node {char const* owner; } ;
struct TYPE_3__ {char const* owner; } ;
typedef  TYPE_1__ adns_answer ;

/* Variables and functions */

__attribute__((used)) static const char *owner_show(struct query_node *qun, adns_answer *answer) {
  return answer->owner ? answer->owner : qun->owner;
}