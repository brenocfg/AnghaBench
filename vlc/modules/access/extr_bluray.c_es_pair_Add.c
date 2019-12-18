#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_array_t ;
struct TYPE_8__ {int b_recyling; int b_restart_decoders_on_reuse; int /*<<< orphan*/  fmt; scalar_t__ i_next_block_flags; int /*<<< orphan*/ * p_es; } ;
typedef  TYPE_1__ es_pair_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ vlc_array_append (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool es_pair_Add(vlc_array_t *p_array, const es_format_t *p_fmt,
                        es_out_id_t *p_es)
{
    es_pair_t *p_pair = malloc(sizeof(*p_pair));
    if (likely(p_pair != NULL))
    {
        p_pair->p_es = p_es;
        p_pair->i_next_block_flags = 0;
        p_pair->b_recyling = false;
        p_pair->b_restart_decoders_on_reuse = true;
        if(vlc_array_append(p_array, p_pair) != VLC_SUCCESS)
        {
            free(p_pair);
            p_pair = NULL;
        }
        else
        {
            es_format_Init(&p_pair->fmt, p_fmt->i_cat, p_fmt->i_codec);
            es_format_Copy(&p_pair->fmt, p_fmt);
        }
    }
    return p_pair != NULL;
}