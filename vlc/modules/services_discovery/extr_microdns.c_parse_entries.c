#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct srv {struct srv* psz_device_name; int /*<<< orphan*/  i_renderer_flags; int /*<<< orphan*/  psz_protocol; int /*<<< orphan*/  i_port; } ;
struct TYPE_8__ {char* addr_str; } ;
struct TYPE_7__ {char* addr_str; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_9__ {struct rr_data_txt* TXT; TYPE_3__ AAAA; TYPE_2__ A; TYPE_1__ SRV; } ;
struct rr_entry {scalar_t__ type; TYPE_4__ data; int /*<<< orphan*/  name; struct rr_entry* next; } ;
struct rr_data_txt {scalar_t__ txt; struct rr_data_txt* next; } ;
struct TYPE_10__ {int b_renderer; int /*<<< orphan*/  i_renderer_flags; int /*<<< orphan*/  psz_protocol; int /*<<< orphan*/  psz_service_name; } ;

/* Variables and functions */
 unsigned int NB_PROTOCOLS ; 
 scalar_t__ RR_A ; 
 scalar_t__ RR_AAAA ; 
 scalar_t__ RR_SRV ; 
 scalar_t__ RR_TXT ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_RENDERER_CAN_AUDIO ; 
 int /*<<< orphan*/  VLC_RENDERER_CAN_VIDEO ; 
 int VLC_SUCCESS ; 
 int atoi (scalar_t__) ; 
 struct srv* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  free (struct srv*) ; 
 TYPE_5__* protocols ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct srv* strdup (scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,scalar_t__,int) ; 
 struct srv* strndup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_entries( const struct rr_entry *p_entries, bool b_renderer,
               struct srv **pp_srvs, unsigned int *p_nb_srv,
               const char **ppsz_ip, bool *p_ipv6 )
{
    /* Count the number of servers */
    unsigned int i_nb_srv = 0;
    for( const struct rr_entry *p_entry = p_entries;
         p_entry != NULL; p_entry = p_entry->next )
    {
        if( p_entry->type == RR_SRV )
            i_nb_srv++;
    }
    if( i_nb_srv == 0 )
        return VLC_EGENERIC;

    struct srv *p_srvs = calloc(i_nb_srv, sizeof(struct srv));
    if( p_srvs == NULL )
        return VLC_EGENERIC;

    /* There is one ip for several srvs, fetch them */
    const char *psz_ip = NULL;
    struct srv *p_srv = NULL;
    i_nb_srv = 0;
    for( const struct rr_entry *p_entry = p_entries;
         p_entry != NULL; p_entry = p_entry->next )
    {
        if( p_entry->type == RR_SRV )
        {
            for( unsigned i = 0; i < NB_PROTOCOLS; ++i )
            {
                if( !strrcmp( p_entry->name, protocols[i].psz_service_name ) &&
                    protocols[i].b_renderer == b_renderer )
                {
                    p_srv = &p_srvs[i_nb_srv];

                    p_srv->psz_device_name =
                        strndup( p_entry->name, strlen( p_entry->name )
                                 - strlen( protocols[i].psz_service_name ) - 1);
                    if( p_srv->psz_device_name == NULL )
                        break;
                    p_srv->psz_protocol = protocols[i].psz_protocol;
                    p_srv->i_port = p_entry->data.SRV.port;
                    p_srv->i_renderer_flags = protocols[i].i_renderer_flags;
                    ++i_nb_srv;
                    break;
                }
            }
        }
        else if( p_entry->type == RR_A && psz_ip == NULL )
            psz_ip = p_entry->data.A.addr_str;
        else if( p_entry->type == RR_AAAA && psz_ip == NULL )
        {
            psz_ip = p_entry->data.AAAA.addr_str;
            *p_ipv6 = true;
        }
        else if( p_entry->type == RR_TXT && p_srv != NULL )
        {
            for ( struct rr_data_txt *p_txt = p_entry->data.TXT;
                  p_txt != NULL ; p_txt = p_txt->next )
            {
                if( !strcmp( p_srv->psz_protocol, "chromecast" ) )
                {
                    if ( !strncmp( "fn=", p_txt->txt, 3 ) )
                    {
                        free( p_srv->psz_device_name );
                        p_srv->psz_device_name = strdup( p_txt->txt + 3 );
                    }
                    else if( !strncmp( "ca=", p_txt->txt, 3 ) )
                    {
                        int ca = atoi( p_txt->txt + 3);
                        /*
                         * For chromecast, the `ca=` is composed from (at least)
                         * 0x01 to indicate video support
                         * 0x04 to indivate audio support
                         */
                        if ( ( ca & 0x01 ) != 0 )
                            p_srv->i_renderer_flags |= VLC_RENDERER_CAN_VIDEO;
                        if ( ( ca & 0x04 ) != 0 )
                            p_srv->i_renderer_flags |= VLC_RENDERER_CAN_AUDIO;
                    }
                }
            }
        }
    }
    if( psz_ip == NULL || i_nb_srv == 0 )
    {
        for( unsigned int i = 0; i < i_nb_srv; ++i )
            free( p_srvs[i].psz_device_name );
        free( p_srvs );
        return VLC_EGENERIC;
    }

    *pp_srvs = p_srvs;
    *p_nb_srv = i_nb_srv;
    *ppsz_ip = psz_ip;
    return VLC_SUCCESS;
}