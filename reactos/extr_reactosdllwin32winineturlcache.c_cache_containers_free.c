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
 int /*<<< orphan*/  LIST_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UrlContainers ; 
 int /*<<< orphan*/  cache_container ; 
 int /*<<< orphan*/  cache_container_delete_container (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_containers_free(void)
{
    while(!list_empty(&UrlContainers))
        cache_container_delete_container(
            LIST_ENTRY(list_head(&UrlContainers), cache_container, entry)
        );
}