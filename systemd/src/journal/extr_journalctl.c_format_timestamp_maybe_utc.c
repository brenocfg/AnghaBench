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
 scalar_t__ arg_utc ; 
 char* format_timestamp (char*,size_t,int /*<<< orphan*/ ) ; 
 char* format_timestamp_utc (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *format_timestamp_maybe_utc(char *buf, size_t l, usec_t t) {

        if (arg_utc)
                return format_timestamp_utc(buf, l, t);

        return format_timestamp(buf, l, t);
}