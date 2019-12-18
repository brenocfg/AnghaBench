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
typedef  int /*<<< orphan*/  WriteStringFileFlags ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int write_string_stream_ts (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int write_string_stream(FILE *f, const char *line, WriteStringFileFlags flags) {
        return write_string_stream_ts(f, line, flags, NULL);
}