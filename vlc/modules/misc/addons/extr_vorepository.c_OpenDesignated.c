#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  pf_retrieve; int /*<<< orphan*/  pf_find; scalar_t__ psz_uri; } ;
typedef  TYPE_1__ addons_finder_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindDesignated ; 
 int /*<<< orphan*/  Retrieve ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ strlen (scalar_t__) ; 
 scalar_t__ strncmp (char*,scalar_t__,int) ; 

__attribute__((used)) static int OpenDesignated(vlc_object_t *p_this)
{
    addons_finder_t *p_finder = (addons_finder_t*) p_this;
    if ( !p_finder->psz_uri
         || strncmp( "file://", p_finder->psz_uri, 7 )
         || strncmp( ".vlp", p_finder->psz_uri + strlen( p_finder->psz_uri ) - 4, 4 )
       )
        return VLC_EGENERIC;

    p_finder->pf_find = FindDesignated;
    p_finder->pf_retrieve = Retrieve;

    return VLC_SUCCESS;
}