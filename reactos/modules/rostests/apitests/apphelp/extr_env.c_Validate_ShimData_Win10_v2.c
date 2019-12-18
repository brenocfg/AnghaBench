#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {size_t dwLayerCount; scalar_t__* atrLayers; } ;
struct TYPE_4__ {scalar_t__ dwMagic; int dwSize; TYPE_1__ Query; } ;
typedef  TYPE_2__ ShimData_Win10_v2 ;
typedef  scalar_t__ PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  GetEnvironmentVariableA (char*,char*,int /*<<< orphan*/ ) ; 
 size_t SDB_MAX_LAYERS ; 
 scalar_t__ SHIMDATA_MAGIC ; 
 int /*<<< orphan*/  ValidateShim (scalar_t__,char const*) ; 
 int /*<<< orphan*/  _countof (char*) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void Validate_ShimData_Win10_v2(PVOID data, WCHAR szApphelp[256], size_t count, const char* layers[])
{
    size_t n;
    ShimData_Win10_v2* pShimData = (ShimData_Win10_v2*)data;

    if (pShimData->dwMagic != SHIMDATA_MAGIC)
    {
        skip("Yet another unknown shimdata variant...\n");
        return;
    }

    ok(pShimData->dwSize == sizeof(ShimData_Win10_v2), "Expected pShimData->dwSize to be %u, was %u\n",
       sizeof(ShimData_Win10_v2), pShimData->dwSize);
    if (pShimData->Query.dwLayerCount != min(count, SDB_MAX_LAYERS))
    {
        char buf[250] = {0};
        GetEnvironmentVariableA("__COMPAT_LAYER", buf, _countof(buf));
        trace("At test: %s\n", buf);
    }
    ok(pShimData->Query.dwLayerCount == min(count, SDB_MAX_LAYERS),
       "Expected LayerCount to be %u, was %u\n", min(count, SDB_MAX_LAYERS), pShimData->Query.dwLayerCount);
    for (n = 0; n < SDB_MAX_LAYERS; ++n)
    {
        if (n < count)
        {
            ok(pShimData->Query.atrLayers[n] != 0, "Expected to find a valid layer in index %u / %u\n", n, count);
            ValidateShim(pShimData->Query.atrLayers[n], layers[n]);
        }
        else
            ok(pShimData->Query.atrLayers[n] == 0, "Expected to find an empty layer in index %u / %u\n", n, count);
    }

}