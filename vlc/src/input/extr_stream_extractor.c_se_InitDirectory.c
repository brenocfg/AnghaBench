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
struct TYPE_7__ {TYPE_1__* source; } ;
struct stream_extractor_private {TYPE_3__ directory; } ;
struct TYPE_6__ {int /*<<< orphan*/  psz_url; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; } ;
typedef  TYPE_2__ stream_t ;
typedef  TYPE_3__ stream_directory_t ;
struct TYPE_5__ {int /*<<< orphan*/  psz_url; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  se_DirControl ; 
 int /*<<< orphan*/  se_ReadDir ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
se_InitDirectory( struct stream_extractor_private* priv, stream_t* s )
{
    stream_directory_t* directory = &priv->directory;

    s->pf_readdir = se_ReadDir;
    s->pf_control = se_DirControl;
    s->psz_url = strdup( directory->source->psz_url );

    if( unlikely( !s->psz_url ) )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}