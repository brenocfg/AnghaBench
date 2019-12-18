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
struct siphash {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * language; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ CatalogItem ;

/* Variables and functions */
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ *,int,struct siphash*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void catalog_hash_func(const CatalogItem *i, struct siphash *state) {
        siphash24_compress(&i->id, sizeof(i->id), state);
        siphash24_compress(i->language, strlen(i->language), state);
}