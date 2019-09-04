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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  quitnow (int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

void sysfail(const char *what, int errnoval) {
  fprintf(stderr,"adnshost failed: %s: %s\n",what,strerror(errnoval));
  quitnow(10);
}