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
typedef  int /*<<< orphan*/  usec_t ;

/* Variables and functions */
 char* format_timestamp_internal (char*,size_t,int /*<<< orphan*/ ,int,int) ; 

char *format_timestamp_us(char *buf, size_t l, usec_t t) {
        return format_timestamp_internal(buf, l, t, false, true);
}