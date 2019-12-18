#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  scan_t ;
struct TYPE_19__ {int /*<<< orphan*/  type; void* psz_provider; void* psz_name; int /*<<< orphan*/  b_crypted; } ;
typedef  TYPE_1__ scan_service_t ;
struct TYPE_20__ {scalar_t__ i_sdt_version; } ;
typedef  TYPE_2__ scan_multiplex_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_service_type; int /*<<< orphan*/  i_service_provider_name_length; int /*<<< orphan*/  i_service_provider_name; int /*<<< orphan*/  i_service_name_length; int /*<<< orphan*/  i_service_name; } ;
typedef  TYPE_3__ dvbpsi_service_dr_t ;
struct TYPE_22__ {scalar_t__ i_version; TYPE_5__* p_first_service; int /*<<< orphan*/  i_extension; } ;
typedef  TYPE_4__ dvbpsi_sdt_t ;
struct TYPE_23__ {TYPE_6__* p_first_descriptor; int /*<<< orphan*/  b_free_ca; int /*<<< orphan*/  i_service_id; struct TYPE_23__* p_next; } ;
typedef  TYPE_5__ dvbpsi_sdt_service_t ;
struct TYPE_24__ {int i_tag; struct TYPE_24__* p_next; } ;
typedef  TYPE_6__ dvbpsi_descriptor_t ;

/* Variables and functions */
 scalar_t__ UINT8_MAX ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_3__* dvbpsi_DecodeServiceDr (TYPE_6__*) ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_2__* scan_FindMultiplex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_NotifyService (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  scan_SetMultiplexScanStatus (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  scan_multiplex_AddService (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* scan_multiplex_FindService (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_service_Delete (TYPE_1__*) ; 
 TYPE_1__* scan_service_New (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void* vlc_from_EIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ParseSDT( vlc_object_t *p_obj, scan_t *p_scan, const dvbpsi_sdt_t *p_sdt )
{
    VLC_UNUSED(p_obj);
    /* SDT must not create new service without proper config ( local )
       or it must has been created by another network NIT (providing freq).
       Guaranteed by parsing order( PAT, current ts SDT ) or ( NIT, SDT ) */
    scan_multiplex_t *p_mplex = scan_FindMultiplex( p_scan, p_sdt->i_extension );
    if( unlikely(p_mplex == NULL) )
        return ;

    scan_SetMultiplexScanStatus( p_scan, p_mplex, true );

    if( p_mplex->i_sdt_version == UINT8_MAX )
        p_mplex->i_sdt_version = p_sdt->i_version;

    for( const dvbpsi_sdt_service_t *p_srv = p_sdt->p_first_service;
                                     p_srv; p_srv = p_srv->p_next )
    {
        bool b_newservice = false;
        scan_service_t *s = scan_multiplex_FindService( p_mplex, p_srv->i_service_id );
        if( s == NULL )
        {
            b_newservice = true;
            s = scan_service_New( p_srv->i_service_id );
            if( unlikely(s == NULL) )
                continue;
            if( !scan_multiplex_AddService( p_mplex, s ) )
            {
                scan_service_Delete( s );
                continue;
            }
        }

        s->b_crypted = p_srv->b_free_ca;

        for( dvbpsi_descriptor_t *p_dr = p_srv->p_first_descriptor;
                                  p_dr; p_dr = p_dr->p_next )
        {
            if( p_dr->i_tag != 0x48 )
                continue;

            dvbpsi_service_dr_t *pD = dvbpsi_DecodeServiceDr( p_dr );
            if( pD )
            {
                if( !s->psz_name )
                    s->psz_name = vlc_from_EIT( pD->i_service_name,
                                                pD->i_service_name_length );
                free( s->psz_provider );
                s->psz_provider = vlc_from_EIT( pD->i_service_provider_name,
                                                pD->i_service_provider_name_length );

                s->type = pD->i_service_type;
            }
        }

        scan_NotifyService( p_scan, s, !b_newservice );
    }
}