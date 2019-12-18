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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  es_out_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * demux_NewAdvanced (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

demux_t *demux_New( vlc_object_t *p_obj, const char *psz_name,
                    stream_t *s, es_out_t *out )
{
    assert(s != NULL );
    return demux_NewAdvanced( p_obj, NULL, psz_name, "", s, out, false );
}