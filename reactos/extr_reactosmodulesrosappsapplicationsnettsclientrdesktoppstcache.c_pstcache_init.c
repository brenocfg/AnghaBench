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
typedef  size_t uint8 ;
struct TYPE_3__ {int* pstcache_fd; int pstcache_Bpp; int server_depth; scalar_t__ bitmap_cache_persist_enable; scalar_t__ bitmap_cache; scalar_t__ pstcache_enumerated; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  rd_close_file (int) ; 
 int /*<<< orphan*/  rd_lock_file (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rd_open_file (char*) ; 
 int /*<<< orphan*/  rd_pstcache_mkdir () ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t,int) ; 
 int /*<<< orphan*/  warning (char*) ; 

BOOL
pstcache_init(RDPCLIENT * This, uint8 cache_id)
{
	int fd;
	char filename[256];

	if (This->pstcache_enumerated)
		return True;

	This->pstcache_fd[cache_id] = 0;

	if (!(This->bitmap_cache && This->bitmap_cache_persist_enable))
		return False;

	if (!rd_pstcache_mkdir())
	{
		DEBUG(("failed to get/make cache directory!\n"));
		return False;
	}

	This->pstcache_Bpp = (This->server_depth + 7) / 8;
	sprintf(filename, "cache/pstcache_%d_%d", cache_id, This->pstcache_Bpp);
	DEBUG(("persistent bitmap cache file: %s\n", filename));

	fd = rd_open_file(filename);
	if (fd == -1)
		return False;

	if (!rd_lock_file(fd, 0, 0))
	{
		warning("Persistent bitmap caching is disabled. (The file is already in use)\n");
		rd_close_file(fd);
		return False;
	}

	This->pstcache_fd[cache_id] = fd;
	return True;
}