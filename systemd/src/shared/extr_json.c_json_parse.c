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
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int json_parse_internal (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*,unsigned int*,int) ; 

int json_parse(const char *input, JsonVariant **ret, unsigned *ret_line, unsigned *ret_column) {
        return json_parse_internal(&input, NULL, ret, ret_line, ret_column, false);
}