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
 int /*<<< orphan*/ * EnsureUTF8 (char*) ; 
 int /*<<< orphan*/ * IsUTF8 (char const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void test (const char *in, const char *out)
{
    bool isutf8 = !strcmp (in, out);
    char *str = strdup (in);
    if (str == NULL)
        abort ();

    if (isutf8)
        printf ("\"%s\" should be accepted...\n", in);
    else
        printf ("\"%s\" should be rewritten as \"%s\"...\n", in, out);

    if ((IsUTF8 (in) != NULL) != isutf8)
    {
        printf (" ERROR: IsUTF8 (%s) failed\n", in);
        exit (1);
    }

    if ((EnsureUTF8 (str) != NULL) != isutf8)
    {
        printf (" ERROR: EnsureUTF8 (%s) failed\n", in);
        exit (2);
    }

    if (strcmp (str, out))
    {
        printf (" ERROR: got \"%s\"\n", str);
        exit (3);
    }

    if ((EnsureUTF8 (str) == NULL) || IsUTF8 (str) == NULL)
    {
        printf (" ERROR: EnsureUTF8 (%s) is not UTF-8\n", in);
        exit (4);
    }
    free (str);
}