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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 scalar_t__ TYPE_VOID ; 
 scalar_t__ type_get_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int is_void(const type_t *t)
{
    return type_get_type(t) == TYPE_VOID;
}