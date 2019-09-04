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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  __JSVAL_OBJ (int /*<<< orphan*/ ) ; 
 scalar_t__ is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL is_null_instance(jsval_t v)
{
    return is_null(v) || (is_object_instance(v) && !__JSVAL_OBJ(v));
}