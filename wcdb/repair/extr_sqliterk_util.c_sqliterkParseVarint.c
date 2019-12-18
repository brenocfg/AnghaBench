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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int sqliterkParseVarint64 (unsigned char const*,int,int*,scalar_t__*) ; 

int sqliterkParseVarint(const unsigned char *data,
                        int offset,
                        int *length,
                        int *value)
{
    if (!value) {
        return SQLITERK_MISUSE;
    }
    int64_t out;
    int rc = sqliterkParseVarint64(data, offset, length, &out);
    if (rc != SQLITERK_OK) {
        return rc;
    }
    *value = (int) out;
    return SQLITERK_OK;
}