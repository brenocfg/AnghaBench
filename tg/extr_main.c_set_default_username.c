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
 scalar_t__ default_username ; 
 int /*<<< orphan*/  tfree_str (scalar_t__) ; 
 scalar_t__ tstrdup (char const*) ; 

void set_default_username (const char *s) {
  if (default_username) { 
    tfree_str (default_username);
  }
  default_username = tstrdup (s);
}