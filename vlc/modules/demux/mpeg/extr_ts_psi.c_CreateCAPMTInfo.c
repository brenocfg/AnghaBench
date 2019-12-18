#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  en50221_capmt_info_t ;
typedef  int /*<<< orphan*/  en50221_capmt_es_info_t ;
struct TYPE_5__ {TYPE_2__* p_first_es; TYPE_3__* p_first_descriptor; int /*<<< orphan*/  i_program_number; int /*<<< orphan*/  i_version; } ;
typedef  TYPE_1__ dvbpsi_pmt_t ;
struct TYPE_6__ {TYPE_3__* p_first_descriptor; int /*<<< orphan*/  i_pid; int /*<<< orphan*/  i_type; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ dvbpsi_pmt_es_t ;
struct TYPE_7__ {int i_tag; int /*<<< orphan*/  i_length; int /*<<< orphan*/  p_data; struct TYPE_7__* p_next; } ;
typedef  TYPE_3__ dvbpsi_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  en50221_capmt_AddCADescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en50221_capmt_AddESCADescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * en50221_capmt_EsAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * en50221_capmt_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static en50221_capmt_info_t * CreateCAPMTInfo( const dvbpsi_pmt_t *p_pmt )
{
    en50221_capmt_info_t *p_en = en50221_capmt_New( p_pmt->i_version,
                                                    p_pmt->i_program_number );
    if( unlikely(p_en == NULL) )
        return p_en;

    for( const dvbpsi_descriptor_t *p_dr = p_pmt->p_first_descriptor;
                                           p_dr; p_dr = p_dr->p_next )
    {
        if( p_dr->i_tag == 0x09 )
            en50221_capmt_AddCADescriptor( p_en, p_dr->p_data, p_dr->i_length );
    }

    for( const dvbpsi_pmt_es_t *p_es = p_pmt->p_first_es;
                                       p_es; p_es = p_es->p_next )
    {
        en50221_capmt_es_info_t *p_enes = en50221_capmt_EsAdd( p_en,
                                                               p_es->i_type,
                                                               p_es->i_pid );
        if( likely(p_enes) )
        {
            for( const dvbpsi_descriptor_t *p_dr = p_es->p_first_descriptor;
                                                   p_dr; p_dr = p_dr->p_next )
            {
                if( p_dr->i_tag == 0x09 )
                    en50221_capmt_AddESCADescriptor( p_enes, p_dr->p_data, p_dr->i_length );
            }
        }
    }

    return p_en;
}