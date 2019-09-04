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
typedef  int /*<<< orphan*/  mmio ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {scalar_t__ fccIOProc; int cchBuffer; char* pchBuffer; int wErrorRet; int dwFlags; char* pchNext; char* pchEndRead; char* pchEndWrite; int lBufOffset; int lDiskOffset; } ;
typedef  int MMRESULT ;
typedef  TYPE_1__ MMIOINFO ;
typedef  int LPCSTR ;
typedef  scalar_t__ HMMIO ;

/* Variables and functions */
 scalar_t__ FOURCC_DOS ; 
 scalar_t__ FOURCC_MEM ; 
 int MMIO_ALLOCBUF ; 
 int MMIO_READ ; 
 int MMIO_WRITE ; 
 int MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmioClose (scalar_t__,int /*<<< orphan*/ ) ; 
 int mmioGetInfo (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioOpenA (char*,TYPE_1__*,int) ; 
 int mmioSeek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmioSetBuffer (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_mmioSetBuffer(char *fname)
{
    char buf[256];
    MMRESULT ret;
    HMMIO hmmio;
    MMIOINFO mmio;

    memset(&mmio, 0, sizeof(mmio));
    mmio.fccIOProc = fname ? FOURCC_DOS : FOURCC_MEM;
    mmio.cchBuffer = sizeof(buf);
    mmio.pchBuffer = buf;
    hmmio = mmioOpenA(fname, &mmio, MMIO_READ);
    if (fname && !hmmio)
    {
        trace("No optional %s file. Skipping the test\n", fname);
        return;
    }
    ok(hmmio != 0, "mmioOpenA error %u\n", mmio.wErrorRet);

    memset(&mmio, 0, sizeof(mmio));
    ret = mmioGetInfo(hmmio, &mmio, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioGetInfo error %u\n", ret);
    ok(mmio.dwFlags == MMIO_READ, "expected MMIO_READ, got %x\n", mmio.dwFlags);
    ok(mmio.wErrorRet == MMSYSERR_NOERROR, "expected MMSYSERR_NOERROR, got %u\n", mmio.wErrorRet);
    ok(mmio.fccIOProc == (fname ? FOURCC_DOS : FOURCC_MEM), "got %4.4s\n", (LPCSTR)&mmio.fccIOProc);
    ok(mmio.cchBuffer == sizeof(buf), "got %u\n", mmio.cchBuffer);
    ok(mmio.pchBuffer == buf, "expected %p, got %p\n", buf, mmio.pchBuffer);
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    if (mmio.fccIOProc == FOURCC_DOS)
        ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);
    else
        ok(mmio.pchEndRead == mmio.pchBuffer + mmio.cchBuffer, "expected %p + %d, got %p\n", mmio.pchBuffer, mmio.cchBuffer, mmio.pchEndRead);
    ok(mmio.pchEndWrite == mmio.pchBuffer + mmio.cchBuffer, "expected %p + %d, got %p\n", mmio.pchBuffer, mmio.cchBuffer, mmio.pchEndWrite);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.lDiskOffset == 0, "expected 0, got %d\n", mmio.lDiskOffset);

    ret = mmioSeek(hmmio, 0, SEEK_CUR);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = mmioSetBuffer(hmmio, NULL, 0, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioSetBuffer error %u\n", ret);

    memset(&mmio, 0, sizeof(mmio));
    ret = mmioGetInfo(hmmio, &mmio, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioGetInfo error %u\n", ret);
    ok(mmio.dwFlags == MMIO_READ, "expected MMIO_READ, got %x\n", mmio.dwFlags);
    ok(mmio.wErrorRet == MMSYSERR_NOERROR, "expected MMSYSERR_NOERROR, got %u\n", mmio.wErrorRet);
    ok(mmio.fccIOProc == (fname ? FOURCC_DOS : FOURCC_MEM), "got %4.4s\n", (LPCSTR)&mmio.fccIOProc);
    ok(mmio.cchBuffer == 0, "got not 0\n");
    ok(mmio.pchBuffer == NULL, "got not NULL buf\n");
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);
    ok(mmio.pchEndWrite == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndWrite);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.lDiskOffset == 0, "expected 0, got %d\n", mmio.lDiskOffset);

    ret = mmioSeek(hmmio, 0, SEEK_CUR);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = mmioSetBuffer(hmmio, NULL, 0, MMIO_ALLOCBUF);
    ok(ret == MMSYSERR_NOERROR, "mmioSetBuffer error %u\n", ret);

    memset(&mmio, 0, sizeof(mmio));
    ret = mmioGetInfo(hmmio, &mmio, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioGetInfo error %u\n", ret);
    ok(mmio.dwFlags == MMIO_READ, "expected MMIO_READ, got %x\n", mmio.dwFlags);
    ok(mmio.wErrorRet == MMSYSERR_NOERROR, "expected MMSYSERR_NOERROR, got %u\n", mmio.wErrorRet);
    ok(mmio.fccIOProc == (fname ? FOURCC_DOS : FOURCC_MEM), "got %4.4s\n", (LPCSTR)&mmio.fccIOProc);
    ok(mmio.cchBuffer == 0, "got not 0\n");
    ok(mmio.pchBuffer == NULL, "got not NULL buf\n");
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);
    ok(mmio.pchEndWrite == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndWrite);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.lDiskOffset == 0, "expected 0, got %d\n", mmio.lDiskOffset);

    ret = mmioSeek(hmmio, 0, SEEK_CUR);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = mmioSetBuffer(hmmio, buf, 0, MMIO_ALLOCBUF);
    ok(ret == MMSYSERR_NOERROR, "mmioSetBuffer error %u\n", ret);

    memset(&mmio, 0, sizeof(mmio));
    ret = mmioGetInfo(hmmio, &mmio, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioGetInfo error %u\n", ret);
    ok(mmio.dwFlags == MMIO_READ, "expected MMIO_READ, got %x\n", mmio.dwFlags);
    ok(mmio.wErrorRet == MMSYSERR_NOERROR, "expected MMSYSERR_NOERROR, got %u\n", mmio.wErrorRet);
    ok(mmio.fccIOProc == (fname ? FOURCC_DOS : FOURCC_MEM), "got %4.4s\n", (LPCSTR)&mmio.fccIOProc);
    ok(mmio.cchBuffer == 0, "got not 0\n");
    ok(mmio.pchBuffer == buf, "expected %p, got %p\n", buf, mmio.pchBuffer);
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);
    ok(mmio.pchEndWrite == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndWrite);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.lDiskOffset == 0, "expected 0, got %d\n", mmio.lDiskOffset);

    ret = mmioSeek(hmmio, 0, SEEK_CUR);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = mmioSetBuffer(hmmio, NULL, 256, MMIO_WRITE|MMIO_ALLOCBUF);
    ok(ret == MMSYSERR_NOERROR, "mmioSetBuffer error %u\n", ret);

    memset(&mmio, 0, sizeof(mmio));
    ret = mmioGetInfo(hmmio, &mmio, 0);
    ok(ret == MMSYSERR_NOERROR, "mmioGetInfo error %u\n", ret);
    ok(mmio.dwFlags == (MMIO_READ|MMIO_ALLOCBUF), "expected MMIO_READ|MMIO_ALLOCBUF, got %x\n", mmio.dwFlags);
    ok(mmio.wErrorRet == MMSYSERR_NOERROR, "expected MMSYSERR_NOERROR, got %u\n", mmio.wErrorRet);
    ok(mmio.fccIOProc == (fname ? FOURCC_DOS : FOURCC_MEM), "got %4.4s\n", (LPCSTR)&mmio.fccIOProc);
    ok(mmio.cchBuffer == 256, "got %u\n", mmio.cchBuffer);
    ok(mmio.pchBuffer != NULL, "expected not NULL\n");
    ok(mmio.pchBuffer != buf, "expected != buf\n");
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", buf, mmio.pchEndRead);
    ok(mmio.pchEndWrite == mmio.pchBuffer + mmio.cchBuffer, "expected %p + %d, got %p\n", mmio.pchBuffer, mmio.cchBuffer, mmio.pchEndWrite);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.lDiskOffset == 0, "expected 0, got %d\n", mmio.lDiskOffset);

    ret = mmioSeek(hmmio, 0, SEEK_CUR);
    ok(ret == 0, "expected 0, got %d\n", ret);

    mmioClose(hmmio, 0);
}