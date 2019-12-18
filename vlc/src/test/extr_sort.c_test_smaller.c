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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_smaller(const char *small, const char *big,
                         int (*cmp)(const char *, const char *))
{
    int ret = cmp(small, big);
    if (ret >= 0) {
        fprintf(stderr, "Failure: \"%s\" %s \"%s\"\n",
                small, ret ? ">" : "==", big);
        exit(1);
    }
}