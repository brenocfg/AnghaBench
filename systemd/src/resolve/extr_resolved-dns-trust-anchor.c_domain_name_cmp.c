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
 int dns_name_compare_func (char* const,char* const) ; 

__attribute__((used)) static int domain_name_cmp(char * const *a, char * const *b) {
        return dns_name_compare_func(*a, *b);
}