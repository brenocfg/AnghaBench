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
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  memcpy (double*,unsigned char*,int) ; 

int sqliterkParseNumber(const unsigned char *data, int offset, double *value)
{
    if (!data || !value) {
        return SQLITERK_MISUSE;
    }
    unsigned char out[8];
    const unsigned char *begin = data + offset;
    int i;
    for (i = 0; i < 8; i++) {
        // All float values in SQLite is big-endian with 8 lengths.
        // For further informantion, see [Record Format] chapter at
        // https://www.sqlite.org/fileformat2.html
        out[i] = begin[8 - 1 - i];
    }
    memcpy(value, out, 8);
    return SQLITERK_OK;
}