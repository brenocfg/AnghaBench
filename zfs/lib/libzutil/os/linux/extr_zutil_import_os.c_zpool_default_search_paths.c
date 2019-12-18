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
 size_t DEFAULT_IMPORT_PATH_SIZE ; 
 scalar_t__ zpool_default_import_path ; 

const char * const *
zpool_default_search_paths(size_t *count)
{
	*count = DEFAULT_IMPORT_PATH_SIZE;
	return ((const char * const *)zpool_default_import_path);
}