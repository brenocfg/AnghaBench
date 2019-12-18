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
struct dummystream {scalar_t__ readcalls; int writecalls; scalar_t__ seekcalls; int /*<<< orphan*/  IStream_iface; } ;
typedef  int /*<<< orphan*/  buff ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  InitDummyStream (struct dummystream*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pSHLWAPI_212 (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void test_SHLWAPI_212(void)
{
  struct dummystream streamobj;
  char buff[256];
  HRESULT hRet;

  if (!pSHLWAPI_212)
    return;

  InitDummyStream(&streamobj);
  hRet = pSHLWAPI_212(&streamobj.IStream_iface, buff, sizeof(buff));

  ok(hRet == S_OK, "failed Write()\n");
  ok(streamobj.readcalls == 0, "called Read()\n");
  ok(streamobj.writecalls == 1, "wrong call count\n");
  ok(streamobj.seekcalls == 0, "called Seek()\n");
}