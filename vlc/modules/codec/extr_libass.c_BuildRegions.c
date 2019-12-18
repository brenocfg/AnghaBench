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
typedef  int /*<<< orphan*/  rectangle_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ w; scalar_t__ h; struct TYPE_6__* next; } ;
typedef  TYPE_1__ ASS_Image ;

/* Variables and functions */
 int INT_MAX ; 
 int __MAX (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  p_spu ; 
 int /*<<< orphan*/  r_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_img (TYPE_1__*) ; 
 int /*<<< orphan*/  r_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int r_surface (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static int BuildRegions( rectangle_t *p_region, int i_max_region, ASS_Image *p_img_list, int i_width, int i_height )
{
    ASS_Image *p_tmp;
    int i_count;

#ifdef DEBUG_REGION
    int64_t i_ck_start = vlc_tick_now();
#endif

    for( p_tmp = p_img_list, i_count = 0; p_tmp != NULL; p_tmp = p_tmp->next )
        if( p_tmp->w > 0 && p_tmp->h > 0 )
            i_count++;
    if( i_count <= 0 )
        return 0;

    ASS_Image **pp_img = calloc( i_count, sizeof(*pp_img) );
    if( !pp_img )
        return 0;

    for( p_tmp = p_img_list, i_count = 0; p_tmp != NULL; p_tmp = p_tmp->next )
        if( p_tmp->w > 0 && p_tmp->h > 0 )
            pp_img[i_count++] = p_tmp;

    /* */
    const int i_w_inc = __MAX( ( i_width + 49 ) / 50, 32 );
    const int i_h_inc = __MAX( ( i_height + 99 ) / 100, 32 );
    int i_maxh = i_w_inc;
    int i_maxw = i_h_inc;
    int i_region;
    rectangle_t region[i_max_region+1];

    i_region = 0;
    for( int i_used = 0; i_used < i_count; )
    {
        int n;
        for( n = 0; n < i_count; n++ )
        {
            if( pp_img[n] )
                break;
        }
        assert( i_region < i_max_region + 1 );
        region[i_region++] = r_img( pp_img[n] );
        pp_img[n] = NULL; i_used++;

        bool b_ok;
        do {
            b_ok = false;
            for( n = 0; n < i_count; n++ )
            {
                ASS_Image *p_img = pp_img[n];
                if( !p_img )
                    continue;
                rectangle_t r = r_img( p_img );

                int k;
                int i_best = -1;
                int i_best_s = INT_MAX;
                for( k = 0; k < i_region; k++ )
                {
                    if( !r_overlap( &region[k], &r, i_maxw, i_maxh ) )
                        continue;
                    int s = r_surface( &r );
                    if( s < i_best_s )
                    {
                        i_best_s = s;
                        i_best = k;
                    }
                }
                if( i_best >= 0 )
                {
                    r_add( &region[i_best], &r );
                    pp_img[n] = NULL; i_used++;
                    b_ok = true;
                }
            }
        } while( b_ok );

        if( i_region > i_max_region )
        {
            int i_best_i = -1;
            int i_best_j = -1;
            int i_best_ds = INT_MAX;

            /* merge best */
            for( int i = 0; i < i_region; i++ )
            {
                for( int j = i+1; j < i_region; j++ )
                {
                    rectangle_t rect = region[i];
                    r_add( &rect, &region[j] );
                    int ds = r_surface( &rect ) - r_surface( &region[i] ) - r_surface( &region[j] );

                    if( ds < i_best_ds )
                    {
                        i_best_i = i;
                        i_best_j = j;
                        i_best_ds = ds;
                    }
                }
            }
#ifdef DEBUG_REGION
            msg_Err( p_spu, "Merging %d and %d", i_best_i, i_best_j );
#endif
            if( i_best_j >= 0 && i_best_i >= 0 )
            {
                r_add( &region[i_best_i], &region[i_best_j] );

                if( i_best_j+1 < i_region )
                    memmove( &region[i_best_j], &region[i_best_j+1], sizeof(*region) * ( i_region - (i_best_j+1)  ) );
                i_region--;
            }
        }
    }

    /* */
    for( int n = 0; n < i_region; n++ )
        p_region[n] = region[n];

#ifdef DEBUG_REGION
    int64_t i_ck_time = vlc_tick_now() - i_ck_start;
    msg_Err( p_spu, "ASS: %d objects merged into %d region in %d micros", i_count, i_region, (int)(i_ck_time) );
#endif

    free( pp_img );

    return i_region;
}