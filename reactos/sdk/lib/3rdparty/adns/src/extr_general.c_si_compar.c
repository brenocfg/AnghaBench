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
struct sinfo {int /*<<< orphan*/  const st; } ;
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */

__attribute__((used)) static int si_compar(const void *key, const void *elem) {
  const adns_status *st= key;
  const struct sinfo *si= elem;

  return *st < si->st ? -1 : *st > si->st ? 1 : 0;
}