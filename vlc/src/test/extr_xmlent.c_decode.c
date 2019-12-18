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
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vlc_xml_decode (char*) ; 

__attribute__((used)) static void decode (const char *in, const char *out)
{
    char buf[strlen (in) + 1];

    printf ("\"%s\" -> \"%s\" ?\n", in, out);
    strcpy (buf, in);
    vlc_xml_decode (buf);

    if (strcmp (buf, out))
    {
        printf (" ERROR: got \"%s\"\n", buf);
        exit (2);
    }
}