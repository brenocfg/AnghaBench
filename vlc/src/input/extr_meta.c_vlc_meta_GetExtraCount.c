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
struct TYPE_3__ {int /*<<< orphan*/  extra_tags; } ;
typedef  TYPE_1__ vlc_meta_t ;

/* Variables and functions */
 int vlc_dictionary_keys_count (int /*<<< orphan*/ *) ; 

unsigned vlc_meta_GetExtraCount( const vlc_meta_t *m )
{
    return vlc_dictionary_keys_count(&m->extra_tags);
}