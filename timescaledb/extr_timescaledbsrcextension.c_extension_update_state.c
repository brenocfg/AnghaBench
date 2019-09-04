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
 int /*<<< orphan*/  extension_current_state () ; 
 int extension_set_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
extension_update_state()
{
	return extension_set_state(extension_current_state());
}