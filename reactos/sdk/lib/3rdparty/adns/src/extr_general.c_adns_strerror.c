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
struct sinfo {char const* string; } ;
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */
 struct sinfo* findsinfo (int /*<<< orphan*/ ) ; 

const char *adns_strerror(adns_status st) {
  const struct sinfo *si;

  si= findsinfo(st);
  return si->string;
}