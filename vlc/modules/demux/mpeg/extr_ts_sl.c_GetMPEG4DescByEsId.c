#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {int i_size; TYPE_5__** p_elems; } ;
struct TYPE_11__ {TYPE_2__ objects; } ;
struct TYPE_12__ {TYPE_3__ od; TYPE_1__* iod; } ;
typedef  TYPE_4__ ts_pmt_t ;
struct TYPE_13__ {TYPE_6__* es_descr; } ;
typedef  TYPE_5__ od_descriptor_t ;
struct TYPE_14__ {scalar_t__ i_es_id; scalar_t__ b_ok; } ;
typedef  TYPE_6__ es_mpeg4_descriptor_t ;
struct TYPE_9__ {TYPE_6__* es_descr; } ;

/* Variables and functions */
 int ES_DESCRIPTOR_COUNT ; 

const es_mpeg4_descriptor_t * GetMPEG4DescByEsId( const ts_pmt_t *pmt, uint16_t i_es_id )
{
    for( int i = 0; i < ES_DESCRIPTOR_COUNT; i++ )
    {
        const es_mpeg4_descriptor_t *es_descr = &pmt->iod->es_descr[i];
        if( es_descr->i_es_id == i_es_id && es_descr->b_ok )
            return es_descr;
    }
    for( int i=0; i<pmt->od.objects.i_size; i++ )
    {
        const od_descriptor_t *od = pmt->od.objects.p_elems[i];
        for( int j = 0; j < ES_DESCRIPTOR_COUNT; j++ )
        {
            const es_mpeg4_descriptor_t *es_descr = &od->es_descr[j];
            if( es_descr->i_es_id == i_es_id && es_descr->b_ok )
                return es_descr;
        }
    }
    return NULL;
}