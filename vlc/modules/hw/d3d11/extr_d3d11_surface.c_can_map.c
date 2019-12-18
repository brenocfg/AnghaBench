#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  staging_resource; } ;
typedef  TYPE_1__ filter_sys_t ;
typedef  int /*<<< orphan*/  ID3D11DeviceContext ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3D11_MAPPED_SUBRESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_MAP_READ ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT can_map(filter_sys_t *sys, ID3D11DeviceContext *context)
{
    D3D11_MAPPED_SUBRESOURCE lock;
    HRESULT hr = ID3D11DeviceContext_Map(context, sys->staging_resource, 0,
                                         D3D11_MAP_READ, 0, &lock);
    ID3D11DeviceContext_Unmap(context, sys->staging_resource, 0);
    return hr;
}