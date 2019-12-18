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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static char *
make_output_filename(const char *input_filename, const char *extension)
{
    char *output_filename;
    const char *c, *e;
    int len;

    if (extension == NULL) {
        fprintf(stderr, "no filename extension; cannot create output filename!\n");
        exit(1);
    }

    if (input_filename == NULL)
        c = "out";
    else {
        /* strip any leading path */
        c = strrchr(input_filename, '/');       /* *nix */
        if (c == NULL)
            c = strrchr(input_filename, '\\');  /* win32/dos */
        if (c != NULL)
            c++;                /* skip the path separator */
        else
            c = input_filename; /* no leading path */
    }

    /* make sure we haven't just stripped the last character */
    if (*c == '\0')
        c = "out";

    /* strip the extension */
    len = strlen(c);
    e = strrchr(c, '.');
    if (e != NULL)
        len -= strlen(e);

    /* allocate enough space for the base + ext */
    output_filename = (char *)malloc(len + strlen(extension) + 1);
    if (output_filename == NULL) {
        fprintf(stderr, "failed to allocate memory for output filename\n");
        exit(1);
    }

    strncpy(output_filename, c, len);
    strncpy(output_filename + len, extension, strlen(extension));
    *(output_filename + len + strlen(extension)) = '\0';

    /* return the new string */
    return (output_filename);
}