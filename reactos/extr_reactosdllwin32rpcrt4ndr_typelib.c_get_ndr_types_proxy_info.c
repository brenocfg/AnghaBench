#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__** pProxyVtblList; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* pStublessProxyInfo; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  MIDL_STUBLESS_PROXY_INFO ;

/* Variables and functions */
 TYPE_3__ ndr_types_ProxyFileInfo ; 

__attribute__((used)) static const MIDL_STUBLESS_PROXY_INFO *get_ndr_types_proxy_info(void)
{
    return ndr_types_ProxyFileInfo.pProxyVtblList[0]->header.pStublessProxyInfo;
}