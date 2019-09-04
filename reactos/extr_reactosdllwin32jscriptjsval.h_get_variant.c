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
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 int /*<<< orphan*/ * __JSVAL_VAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline VARIANT *get_variant(jsval_t v)
{
    return __JSVAL_VAR(v);
}