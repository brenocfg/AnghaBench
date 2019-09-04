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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  quitnow (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void usageerr(const char *why) {
  fprintf(stderr,"adnsresfilter: bad usage: %s\n",why);
  usage();
  quitnow(1);
}