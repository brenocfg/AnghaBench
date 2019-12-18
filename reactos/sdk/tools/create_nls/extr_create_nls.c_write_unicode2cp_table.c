#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int MaxCharSize; scalar_t__* DefaultChar; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CPINFOEXA ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (void*) ; 
 int fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  patch_aliases (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static BOOL write_unicode2cp_table(FILE *out, CPINFOEXA *cpi, WCHAR *table)
{
    void *u2cp;
    WCHAR *wc;
    CHAR *c;
    int i;
    BOOL ret = TRUE;

    u2cp = malloc(cpi->MaxCharSize * 65536);
    if(!u2cp) {
        printf("Not enough memory for Unicode to Codepage table\n");
        return FALSE;
    }

    if(cpi->MaxCharSize == 2) {
        wc = (WCHAR *)u2cp;
        for(i = 0; i < 65536; i++)
            wc[i] = *(WCHAR *)cpi->DefaultChar;

        for(i = 0; i < 65536; i++)
            if (table[i] != '?')
                wc[table[i]] = (WCHAR)i;
    }
    else {
        c = (CHAR *)u2cp;
        for(i = 0; i < 65536; i++)
            c[i] = cpi->DefaultChar[0];

        for(i = 0; i < 256; i++)
            if (table[i] != '?')
                c[table[i]] = (CHAR)i;
    }

    patch_aliases(u2cp, cpi);

    if(fwrite(u2cp, 1, cpi->MaxCharSize * 65536, out) != cpi->MaxCharSize * 65536)
        ret = FALSE;

    free(u2cp);

    return ret;
}