#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_5__ {size_t sh_hashlen; TYPE_2__** sh_hash; } ;
typedef  TYPE_1__ fmd_serd_hash_t ;
struct TYPE_6__ {int /*<<< orphan*/  sg_name; struct TYPE_6__* sg_next; } ;
typedef  TYPE_2__ fmd_serd_eng_t ;

/* Variables and functions */
 size_t fmd_strhash (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

fmd_serd_eng_t *
fmd_serd_eng_lookup(fmd_serd_hash_t *shp, const char *name)
{
	uint_t h = fmd_strhash(name) % shp->sh_hashlen;
	fmd_serd_eng_t *sgp;

	for (sgp = shp->sh_hash[h]; sgp != NULL; sgp = sgp->sg_next) {
		if (strcmp(name, sgp->sg_name) == 0)
			return (sgp);
	}

	return (NULL);
}