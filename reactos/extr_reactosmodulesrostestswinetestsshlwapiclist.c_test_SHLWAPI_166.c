#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int QuadPart; } ;
struct dummystream {int readcalls; scalar_t__ writecalls; int seekcalls; int statcalls; TYPE_1__ pos; int /*<<< orphan*/  IStream_iface; scalar_t__ failreadcall; scalar_t__ failstatcall; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  InitDummyStream (struct dummystream*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pSHLWAPI_166 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL test_SHLWAPI_166(void)
{
  struct dummystream streamobj;
  BOOL bRet;

  if (!pSHLWAPI_166)
    return FALSE;

  InitDummyStream(&streamobj);
  bRet = pSHLWAPI_166(&streamobj.IStream_iface);

  if (bRet != TRUE)
    return FALSE; /* This version doesn't support stream ops on clists */

  ok(streamobj.readcalls == 0, "called Read()\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 0, "called Seek()\n");
  ok(streamobj.statcalls == 1, "wrong call count\n");

  streamobj.statcalls = 0;
  streamobj.pos.QuadPart = 50001;

  bRet = pSHLWAPI_166(&streamobj.IStream_iface);

  ok(bRet == FALSE, "failed after seek adjusted\n");
  ok(streamobj.readcalls == 0, "called Read()\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 0, "called Seek()\n");
  ok(streamobj.statcalls == 1, "wrong call count\n");

  /* Failure cases */
  InitDummyStream(&streamobj);
  streamobj.pos.QuadPart = 50001;
  streamobj.failstatcall = TRUE; /* 1: Stat() Bad, Read() OK */
  bRet = pSHLWAPI_166(&streamobj.IStream_iface);
  ok(bRet == FALSE, "should be FALSE after read is OK\n");
  ok(streamobj.readcalls == 1, "wrong call count\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 1, "wrong call count\n");
  ok(streamobj.statcalls == 1, "wrong call count\n");
  ok(streamobj.pos.QuadPart == 0, "Didn't seek to start\n");

  InitDummyStream(&streamobj);
  streamobj.pos.QuadPart = 50001;
  streamobj.failstatcall = TRUE;
  streamobj.failreadcall = TRUE; /* 2: Stat() Bad, Read() Bad Also */
  bRet = pSHLWAPI_166(&streamobj.IStream_iface);
  ok(bRet == TRUE, "Should be true after read fails\n");
  ok(streamobj.readcalls == 1, "wrong call count\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 0, "Called Seek()\n");
  ok(streamobj.statcalls == 1, "wrong call count\n");
  ok(streamobj.pos.QuadPart == 50001, "called Seek() after read failed\n");
  return TRUE;
}