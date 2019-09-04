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
typedef  int /*<<< orphan*/  urlcache_header ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ cache_container ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL cache_container_unlock_index(cache_container *pContainer, urlcache_header *pHeader)
{
    /* release mutex */
    ReleaseMutex(pContainer->mutex);
    return UnmapViewOfFile(pHeader);
}