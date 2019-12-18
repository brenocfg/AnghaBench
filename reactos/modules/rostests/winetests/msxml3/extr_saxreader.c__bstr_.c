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
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_str_from_narrow (char const*) ; 
 int /*<<< orphan*/ * alloced_bstrs ; 
 size_t alloced_bstrs_count ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static BSTR _bstr_(const char *str)
{
    assert(alloced_bstrs_count < ARRAY_SIZE(alloced_bstrs));
    alloced_bstrs[alloced_bstrs_count] = alloc_str_from_narrow(str);
    return alloced_bstrs[alloced_bstrs_count++];
}