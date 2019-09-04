#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dummystream {int seekcalls; scalar_t__ statcalls; scalar_t__ readcalls; scalar_t__ writecalls; int /*<<< orphan*/  IStream_iface; } ;
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_6__ {long QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  InitDummyStream (struct dummystream*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pSHLWAPI_213 (int /*<<< orphan*/ *) ; 
 scalar_t__ pSHLWAPI_214 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void test_SHLWAPI_213(void)
{
  struct dummystream streamobj;
  ULARGE_INTEGER ul;
  LARGE_INTEGER ll;
  HRESULT hRet;

  if (!pSHLWAPI_213 || !pSHLWAPI_214)
    return;

  InitDummyStream(&streamobj);
  ll.QuadPart = 5000l;
  Seek(&streamobj.IStream_iface, ll, 0, NULL); /* Seek to 5000l */

  streamobj.seekcalls = 0;
  pSHLWAPI_213(&streamobj.IStream_iface); /* Should rewind */
  ok(streamobj.statcalls == 0, "called Stat()\n");
  ok(streamobj.readcalls == 0, "called Read()\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 1, "wrong call count\n");

  ul.QuadPart = 50001;
  hRet = pSHLWAPI_214(&streamobj.IStream_iface, &ul);
  ok(hRet == S_OK, "failed Stat()\n");
  ok(ul.QuadPart == 0, "213 didn't rewind stream\n");
}