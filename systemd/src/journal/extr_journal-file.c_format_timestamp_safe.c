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
 char* format_timestamp (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char* format_timestamp_safe(char *buf, size_t l, usec_t t) {
        const char *x;

        x = format_timestamp(buf, l, t);
        if (x)
                return x;
        return " --- ";
}