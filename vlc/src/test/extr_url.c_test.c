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
typedef  char* (* conv_t ) (char const*) ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  test_compare (char const*,char const*,char*) ; 

__attribute__((used)) static void test (conv_t f, const char *in, const char *out)
{
    char *res = f(in);
    test_compare(in, out, res);
    free(res);
}