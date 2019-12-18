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
 int /*<<< orphan*/  abort () ; 
 int atoi (char const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  usage (char const*,int) ; 

__attribute__((used)) static void cmdline(int argc, const char **argv, const char **in,
                    char **out, char **out_with_ext, int *w)
{
    int idx = 1;
    size_t len;

    if (argc != 3 && argc != 5)
        usage(argv[0], argc != 2 || strcmp(argv[1], "-h"));

    *w = 0;

    if (argc == 5) {
        if (strcmp(argv[1], "-s"))
            usage(argv[0], 1);

        idx += 2; /* skip "-s width" */
        *w = atoi(argv[2]);
    }

    *in  = argv[idx++];
    *out = strdup(argv[idx++]);
    if (!*out)
        abort();

    len = strlen(*out);
    if (len >= 4 && !strcmp(*out + len - 4, ".png")) {
        *out_with_ext = *out;
        return;
    }

    /* We need to add .png extension to filename,
     * VLC relies on it to detect output format,
     * and nautilus doesn't give filenames ending in .png */

    *out_with_ext = malloc(len + sizeof ".png");
    if (!*out_with_ext)
        abort();
    strcpy(*out_with_ext, *out);
    strcat(*out_with_ext, ".png");
}