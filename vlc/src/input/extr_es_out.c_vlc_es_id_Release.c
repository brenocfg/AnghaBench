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
typedef  int /*<<< orphan*/  vlc_es_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  EsRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_es_id_get_out (int /*<<< orphan*/ *) ; 

void
vlc_es_id_Release(vlc_es_id_t *id)
{
    EsRelease(vlc_es_id_get_out(id));
}