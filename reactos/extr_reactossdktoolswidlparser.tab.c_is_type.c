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
 int /*<<< orphan*/  current_namespace ; 
 int /*<<< orphan*/ * find_type (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int is_type(const char *name)
{
  return find_type(name, current_namespace, 0) != NULL;
}