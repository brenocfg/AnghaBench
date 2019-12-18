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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int J2K_CFMT ; 
 int /*<<< orphan*/  J2K_CODESTREAM_MAGIC ; 
 int JP2_CFMT ; 
 int /*<<< orphan*/  JP2_MAGIC ; 
 int /*<<< orphan*/  JP2_RFC3745_MAGIC ; 
 int JPT_CFMT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int get_file_format (char const*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

__attribute__((used)) static int infile_format(const char *fname)
{
    FILE *reader;
    const char *s, *magic_s;
    int ext_format, magic_format;
    unsigned char buf[12];
    size_t l_nb_read;

    reader = fopen(fname, "rb");

    if (reader == NULL) {
        return -1;
    }

    memset(buf, 0, 12);
    l_nb_read = fread(buf, 1, 12, reader);
    fclose(reader);
    if (l_nb_read != 12) {
        return -1;
    }



    ext_format = get_file_format(fname);

    if (ext_format == JPT_CFMT) {
        return JPT_CFMT;
    }

    if (memcmp(buf, JP2_RFC3745_MAGIC, 12) == 0 || memcmp(buf, JP2_MAGIC, 4) == 0) {
        magic_format = JP2_CFMT;
        magic_s = ".jp2";
    } else if (memcmp(buf, J2K_CODESTREAM_MAGIC, 4) == 0) {
        magic_format = J2K_CFMT;
        magic_s = ".j2k or .jpc or .j2c";
    } else {
        return -1;
    }

    if (magic_format == ext_format) {
        return ext_format;
    }

    s = fname + strlen(fname) - 4;

    fputs("\n===========================================\n", stderr);
    fprintf(stderr, "The extension of this file is incorrect.\n"
            "FOUND %s. SHOULD BE %s\n", s, magic_s);
    fputs("===========================================\n", stderr);

    return magic_format;
}