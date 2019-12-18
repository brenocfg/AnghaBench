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
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  profile_state ; 
 int /*<<< orphan*/  profile_trigger (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void profile_signal(int sig)
{
  UNUSED(sig);
  profile_trigger(&profile_state);
}