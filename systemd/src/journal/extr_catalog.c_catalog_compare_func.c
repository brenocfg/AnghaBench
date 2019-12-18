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
struct TYPE_5__ {int /*<<< orphan*/ * bytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  language; TYPE_1__ id; } ;
typedef  TYPE_2__ CatalogItem ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ELEMENTSOF (int /*<<< orphan*/ *) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int catalog_compare_func(const CatalogItem *a, const CatalogItem *b) {
        unsigned k;
        int r;

        for (k = 0; k < ELEMENTSOF(b->id.bytes); k++) {
                r = CMP(a->id.bytes[k], b->id.bytes[k]);
                if (r != 0)
                        return r;
        }

        return strcmp(a->language, b->language);
}