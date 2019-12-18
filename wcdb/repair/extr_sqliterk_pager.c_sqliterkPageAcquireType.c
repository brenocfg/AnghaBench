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
struct TYPE_4__ {int pagesize; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ sqliterk_pager ;
typedef  int sqliterk_page_type ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int sqliterkOSRead (int /*<<< orphan*/ ,scalar_t__,unsigned char*,size_t*) ; 
 scalar_t__ sqliterkPagenoHeaderOffset (int) ; 
 int sqliterkPagerIsPagenoValid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqliterkParseInt (unsigned char*,int /*<<< orphan*/ ,int,int*) ; 
#define  sqliterk_page_type_interior_index 131 
#define  sqliterk_page_type_interior_table 130 
#define  sqliterk_page_type_leaf_index 129 
#define  sqliterk_page_type_leaf_table 128 
 int sqliterk_page_type_unknown ; 

int sqliterkPageAcquireType(sqliterk_pager *pager,
                            int pageno,
                            sqliterk_page_type *type)
{
    // TODO: for encrypted databases, decode the whole page.
    // Use sqliterkPageAcquire instead.

    if (!pager || sqliterkPagerIsPagenoValid(pager, pageno) != SQLITERK_OK ||
        !type) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    unsigned char typedata;
    size_t typesize = 1;
    rc = sqliterkOSRead(pager->file,
                        sqliterkPagenoHeaderOffset(pageno) +
                            (pageno - 1) * pager->pagesize,
                        &typedata, &typesize);
    if (rc != SQLITERK_OK) {
        goto sqliterkPageAcquireType_Failed;
    }

    int theType;
    sqliterkParseInt(&typedata, 0, 1, &theType);
    switch (theType) {
        case sqliterk_page_type_interior_index:
        case sqliterk_page_type_interior_table:
        case sqliterk_page_type_leaf_index:
        case sqliterk_page_type_leaf_table:
            *type = theType;
            break;
        default:
            *type = sqliterk_page_type_unknown;
            break;
    }
    return SQLITERK_OK;

sqliterkPageAcquireType_Failed:
    *type = sqliterk_page_type_unknown;
    return rc;
}