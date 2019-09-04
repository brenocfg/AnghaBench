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
 scalar_t__ JSV_NULL ; 
 scalar_t__ __JSVAL_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL is_null(jsval_t v)
{
    return __JSVAL_TYPE(v) == JSV_NULL;
}