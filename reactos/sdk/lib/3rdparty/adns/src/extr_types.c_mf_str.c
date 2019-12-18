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
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int /*<<< orphan*/  adns__makefinal_str (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void mf_str(adns_query qu, void *datap) {
  char **rrp= datap;

  adns__makefinal_str(qu,rrp);
}