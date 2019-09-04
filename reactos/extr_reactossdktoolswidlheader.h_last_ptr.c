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
 int /*<<< orphan*/  is_declptr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_pointer_get_ref (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int last_ptr(const type_t *type)
{
    return is_ptr(type) && !is_declptr(type_pointer_get_ref(type));
}