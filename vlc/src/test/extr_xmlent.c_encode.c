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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* vlc_xml_encode (char const*) ; 

__attribute__((used)) static void encode (const char *in, const char *out)
{
    char *buf;

    printf ("\"%s\" -> \"%s\" ?\n", in, out);
    buf = vlc_xml_encode (in);

    if (buf == NULL)
    {
        puts(" ERROR: got NULL");
        exit(2);
    }

    if (strcmp (buf, out))
    {
        printf (" ERROR: got \"%s\"\n", buf);
        exit (2);
    }
    free (buf);
}