#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_11__ {scalar_t__ type; int i_bitmap; TYPE_5__** pp_es; } ;
struct TYPE_9__ {int i_id; } ;
struct TYPE_12__ {TYPE_3__ cc; TYPE_1__ fmt; } ;
typedef  TYPE_4__ es_out_id_t ;
struct TYPE_10__ {int const i_id; } ;
struct TYPE_13__ {TYPE_2__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EsOutDelLocked (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_4__* EsOutGetSelectedCat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EsOutSendEsEvent (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VLC_INPUT_ES_UNSELECTED ; 

__attribute__((used)) static void EsDeleteCCChannels( es_out_t *out, es_out_id_t *parent )
{
    if( parent->cc.type == 0 )
        return;

    es_out_id_t *spu_es = EsOutGetSelectedCat( out, SPU_ES );
    const int i_spu_id = spu_es ? spu_es->fmt.i_id : -1;

    uint64_t i_bitmap = parent->cc.i_bitmap;
    for( int i = 0; i_bitmap > 0; i++, i_bitmap >>= 1 )
    {
        if( (i_bitmap & 1) == 0 || !parent->cc.pp_es[i] )
            continue;

        if( i_spu_id == parent->cc.pp_es[i]->fmt.i_id )
        {
            /* Force unselection of the CC */
            EsOutSendEsEvent(out, parent->cc.pp_es[i], VLC_INPUT_ES_UNSELECTED);
        }
        EsOutDelLocked( out, parent->cc.pp_es[i] );
    }

    parent->cc.i_bitmap = 0;
    parent->cc.type = 0;
}