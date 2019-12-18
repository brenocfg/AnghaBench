#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_18__ {TYPE_5__* p_sdt; } ;
struct TYPE_17__ {int i_sdt; TYPE_5__** pp_sdt; } ;
struct TYPE_19__ {TYPE_2__ local; TYPE_1__ others; int /*<<< orphan*/ * p_obj; } ;
typedef  TYPE_3__ scan_session_t ;
struct TYPE_20__ {size_t i_service_name_length; int /*<<< orphan*/  i_service_type; int /*<<< orphan*/  i_service_name; } ;
typedef  TYPE_4__ dvbpsi_service_dr_t ;
struct TYPE_21__ {scalar_t__ i_table_id; scalar_t__ i_version; scalar_t__ b_current_next; TYPE_6__* p_first_service; int /*<<< orphan*/  i_network_id; int /*<<< orphan*/  i_extension; } ;
typedef  TYPE_5__ dvbpsi_sdt_t ;
struct TYPE_22__ {TYPE_7__* p_first_descriptor; int /*<<< orphan*/  b_free_ca; int /*<<< orphan*/  i_running_status; int /*<<< orphan*/  b_eit_present; int /*<<< orphan*/  b_eit_schedule; int /*<<< orphan*/  i_service_id; struct TYPE_22__* p_next; } ;
typedef  TYPE_6__ dvbpsi_sdt_service_t ;
struct TYPE_23__ {int i_tag; struct TYPE_23__* p_next; } ;
typedef  TYPE_7__ dvbpsi_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetOtherTsSDT (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__***) ; 
 scalar_t__ SDT_CURRENT_TS_TABLE_ID ; 
 scalar_t__ SDT_OTHER_TS_TABLE_ID ; 
 TYPE_4__* dvbpsi_DecodeServiceDr (TYPE_7__*) ; 
 int /*<<< orphan*/  dvbpsi_sdt_delete (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_5__** realloc (TYPE_5__**,int) ; 

__attribute__((used)) static void SDTCallBack( scan_session_t *p_session, dvbpsi_sdt_t *p_sdt )
{
    vlc_object_t *p_obj = p_session->p_obj;
    dvbpsi_sdt_t **pp_stored_sdt = NULL;
    if( p_sdt->i_table_id == SDT_OTHER_TS_TABLE_ID )
    {
        if( !GetOtherTsSDT( p_session, p_sdt->i_extension, &pp_stored_sdt ) )
        {
            dvbpsi_sdt_t **pp_realloc = realloc( p_session->others.pp_sdt,
                                                (p_session->others.i_sdt + 1) * sizeof( *pp_realloc ) );
            if( !pp_realloc ) /* oom */
            {
                dvbpsi_sdt_delete( p_sdt );
                return;
            }
            pp_stored_sdt = &pp_realloc[p_session->others.i_sdt];
            p_session->others.pp_sdt = pp_realloc;
            p_session->others.i_sdt++;
        }
    }
    else /* SDT_CURRENT_TS_TABLE_ID */
    {
        pp_stored_sdt = &p_session->local.p_sdt;
    }

    /* Store, replace, or discard */
    if( *pp_stored_sdt )
    {
        if( (*pp_stored_sdt)->i_version == p_sdt->i_version ||
            (*pp_stored_sdt)->b_current_next > p_sdt->b_current_next )
        {
            /* Duplicate or stored one isn't current */
            dvbpsi_sdt_delete( p_sdt );
            return;
        }
        dvbpsi_sdt_delete( *pp_stored_sdt );
    }
    *pp_stored_sdt = p_sdt;

    /* */
    msg_Dbg( p_obj, "new SDT %s ts_id=%d version=%d current_next=%d network_id=%d",
             ( p_sdt->i_table_id == SDT_CURRENT_TS_TABLE_ID ) ? "local" : "other",
             p_sdt->i_extension, p_sdt->i_version, p_sdt->b_current_next,
             p_sdt->i_network_id );

    dvbpsi_sdt_service_t *p_srv;
    for( p_srv = p_sdt->p_first_service; p_srv; p_srv = p_srv->p_next )
    {
        dvbpsi_descriptor_t *p_dr;

        msg_Dbg( p_obj, "  * service id=%d eit schedule=%d present=%d running=%d free_ca=%d",
                 p_srv->i_service_id, p_srv->b_eit_schedule,
                 p_srv->b_eit_present, p_srv->i_running_status,
                 p_srv->b_free_ca );
        for( p_dr = p_srv->p_first_descriptor; p_dr; p_dr = p_dr->p_next )
        {
            if( p_dr->i_tag == 0x48 )
            {
                dvbpsi_service_dr_t *pD = dvbpsi_DecodeServiceDr( p_dr );
                if( pD )
                {
                    char str2[257];

                    memcpy( str2, pD->i_service_name, pD->i_service_name_length );
                    str2[pD->i_service_name_length] = '\0';

                    msg_Dbg( p_obj, "    - type=%d name=%s",
                             pD->i_service_type, str2 );
                }
            }
            else
            {
                msg_Dbg( p_obj, "    * dsc 0x%x", p_dr->i_tag );
            }
        }
    }
}