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
typedef  int /*<<< orphan*/  sqliterk_page ;
typedef  int /*<<< orphan*/  sqliterk_column ;
typedef  int /*<<< orphan*/  sqliterk_btree ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int SQLITERK_CANCELLED ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int sqliterkBtreeParsePayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int sqliterkColumnAlloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqliterkColumnClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkColumnFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkColumnSetRowId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterkOSDebug (int,char*) ; 
 unsigned char* sqliterkPageGetData (int /*<<< orphan*/ *) ; 
 int sqliterkParseVarint (unsigned char const*,int,int*,int*) ; 
 int sqliterkParseVarint64 (unsigned char const*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sqliterkBtreeParseCell(sqliterk_btree *btree,
                                  sqliterk_page *page,
                                  const int *cellPointerArray,
                                  const int cellsCount)
{
    if (!btree || !page || !cellPointerArray || cellsCount < 0) {
        return SQLITERK_MISUSE;
    }
    const unsigned char *pagedata = sqliterkPageGetData(page);
    int rc = SQLITERK_OK;
    sqliterk_column *column;
    rc = sqliterkColumnAlloc(&column);
    if (rc != SQLITERK_OK) {
        goto sqliterkBtreeParsePayload_End;
    }

    int i;
    for (i = 0; i < cellsCount; i++) {
        sqliterkColumnClear(column);
        int offset = cellPointerArray[i];
        // Find payload
        int payloadSizeLength;
        int payloadSize;
        rc = sqliterkParseVarint(pagedata, offset, &payloadSizeLength,
                                 &payloadSize);
        if (rc != SQLITERK_OK) {
            goto sqliterkBtreeParsePayload_End;
        }
        offset += payloadSizeLength;

        int rowidLength;
        int64_t rowid;
        rc = sqliterkParseVarint64(pagedata, offset, &rowidLength, &rowid);
        if (rc != SQLITERK_OK) {
            goto sqliterkBtreeParsePayload_End;
        }
        offset += rowidLength;
        sqliterkColumnSetRowId(column, rowid);

        rc =
            sqliterkBtreeParsePayload(btree, page, offset, payloadSize, column);
        if (rc != SQLITERK_OK) {
            goto sqliterkBtreeParsePayload_End;
        }
    }
sqliterkBtreeParsePayload_End:
    if (column) {
        sqliterkColumnFree(column);
    }
    if (rc != SQLITERK_OK && rc != SQLITERK_CANCELLED) {
        sqliterkOSDebug(rc, "Failed to parse payload.");
    }
    return rc;
}