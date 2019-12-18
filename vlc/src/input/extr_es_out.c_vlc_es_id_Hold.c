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
 int /*<<< orphan*/  EsHold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_es_id_get_out (int /*<<< orphan*/ *) ; 

vlc_es_id_t *
vlc_es_id_Hold(vlc_es_id_t *id)
{
    EsHold(vlc_es_id_get_out(id));
    return id;
}