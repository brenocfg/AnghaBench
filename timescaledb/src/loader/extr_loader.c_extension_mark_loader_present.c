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
 int /*<<< orphan*/  RENDEZVOUS_LOADER_PRESENT_NAME ; 
 void** find_rendezvous_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loader_present ; 

__attribute__((used)) static void
extension_mark_loader_present()
{
	void **presentptr = find_rendezvous_variable(RENDEZVOUS_LOADER_PRESENT_NAME);

	*presentptr = &loader_present;
}