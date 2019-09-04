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
struct dummystream {int readcalls; scalar_t__ writecalls; scalar_t__ seekcalls; int /*<<< orphan*/  IStream_iface; } ;
typedef  int /*<<< orphan*/  buff ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  InitDummyStream (struct dummystream*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pSHLWAPI_184 (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void test_SHLWAPI_184(void)
{
  struct dummystream streamobj;
  char buff[256];
  HRESULT hRet;

  if (!pSHLWAPI_184)
    return;

  InitDummyStream(&streamobj);
  hRet = pSHLWAPI_184(&streamobj.IStream_iface, buff, sizeof(buff));

  ok(hRet == S_OK, "failed Read()\n");
  ok(streamobj.readcalls == 1, "wrong call count\n");
  ok(streamobj.writecalls == 0, "called Write()\n");
  ok(streamobj.seekcalls == 0, "called Seek()\n");
}