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
struct TYPE_3__ {scalar_t__ sh_count; int /*<<< orphan*/  sh_hashlen; int /*<<< orphan*/  sh_hash; } ;
typedef  TYPE_1__ fmd_serd_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_STR_BUCKETS ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 

void
fmd_serd_hash_create(fmd_serd_hash_t *shp)
{
	shp->sh_hashlen = FMD_STR_BUCKETS;
	shp->sh_hash = calloc(shp->sh_hashlen, sizeof (void *));
	shp->sh_count = 0;
}