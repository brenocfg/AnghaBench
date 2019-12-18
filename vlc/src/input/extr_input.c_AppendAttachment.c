#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const input_attachment_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/  const**) ; 
 scalar_t__ likely (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void AppendAttachment( int *pi_attachment, input_attachment_t ***ppp_attachment,
                              const demux_t ***ppp_attachment_demux,
                              int i_new, input_attachment_t **pp_new, const demux_t *p_demux )
{
    int i_attachment = *pi_attachment;
    int i;

    input_attachment_t **pp_att = realloc( *ppp_attachment,
                    sizeof(*pp_att) * ( i_attachment + i_new ) );
    if( likely(pp_att) )
    {
        *ppp_attachment = pp_att;
        const demux_t **pp_attdmx = realloc( *ppp_attachment_demux,
                        sizeof(*pp_attdmx) * ( i_attachment + i_new ) );
        if( likely(pp_attdmx) )
        {
            *ppp_attachment_demux = pp_attdmx;

            for( i = 0; i < i_new; i++ )
            {
                pp_att[i_attachment] = pp_new[i];
                pp_attdmx[i_attachment++] = p_demux;
            }
            /* */
            *pi_attachment = i_attachment;
            free( pp_new );
            return;
        }
    }

    /* on alloc errors */
    for( i = 0; i < i_new; i++ )
        vlc_input_attachment_Delete( pp_new[i] );
    free( pp_new );
}