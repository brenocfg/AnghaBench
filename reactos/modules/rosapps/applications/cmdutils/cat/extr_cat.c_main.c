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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ARRAYSIZE (unsigned char*) ; 
 unsigned int EOF ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _stricmp (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 unsigned int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t fread (unsigned char**,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (unsigned char**,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  putchar (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 

int main(int argc, char* argv[])
{
    int i;
    FILE* in;
    unsigned char buff[512];
    size_t cnt, readcnt;

    if (argc >= 2)
    {
        if (_stricmp(argv[1], "-h"    ) == 0 ||
            _stricmp(argv[1], "--help") == 0 ||
            _stricmp(argv[1], "/?"    ) == 0 ||
            _stricmp(argv[1], "/help" ) == 0)
        {
            help();
            return 0;
        }
    }

    /* Set STDOUT to binary */
    _setmode(_fileno(stdout), O_BINARY);

    /* Special case where we run 'cat' without any argument: we use STDIN */
    if (argc <= 1)
    {
        unsigned int ch;

        /* Set STDIN to binary */
        _setmode(_fileno(stdin), O_BINARY);

#if 0 // Version using feof()
        ch = fgetc(stdin);
        while (!feof(stdin))
        {
            putchar(ch);
            ch = fgetc(stdin);
        }
#else
        while ((ch = fgetc(stdin)) != EOF)
        {
            putchar(ch);
        }
#endif

        return 0;
    }

    /* We have files: read them and output them to STDOUT */
    for (i = 1; i < argc; i++)
    {
        /* Open the file in binary read mode */
        in = fopen(argv[i], "rb");
        if (in == NULL)
        {
            fprintf(stderr, "Failed to open file '%s'\n", argv[i]);
            return -1;
        }

        /* Dump the file to STDOUT */
        cnt = 0; readcnt = 0;
        while (readcnt == cnt)
        {
            /* Read data from the input file */
            cnt = ARRAYSIZE(buff);
            readcnt = fread(&buff, sizeof(buff[0]), cnt, in);
            if (readcnt != cnt)
            {
                /*
                 * The real number of read bytes differs from the number of bytes
                 * we wanted to read, so either a reading error occurred, or EOF
                 * was reached while reading. Bail out if it is a reading error.
                 */
                if (!feof(in))
                {
                    fprintf(stderr, "Error while reading file '%s'\n", argv[i]);
                    fclose(in);
                    return -1;
                }
            }

            /* Nothing to be read anymore, so we can gracefully break */
            if (readcnt == 0) break;

            /* Write data to STDOUT */
            fwrite(&buff, sizeof(buff[0]), readcnt, stdout);
        }

        /* Finally close the file */
        fclose(in);
    }

    return 0;
}