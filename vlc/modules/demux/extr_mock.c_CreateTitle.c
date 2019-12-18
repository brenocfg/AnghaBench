#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct demux_sys {size_t chapter_count; size_t chapter_gap; int /*<<< orphan*/  null_names; int /*<<< orphan*/  length; } ;
typedef  size_t ssize_t ;
struct TYPE_9__ {TYPE_3__** seekpoint; int /*<<< orphan*/  i_seekpoint; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/  i_length; } ;
typedef  TYPE_1__ input_title_t ;
struct TYPE_10__ {struct demux_sys* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {size_t i_time_offset; int /*<<< orphan*/  psz_name; } ;

/* Variables and functions */
 int asprintf (int /*<<< orphan*/ *,char*,size_t,...) ; 
 TYPE_3__** vlc_alloc (size_t,int) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (TYPE_1__*) ; 
 TYPE_1__* vlc_input_title_New () ; 
 TYPE_3__* vlc_seekpoint_New () ; 

__attribute__((used)) static input_title_t *
CreateTitle(demux_t *demux, size_t idx)
{
    struct demux_sys *sys = demux->p_sys;

    input_title_t *t = vlc_input_title_New();
    if (!t)
        return NULL;

    t->i_length = sys->length;
    if (!sys->null_names
     && asprintf(&t->psz_name, "Mock Title %zu", idx) == -1)
    {
        t->psz_name = NULL;
        vlc_input_title_Delete(t);
        return NULL;
    }
    t->seekpoint = vlc_alloc(sys->chapter_count, sizeof(*t->seekpoint));
    if (!t->seekpoint)
    {
        vlc_input_title_Delete(t);
        return NULL;
    }

    for (ssize_t i = 0; i < sys->chapter_count; ++i)
    {
        t->seekpoint[i] = vlc_seekpoint_New();
        if (!t->seekpoint[i])
        {
            vlc_input_title_Delete(t);
            return NULL;
        }
        t->i_seekpoint++;
        if (!sys->null_names
         && asprintf(&t->seekpoint[i]->psz_name, "Mock Chapter %zu-%zu", idx, i)
            == -1)
        {
            vlc_input_title_Delete(t);
            return NULL;
        }
        t->seekpoint[i]->i_time_offset = i * sys->chapter_gap;
    }
    return t;
}