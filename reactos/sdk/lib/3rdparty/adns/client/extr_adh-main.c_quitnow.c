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
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_id ; 

void quitnow(int rc) {
  if (ads) adns_finish(ads);
  free(buf);
  free(ov_id);
  exit(rc);
}