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
typedef  int /*<<< orphan*/  seekpoint_t ;
struct TYPE_3__ {unsigned int i_size; int /*<<< orphan*/ ** pp_chapters; } ;
typedef  TYPE_1__ chapters_array_t ;

/* Variables and functions */
 void* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * vlc_seekpoint_New () ; 

__attribute__((used)) static seekpoint_t * getChapterEntry( unsigned int i_index, chapters_array_t *p_array )
{
    if ( i_index > 4096 ) return NULL;
    if ( i_index >= p_array->i_size )
    {
        unsigned int i_newsize = p_array->i_size;
        while( i_index >= i_newsize ) i_newsize += 50;

        if ( !p_array->pp_chapters )
        {
            p_array->pp_chapters = calloc( i_newsize, sizeof( seekpoint_t * ) );
            if ( !p_array->pp_chapters ) return NULL;
            p_array->i_size = i_newsize;
        } else {
            seekpoint_t **tmp = calloc( i_newsize, sizeof( seekpoint_t * ) );
            if ( !tmp ) return NULL;
            memcpy( tmp, p_array->pp_chapters, p_array->i_size * sizeof( seekpoint_t * ) );
            free( p_array->pp_chapters );
            p_array->pp_chapters = tmp;
            p_array->i_size = i_newsize;
        }
    }
    if ( !p_array->pp_chapters[i_index] )
        p_array->pp_chapters[i_index] = vlc_seekpoint_New();
    return p_array->pp_chapters[i_index];
}