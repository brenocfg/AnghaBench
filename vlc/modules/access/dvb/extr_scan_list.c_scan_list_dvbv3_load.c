#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ delivery; int /*<<< orphan*/  inner_fec; void* i_rate; int /*<<< orphan*/  polarization; void* i_freq; } ;
typedef  TYPE_1__ scan_list_entry_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SCAN_DELIVERY_DVB_S ; 
 scalar_t__ SCAN_DELIVERY_DVB_S2 ; 
 int /*<<< orphan*/  SCAN_POLARIZATION_HORIZONTAL ; 
 int /*<<< orphan*/  SCAN_POLARIZATION_VERTICAL ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_1__* scan_list_entry_New () ; 
 scalar_t__ scan_list_entry_add (TYPE_1__***,TYPE_1__*) ; 
 int /*<<< orphan*/  scan_list_parse_fec (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok_r (char*,char const*,char**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char*) ; 

scan_list_entry_t * scan_list_dvbv3_load( vlc_object_t *p_obj, const char *psz_source, size_t *pi_count )
{
    FILE *p_file = vlc_fopen( psz_source, "r" );
    if( !p_file )
    {
        msg_Err( p_obj, "failed to open satellite file (%s)", psz_source );
        return NULL;
    }

    scan_list_entry_t *p_list = NULL;
    scan_list_entry_t **pp_list_last = &p_list;
    scan_list_entry_t *p_entry = NULL;
    *pi_count = 0;

    const char *psz_delims = " \t";

    char *psz_line = NULL;
    size_t i_len = 0;
    ssize_t i_read;

    while ( (i_read = getline( &psz_line, &i_len, p_file )) != -1 )
    {
        char *psz_token;
        char *p_save = NULL;

        if( p_entry && scan_list_entry_add( &pp_list_last, p_entry ) )
            (*pi_count)++;

        p_entry = scan_list_entry_New();
        if( unlikely(p_entry == NULL) )
            continue;

        /* DELIVERY */
        if( !(psz_token = strtok_r( psz_line, psz_delims, &p_save )) )
            continue;

        if( !strcmp( psz_token, "S" ) )
        {
            p_entry->delivery = SCAN_DELIVERY_DVB_S;
        }
        else if( !strcmp( psz_token, "S2" ) )
        {
            p_entry->delivery = SCAN_DELIVERY_DVB_S2;
        }

        /* Parse the delivery format */
        if( p_entry->delivery == SCAN_DELIVERY_DVB_S || p_entry->delivery == SCAN_DELIVERY_DVB_S2 )
        {
            /* FREQUENCY */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;
            p_entry->i_freq = atoi( psz_token );

            /* POLARIZATION */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;
            p_entry->polarization = !strcasecmp(psz_token, "H") ? SCAN_POLARIZATION_HORIZONTAL
                                                                : SCAN_POLARIZATION_VERTICAL;

            /* RATE */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;
            p_entry->i_rate = atoi( psz_token );

            /* FEC */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;
            p_entry->inner_fec = scan_list_parse_fec( psz_token );

            /* INVERSION */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;

            /* MODULATION */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;

            /* STREAM_ID */
            if( !(psz_token = strtok_r( NULL, psz_delims, &p_save )) )
                continue;
        }

    }

    if( p_entry && scan_list_entry_add( &pp_list_last, p_entry ) )
        (*pi_count)++;

    fclose( p_file );

    return p_list;
}