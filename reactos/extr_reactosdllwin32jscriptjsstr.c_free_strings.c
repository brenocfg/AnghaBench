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
 scalar_t__ empty_str ; 
 int /*<<< orphan*/  jsstr_release (scalar_t__) ; 
 scalar_t__ nan_str ; 
 scalar_t__ null_bstr_str ; 
 scalar_t__ undefined_str ; 

void free_strings(void)
{
    if(empty_str)
        jsstr_release(empty_str);
    if(nan_str)
        jsstr_release(nan_str);
    if(undefined_str)
        jsstr_release(undefined_str);
    if(null_bstr_str)
        jsstr_release(null_bstr_str);
}