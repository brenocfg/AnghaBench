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
 int /*<<< orphan*/  get_home_directory () ; 
 int /*<<< orphan*/  tasprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tfree_str (char*) ; 

char *make_full_path (char *s) {
  if (*s != '/') {
    char *t = s;
    tasprintf (&s, "%s/%s", get_home_directory (), s);
    tfree_str (t);
  }
  return s;
}