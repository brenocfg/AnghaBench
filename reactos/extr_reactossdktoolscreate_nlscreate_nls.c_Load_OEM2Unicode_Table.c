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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int CodePage; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  TYPE_1__ CPINFOEXA ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static WCHAR *Load_OEM2Unicode_Table(char *table_name, WCHAR *def_table, UINT cp, CPINFOEXA *cpi)
{
    char buf[256];
    char *p;
    DWORD n, value;
    FILE *file;
    WCHAR *table;
    int line;

    printf("Loading oem glyph table \"%s\"\n", table_name);

    table = (WCHAR *)malloc(sizeof(WCHAR) * 65536);
    if(!table) {
        printf("Not enough memory for Codepage to Unicode table\n");
        return NULL;
    }

    memcpy(table, def_table, 65536 * sizeof(WCHAR));

    file = fopen(table_name, "r");
    if(file == NULL) {
        free(table);
        return NULL;
    }

    line = 0;

    while(fgets(buf, sizeof(buf), file)) {
        line++;
        p = buf;
        while(isspace(*p)) p++;

        if(!*p || p[0] == '#')
            continue;

        value = strtol(p, &p, 16);
        if(value > 0xFFFF) {
            printf("Line %d: Entry 0x%06lX: File \"%s\" corrupted\n", line, value, table_name);
            continue;
        }

        while(isspace(*p)) p++;

        if(!*p || p[0] == '#') {
            /*printf("Line %d: Entry 0x%02lX has no Unicode value\n", line, n);*/
            continue;
        }
        else {
            n = strtol(p, &p, 16);
            if(n > 0xFFFF) {
                printf("Line %d: Entry 0x%06lX unicode value: File \"%s\" corrupted\n", line, value, table_name);
                continue;
            }
        }

        if (cpi->CodePage == 864) {
            while(isspace(*p)) p++;

            if(!*p || p[0] == '#' || p[0] == '-') {
                /*printf("Line %d: Entry 0x%02lX has no Unicode value\n", line, n);*/
                continue;
            }
            else {
                n = strtol(p, &p, 16);
                if(n > 0xFFFF) {
                    printf("Line %d: Entry 0x%06lX oem value: File \"%s\" corrupted\n", line, value, table_name);
                }
                continue;
            }
        }

        table[n] = (WCHAR)value;
    }

    fclose(file);

    return table;
}