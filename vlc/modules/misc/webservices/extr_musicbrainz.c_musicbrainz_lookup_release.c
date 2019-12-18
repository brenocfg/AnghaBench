#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ root; } ;
typedef  TYPE_1__ musicbrainz_lookup_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  json_value_free (scalar_t__) ; 

__attribute__((used)) static void musicbrainz_lookup_release(musicbrainz_lookup_t *p)
{
    if(p && p->root)
        json_value_free(p->root);
    free(p);
}