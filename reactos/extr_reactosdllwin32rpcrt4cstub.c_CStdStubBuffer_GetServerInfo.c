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
struct TYPE_2__ {int /*<<< orphan*/  const* pServerInfo; } ;
typedef  int /*<<< orphan*/  MIDL_SERVER_INFO ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  CStdStubBuffer ;

/* Variables and functions */
 TYPE_1__ STUB_HEADER (int /*<<< orphan*/ *) ; 

const MIDL_SERVER_INFO *CStdStubBuffer_GetServerInfo(IRpcStubBuffer *iface)
{
  CStdStubBuffer *This = (CStdStubBuffer *)iface;
  return STUB_HEADER(This).pServerInfo;
}