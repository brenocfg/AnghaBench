#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int HeaderSize; void* TransUniDefaultChar; void* UniDefaultChar; void* TransDefaultChar; void* DefaultChar; void* MaximumCharacterSize; void* CodePage; } ;
typedef  TYPE_1__ NLS_FILE_HEADER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strstr (char*,char*) ; 
 int strtoul (char*,char**,int) ; 

int
txt_get_header(const char *file_path, NLS_FILE_HEADER *header)
{
    FILE *file;
    char *p;
    char buf[256];
    uint32_t line = 0;
    int res = 0;
    int found;
    uint32_t val;

    file = fopen(file_path, "r");
    if (!file)
    {
        printf("Unable to read TXT file.\n");
        return 0;
    }

    /* Find CODEPAGE entry */
    found = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        ++line;

        p = strstr(buf, "CODEPAGE");
        if (p)
        {
            /* Length of CODEPAGE string is 8 chars */
            p += 8;

            /* Skip all spaces after CODEPAGE */
            while (isspace(*p)) ++p;

            /* Convert string to uint32_t */
            val = strtoul(p, &p, 10);

            /* Validate codepage value */
            if (val > 0xFFFF)
            {
                printf("Wrong codepage: %u (line: %u)\n", val, line);
                goto Cleanup;
            }

            header->CodePage = (uint16_t)val;

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("CODEPAGE not found.\n");
        goto Cleanup;
    }

    /* Find CPINFO entry */
    found = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        ++line;

        p = strstr(buf, "CPINFO");
        if (p)
        {
            /* Length of CPINFO string is 6 chars */
            p += 6;

            /* Skip all spaces after CPINFO */
            while (isspace(*p)) ++p;

            /* Convert string to uint32_t */
            val = strtoul(p, &p, 10);

            /* Validate value */
            if (val != 1 && val != 2)
            {
                printf("Wrong character size: %u (line: %u)\n", val, line);
                goto Cleanup;
            }

            header->MaximumCharacterSize = (uint16_t)val;

            /* Skip all spaces after character size */
            while (isspace(*p)) ++p;

            /* Convert string to uint32_t */
            val = strtoul(p, &p, 16);
            header->DefaultChar = (uint16_t)val;
            /* By default set value as DefaultChar */
            header->TransDefaultChar = (uint16_t)val;

            /* Skip all spaces after default char */
            while (isspace(*p)) ++p;

            /* Convert string to uint32_t */
            val = strtoul(p, &p, 16);
            header->UniDefaultChar = (uint16_t)val;
            /* By default set value as UniDefaultChar */
            header->TransUniDefaultChar = (uint16_t)val;

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("CPINFO not found.\n");
        goto Cleanup;
    }

    header->HeaderSize = sizeof(NLS_FILE_HEADER) / sizeof(uint16_t);

    res = 1;

Cleanup:
    fclose(file);

    return res;
}