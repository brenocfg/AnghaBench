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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* vlc_strcasestr (char const*,char const*) ; 

__attribute__((used)) static void test_strcasestr (const char *h, const char *n, ssize_t offset)
{
    printf ("\"%s\" should %sbe found in \"%s\"...\n", n,
            (offset != -1) ? "" : "not ", h);

    const char *ret = vlc_strcasestr (h, n);
    if (offset == -1)
    {
        if (ret != NULL)
        {
            printf ("ERROR: got \"%s\"\n", ret);
            exit (10);
        }
    }
    else
    {
        if (ret == NULL)
        {
            printf ("ERROR: not found\n");
            exit (11);
        }
        if ((ret - h) != offset)
        {
            printf ("ERROR: got \"%s\" instead of \"%s\"\n",
                    ret, h + offset);
            exit (12);
        }
    }
}