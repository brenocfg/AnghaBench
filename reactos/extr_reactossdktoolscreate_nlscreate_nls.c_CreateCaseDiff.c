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
typedef  int /*<<< orphan*/  buf ;
typedef  size_t WORD ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 size_t* to_lower_org ; 
 size_t* to_upper_org ; 

__attribute__((used)) static BOOL CreateCaseDiff(char *table_name)
{
    char buf[256];
    char *p;
    WORD code, case_mapping;
    FILE *file;
    int line;

    to_upper_org = (WORD *)calloc(65536, sizeof(WORD));
    if(!to_upper_org) {
        printf("Not enough memory for to upper table\n");
        return FALSE;
    }

    to_lower_org = (WORD *)calloc(65536, sizeof(WORD));
    if(!to_lower_org) {
        printf("Not enough memory for to lower table\n");
        return FALSE;
    }

    file = fopen(table_name, "r");
    if(file == NULL) {
        printf("Could not open file \"%s\"\n", table_name);
        return FALSE;
    }

    line = 0;

    while(fgets(buf, sizeof(buf), file)) {
        line++;
        p = buf;
        while(*p && isspace(*p)) p++;

        if(!*p)
            continue;

        /* 0. Code value */
        code = (WORD)strtol(p, &p, 16);

        //if(code != 0x9A0 && code != 0xBA0)
            //continue;

        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 1. Character name */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 2. General Category */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 3. Canonical Combining Classes */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 4. Bidirectional Category */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 5. Character Decomposition Mapping */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 6. Decimal digit value */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 7. Digit value */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 8. Numeric value */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 9. Mirrored */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 10. Unicode 1.0 Name */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 11. 10646 comment field */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;

        /* 12. Uppercase Mapping */
        while(*p && isspace(*p)) p++;
        if(!*p) continue;
        if(*p != ';') {
            case_mapping = (WORD)strtol(p, &p, 16);
            to_upper_org[code] = case_mapping - code;
            while(*p && *p != ';') p++;
        }
        else
            p++;

        /* 13. Lowercase Mapping */
        while(*p && isspace(*p)) p++;
        if(!*p) continue;
        if(*p != ';') {
            case_mapping = (WORD)strtol(p, &p, 16);
            to_lower_org[code] = case_mapping - code;
            while(*p && *p != ';') p++;
        }
        else
            p++;

        /* 14. Titlecase Mapping */
        while(*p && *p != ';') p++;
        if(!*p)
            continue;
        p++;
    }

    fclose(file);

    return TRUE;
}