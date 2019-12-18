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
 int /*<<< orphan*/  str_compare ; 
 int /*<<< orphan*/  strv_length (char**) ; 
 int /*<<< orphan*/  typesafe_qsort (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char **strv_sort(char **l) {
        typesafe_qsort(l, strv_length(l), str_compare);
        return l;
}