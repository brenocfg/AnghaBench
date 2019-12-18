#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int mediac; int i_attributes; struct TYPE_5__* pp_attributes; struct TYPE_5__* mediav; struct TYPE_5__* fmt; struct TYPE_5__* psz_uri; struct TYPE_5__* psz_sessioninfo; struct TYPE_5__* psz_sessionname; } ;
typedef  TYPE_1__ sdp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeAttribute (TYPE_1__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void FreeSDP( sdp_t *p_sdp )
{
    free( p_sdp->psz_sessionname );
    free( p_sdp->psz_sessioninfo );
    free( p_sdp->psz_uri );

    for (unsigned j = 0; j < p_sdp->mediac; j++)
    {
        free (p_sdp->mediav[j].fmt);
        for (int i = 0; i < p_sdp->mediav[j].i_attributes; i++)
            FreeAttribute (p_sdp->mediav[j].pp_attributes[i]);
        free (p_sdp->mediav[j].pp_attributes);
    }
    free (p_sdp->mediav);

    for (int i = 0; i < p_sdp->i_attributes; i++)
        FreeAttribute (p_sdp->pp_attributes[i]);

    free (p_sdp->pp_attributes);
    free (p_sdp);
}