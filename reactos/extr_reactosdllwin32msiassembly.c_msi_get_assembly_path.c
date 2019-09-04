#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int cbAssemblyInfo; int cchBuf; int /*<<< orphan*/ * pszCurrentAssemblyPathBuf; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** cache_net; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  IAssemblyCache ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ ASSEMBLY_INFO ;

/* Variables and functions */
 size_t CLR_VERSION_V40 ; 
 scalar_t__ E_NOT_SUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IAssemblyCache_QueryAssemblyInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 

WCHAR *msi_get_assembly_path( MSIPACKAGE *package, const WCHAR *displayname )
{
    HRESULT hr;
    ASSEMBLY_INFO info;
    IAssemblyCache *cache = package->cache_net[CLR_VERSION_V40];

    if (!cache) return NULL;

    memset( &info, 0, sizeof(info) );
    info.cbAssemblyInfo = sizeof(info);
    hr = IAssemblyCache_QueryAssemblyInfo( cache, 0, displayname, &info );
    if (hr != E_NOT_SUFFICIENT_BUFFER) return NULL;

    if (!(info.pszCurrentAssemblyPathBuf = msi_alloc( info.cchBuf * sizeof(WCHAR) ))) return NULL;

    hr = IAssemblyCache_QueryAssemblyInfo( cache, 0, displayname, &info );
    if (FAILED( hr ))
    {
        msi_free( info.pszCurrentAssemblyPathBuf );
        return NULL;
    }
    TRACE("returning %s\n", debugstr_w(info.pszCurrentAssemblyPathBuf));
    return info.pszCurrentAssemblyPathBuf;
}