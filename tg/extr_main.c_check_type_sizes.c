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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  logprintf (char*) ; 

void check_type_sizes (void) {
  if (sizeof (int) != 4u) {
    logprintf ("sizeof (int) isn't equal 4.\n");
    exit (1);
  }
  if (sizeof (char) != 1u) {
    logprintf ("sizeof (char) isn't equal 1.\n");
    exit (1);
  }
}