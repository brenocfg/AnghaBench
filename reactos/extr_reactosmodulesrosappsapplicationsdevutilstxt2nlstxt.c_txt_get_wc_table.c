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
typedef  int uint8_t ;
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
txt_get_wc_table(const char *file_path, uint16_t default_char, int is_dbcs)
{
    char buf[256];
    char *p;
    uint16_t *table;
    uint32_t index;
    uint32_t count = 0;
    uint32_t line = 0;
    int res = 0;
    int found;
    FILE *file;

    table = malloc(65536 * (is_dbcs ? sizeof(uint16_t) : sizeof(uint8_t)));
    if (!table)
    {
        printf("Memory allocation failure\n");
        return NULL;
    }

    /* Set default value for all table items */
    for (index = 0; index <= 65535; index++)
    {
        /* DBCS code page */
        if (is_dbcs)
        {
            uint16_t *tmp = (uint16_t*)table;
            tmp[index] = default_char;
        }
        /* SBCS code page */
        else
        {
            uint8_t *tmp = (uint8_t*)table;
            tmp[index] = default_char;
        }
    }

    file = fopen(file_path, "r");
    if (!file)
    {
        printf("Unable to read TXT file.\n");
        goto Cleanup;
    }

    /* Find WCTABLE entry */
    found = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        ++line;

        p = strstr(buf, "WCTABLE");
        if (p)
        {
            p += 7;

            /* Skip spaces */
            while (isspace(*p)) ++p;

            count = strtoul(p, &p, 10);
            if (count == 0 || count > 65536)
            {
                printf("Wrong WCTABLE size: %u (line: %u)\n", count, line);
                goto Cleanup;
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("WCTABLE not found.\n");
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

        uni_char = strtoul(p, &p, 16);
        if (uni_char > 0xFFFF)
        {
            printf("Wrong unicode char value: %u (line: %u)\n", uni_char, line);
            goto Cleanup;
        }

        /* Skip spaces */
        while (isspace(*p)) ++p;

        cp_char = strtoul(p, &p, 16);
        if ((is_dbcs && cp_char > 0xFFFF) || (!is_dbcs && cp_char > 0xFF))
        {
            printf("Wrong char value: %u (line: %u)\n", cp_char, line);
            goto Cleanup;
        }

        /* DBCS code page */
        if (is_dbcs)
        {
            uint16_t *tmp = (uint16_t*)table;
            tmp[uni_char] = cp_char;
        }
        /* SBCS code page */
        else
        {
            uint8_t *tmp = (uint8_t*)table;
            tmp[uni_char] = cp_char;
        }

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