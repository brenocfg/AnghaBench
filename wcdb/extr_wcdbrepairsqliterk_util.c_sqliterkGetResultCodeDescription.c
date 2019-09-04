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
#define  SQLITERK_CANTOPEN 135 
#define  SQLITERK_DAMAGED 134 
#define  SQLITERK_DISCARD 133 
#define  SQLITERK_IOERR 132 
#define  SQLITERK_MISUSE 131 
#define  SQLITERK_NOMEM 130 
#define  SQLITERK_OK 129 
#define  SQLITERK_SHORT_READ 128 

const char *sqliterkGetResultCodeDescription(int result)
{
    switch (result) {
        case SQLITERK_OK:
            return "SQLITERK_OK";
        case SQLITERK_CANTOPEN:
            return "SQLITERK_CANTOPEN";
        case SQLITERK_MISUSE:
            return "SQLITERK_MISUSE";
        case SQLITERK_IOERR:
            return "SQLITERK_IOERR";
        case SQLITERK_NOMEM:
            return "SQLITERK_NOMEM";
        case SQLITERK_SHORT_READ:
            return "SQLITERK_SHORT_READ";
        case SQLITERK_DAMAGED:
            return "SQLITERK_DAMAGED";
        case SQLITERK_DISCARD:
            return "SQLITERK_DISCARD";
        default:
            break;
    }
    return "SQLITERK_UNKNOWN";
}