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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * null_bstr_str ; 

BOOL is_null_bstr(jsstr_t *str)
{
    return str == null_bstr_str;
}