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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ isspace (char) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strstr (char*,char*) ; 
 int strtoul (char*,char**,int) ; 

uint16_t*
txt_get_mb_table(const char *file_path, uint16_t uni_default_char)
{
    uint16_t *table;
    char buf[256];
    char *p;
    uint32_t count = 0;
    uint32_t index;
    uint32_t line = 0;
    int found;
    int res = 0;
    FILE *file;

    table = malloc(256 * sizeof(uint16_t));
    if (!table)
    {
        printf("Memory allocation failure\n");
        return NULL;
    }

    /* Set default value for all table items */
    for (index = 0; index <= 255; index++)
        table[index] = uni_default_char;

    file = fopen(file_path, "r");
    if (!file)
    {
        printf("Unable to read TXT file.\n");
        goto Cleanup;
    }

    /* Find MBTABLE entry */
    found = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        ++line;

        p = strstr(buf, "MBTABLE");
        if (p)
        {
            p += 7;

            /* Skip spaces */
            while (isspace(*p)) ++p;

            count = strtoul(p, &p, 10);
            if (count == 0 || count > 256)
            {
                printf("Wrong MBTABLE size: %u (line: %u)\n", count, line);
                goto Cleanup;
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("MBTABLE not found.\n");
        goto Cleanup;
    }

    /* Parse next line */
    while (fgets(buf, sizeof(buf), file) && count)
    {
        uint32_t cp_char;
        uint32_t uni_char;

        ++line;

        p = buf;

        /* Skip spaces */
        while (isspace(*p)) ++p;

        if (!*p || p[0] == ';')
            continue;

        cp_char = strtoul(p, &p, 16);
        if (cp_char > 0xFF)
        {
            printf("Wrong char value: %u (line: %u)\n", cp_char, line);
            goto Cleanup;
        }

        /* Skip spaces */
        while (isspace(*p)) ++p;

        uni_char = strtoul(p, &p, 16);
        if (uni_char > 0xFFFF)
        {
            printf("Wrong unicode char value: %u (line: %u)\n", uni_char, line);
            goto Cleanup;
        }

        table[cp_char] = uni_char;
        --count;
    }

    res = 1;

Cleanup:
    if (!res)
    {
        free(table);
        table = NULL;
    }

    fclose(file);

    return table;
}