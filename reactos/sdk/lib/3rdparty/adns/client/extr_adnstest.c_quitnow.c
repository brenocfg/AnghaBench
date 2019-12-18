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

/* Variables and functions */
 int /*<<< orphan*/  adns_finish (scalar_t__) ; 
 scalar_t__ ads ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs ; 
 int /*<<< orphan*/  types_a ; 

__attribute__((used)) static void quitnow(int rc) {
  free(mcs);
  free(types_a);
  if (ads) adns_finish(ads);

  exit(rc);
}