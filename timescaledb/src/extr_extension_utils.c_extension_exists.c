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
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_extension_oid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool inline extension_exists()
{
	return OidIsValid(get_extension_oid(EXTENSION_NAME, true));
}