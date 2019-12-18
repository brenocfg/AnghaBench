#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i_id; scalar_t__ p_meta; } ;
typedef  TYPE_1__ es_out_pgrm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ vlc_meta_Get (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Title ; 

__attribute__((used)) static char *EsOutProgramGetMetaName( es_out_pgrm_t *p_pgrm )
{
    char *psz = NULL;
    if( p_pgrm->p_meta && vlc_meta_Get( p_pgrm->p_meta, vlc_meta_Title ) )
    {
        if( asprintf( &psz, _("%s [%s %d]"), vlc_meta_Get( p_pgrm->p_meta, vlc_meta_Title ),
                      _("Program"), p_pgrm->i_id ) == -1 )
            return NULL;
    }
    else
    {
        if( asprintf( &psz, "%s %d", _("Program"), p_pgrm->i_id ) == -1 )
            return NULL;
    }
    return psz;
}