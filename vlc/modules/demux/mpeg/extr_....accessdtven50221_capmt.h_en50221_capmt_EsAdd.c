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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int i_es_count; TYPE_2__* p_es; } ;
typedef  TYPE_1__ en50221_capmt_info_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_descriptors; scalar_t__ i_descriptors; int /*<<< orphan*/  i_stream_type; int /*<<< orphan*/  i_es_pid; } ;
typedef  TYPE_2__ en50221_capmt_es_info_t ;

/* Variables and functions */
 scalar_t__ likely (TYPE_2__*) ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 

__attribute__((used)) static inline en50221_capmt_es_info_t *en50221_capmt_EsAdd( en50221_capmt_info_t *p_en,
                                                            uint8_t i_stream_type,
                                                            uint16_t i_es_pid )
{
    en50221_capmt_es_info_t *p_realloc = realloc( p_en->p_es, sizeof(en50221_capmt_es_info_t) *
                                                              (p_en->i_es_count + 1) );
    if( likely(p_realloc) )
    {
        p_en->p_es = p_realloc;
        en50221_capmt_es_info_t *p_es = &p_en->p_es[ p_en->i_es_count++ ];
        p_es->i_es_pid = i_es_pid;
        p_es->i_stream_type = i_stream_type;
        p_es->i_descriptors = 0;
        p_es->p_descriptors = NULL;
        return p_es;
    }
    return NULL;
}