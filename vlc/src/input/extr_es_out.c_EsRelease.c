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
struct TYPE_4__ {int /*<<< orphan*/  fmt; struct TYPE_4__* psz_language_code; struct TYPE_4__* psz_language; struct TYPE_4__* psz_title; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void EsRelease(es_out_id_t *es)
{
    if (vlc_atomic_rc_dec(&es->rc))
    {
        free(es->psz_title);
        free(es->psz_language);
        free(es->psz_language_code);
        es_format_Clean(&es->fmt);
        free(es);
    }
}