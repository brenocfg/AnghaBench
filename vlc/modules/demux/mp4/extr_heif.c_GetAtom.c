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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  const MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* NextAtom (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static MP4_Box_t * GetAtom( MP4_Box_t *p_root, MP4_Box_t *p_atom,
                            vlc_fourcc_t i_type, const char *psz_path,
                            bool(*pf_match)(const MP4_Box_t *, void *),
                            void *priv )
{
    while( (p_atom = NextAtom( p_root, i_type, psz_path, p_atom )) )
    {
        if( pf_match( p_atom, priv ) )
            return p_atom;
    }
    return NULL;
}