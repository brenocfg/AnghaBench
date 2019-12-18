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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void test_compare(const char *in, const char *exp, const char *res)
{
    if (res == NULL)
    {
        if (exp != NULL)
            fprintf(stderr, "\"%s\" returned NULL, expected \"%s\"\n",
                    in, exp);
        else
            return;
    }
    else
    {
        if (exp == NULL)
            fprintf(stderr, "\"%s\" returned \"%s\", expected NULL\n",
                    in, res);
        else
        if (strcmp(res, exp))
            fprintf(stderr, "\"%s\" returned \"%s\", expected \"%s\"\n",
                    in, res, exp);
        else
            return;
    }
    exit(2);
}