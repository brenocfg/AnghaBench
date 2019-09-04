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
struct TYPE_2__ {int /*<<< orphan*/  ICLRMetaHost_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 TYPE_1__ GlobalCLRMetaHost ; 
 int /*<<< orphan*/  ICLRMetaHost_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 

HRESULT CLRMetaHost_CreateInstance(REFIID riid, void **ppobj)
{
    return ICLRMetaHost_QueryInterface(&GlobalCLRMetaHost.ICLRMetaHost_iface, riid, ppobj);
}