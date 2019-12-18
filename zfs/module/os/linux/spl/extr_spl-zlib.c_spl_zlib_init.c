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

/* Variables and functions */
 int /*<<< orphan*/  KMC_KVMEM ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_MEM_LEVEL ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_deflate_workspacesize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 
 int /*<<< orphan*/  zlib_workspace_cache ; 

int
spl_zlib_init(void)
{
	int size;

	size = MAX(zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL),
	    zlib_inflate_workspacesize());

	zlib_workspace_cache = kmem_cache_create(
	    "spl_zlib_workspace_cache",
	    size, 0, NULL, NULL, NULL, NULL, NULL,
	    KMC_KVMEM);
	if (!zlib_workspace_cache)
		return (1);

	return (0);
}