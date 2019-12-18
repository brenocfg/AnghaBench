#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_number; } ;
typedef  TYPE_2__ ts_pmt_t ;
struct TYPE_8__ {scalar_t__ i_service_id; scalar_t__ i_format; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_group; } ;
struct TYPE_10__ {int b_interlaced; TYPE_1__ metadata; TYPE_7__ fmt; int /*<<< orphan*/ * p_next; int /*<<< orphan*/ * p_extraes; scalar_t__ i_next_block_flags; scalar_t__ i_sl_es_id; int /*<<< orphan*/ * id; TYPE_2__* p_program; } ;
typedef  TYPE_3__ ts_es_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  es_format_Init (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int) ; 

ts_es_t * ts_es_New( ts_pmt_t *p_program )
{
    ts_es_t *p_es = malloc( sizeof(*p_es) );
    if( p_es )
    {
        p_es->p_program = p_program;
        p_es->id = NULL;
        p_es->i_sl_es_id = 0;
        p_es->i_next_block_flags = 0;
        p_es->p_extraes = NULL;
        p_es->p_next = NULL;
        p_es->b_interlaced = false;
        es_format_Init( &p_es->fmt, UNKNOWN_ES, 0 );
        p_es->fmt.i_group = p_program->i_number;
        p_es->metadata.i_format = 0;
        p_es->metadata.i_service_id = 0;
    }
    return p_es;
}