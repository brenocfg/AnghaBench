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
typedef  enum type_type { ____Placeholder_type_type } type_type ;

/* Variables and functions */
 int /*<<< orphan*/  type_get_real_type (int /*<<< orphan*/  const*) ; 
 int type_get_type_detect_alias (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum type_type type_get_type(const type_t *type)
{
    return type_get_type_detect_alias(type_get_real_type(type));
}