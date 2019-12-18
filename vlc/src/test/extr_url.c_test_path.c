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
 int /*<<< orphan*/  make_URI_def ; 
 int /*<<< orphan*/  test (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static inline void test_path (const char *in, const char *out)
{
    test (make_URI_def, in, out);
}