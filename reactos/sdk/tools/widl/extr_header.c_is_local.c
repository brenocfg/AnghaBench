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
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_LOCAL ; 
 int is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int is_local(const attr_list_t *a)
{
  return is_attr(a, ATTR_LOCAL);
}