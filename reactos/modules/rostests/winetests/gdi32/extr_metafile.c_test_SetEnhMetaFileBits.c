#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int nSize; int nBytes; int nHandles; scalar_t__ dSignature; int /*<<< orphan*/  iType; } ;
typedef  int /*<<< orphan*/ * HENHMETAFILE ;
typedef  TYPE_1__ ENHMETAHEADER ;
typedef  TYPE_1__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMR_HEADER ; 
 scalar_t__ ENHMETA_SIGNATURE ; 
 int ERROR_INVALID_DATA ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * SetEnhMetaFileBits (int,TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetEnhMetaFileBits(void)
{
    BYTE data[256];
    HENHMETAFILE hemf;
    ENHMETAHEADER *emh;

    memset(data, 0xAA, sizeof(data));
    SetLastError(0xdeadbeef);
    hemf = SetEnhMetaFileBits(sizeof(data), data);
    ok(!hemf, "SetEnhMetaFileBits should fail\n");
    ok(GetLastError() == ERROR_INVALID_DATA ||
       GetLastError() == ERROR_INVALID_PARAMETER, /* Win9x, WinMe */
       "expected ERROR_INVALID_DATA or ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    emh = (ENHMETAHEADER *)data;
    memset(emh, 0, sizeof(*emh));

    emh->iType = EMR_HEADER;
    emh->nSize = sizeof(*emh);
    emh->dSignature = ENHMETA_SIGNATURE;
    /* emh->nVersion  = 0x10000; XP doesn't care about version */
    emh->nBytes = sizeof(*emh);
    /* emh->nRecords = 1; XP doesn't care about records */
    emh->nHandles = 1; /* XP refuses to load a EMF if nHandles == 0 */

    SetLastError(0xdeadbeef);
    hemf = SetEnhMetaFileBits(emh->nBytes, data);
    ok(hemf != 0, "SetEnhMetaFileBits error %u\n", GetLastError());
    DeleteEnhMetaFile(hemf);

    /* XP refuses to load unaligned EMF */
    emh->nBytes++;
    SetLastError(0xdeadbeef);
    hemf = SetEnhMetaFileBits(emh->nBytes, data);
    ok(!hemf ||
       broken(hemf != NULL), /* Win9x, WinMe */
       "SetEnhMetaFileBits should fail\n");
    ok(GetLastError() == 0xdeadbeef, "Expected deadbeef, got %u\n", GetLastError());
    DeleteEnhMetaFile(hemf);

    emh->dSignature = 0;
    emh->nBytes--;
    SetLastError(0xdeadbeef);
    hemf = SetEnhMetaFileBits(emh->nBytes, data);
    ok(!hemf ||
       broken(hemf != NULL), /* Win9x, WinMe */
       "SetEnhMetaFileBits should fail\n");
    ok(GetLastError() == 0xdeadbeef, "Expected deadbeef, got %u\n", GetLastError());
    DeleteEnhMetaFile(hemf);
}