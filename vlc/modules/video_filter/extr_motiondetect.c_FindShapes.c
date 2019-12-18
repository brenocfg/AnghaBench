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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  GaussianConvolution (int*,int*,int,int,int) ; 
 int NUM_COLORS ; 
 int __MAX (int,int) ; 
 int __MIN (int,int) ; 

__attribute__((used)) static int FindShapes( uint32_t *p_diff, uint32_t *p_smooth,
                       int i_pitch, int i_visible, int i_lines,
                       int *colors,
                       int *color_x_min, int *color_x_max,
                       int *color_y_min, int *color_y_max )
{
    int last = 1;

    /**
     * Apply some smoothing to remove noise
     */
    GaussianConvolution( p_diff, p_smooth, i_pitch, i_lines, i_visible );

    /**
     * Label the shapes and build the labels dependencies list
     */
    for( int j = 0; j < i_pitch; j++ )
    {
        p_smooth[j] = 0;
        p_smooth[(i_lines-1)*i_pitch+j] = 0;
    }
    for( int i = 1; i < i_lines-1; i++ )
    {
        int j;
        p_smooth[i*i_pitch] = 0;
        for( j = 1; j < i_pitch-1; j++ )
        {
            if( p_smooth[i*i_pitch+j] > 15 )
            {
                if( p_smooth[(i-1)*i_pitch+j-1] )
                {
                    p_smooth[i*i_pitch+j] = p_smooth[(i-1)*i_pitch+j-1];
                }
                else if( p_smooth[(i-1)*i_pitch+j] )
                    p_smooth[i*i_pitch+j] = p_smooth[(i-1)*i_pitch+j];
                else if( p_smooth[i*i_pitch+j-1] )
                    p_smooth[i*i_pitch+j] = p_smooth[i*i_pitch+j-1];
                else
                {
                    if( last < NUM_COLORS )
                    {
                        p_smooth[i*i_pitch+j] = last;
                        colors[last] = last;
                        last++;
                    }
                }
                #define CHECK( A ) \
                if( p_smooth[A] && p_smooth[A] != p_smooth[i*i_pitch+j] ) \
                { \
                    if( p_smooth[A] < p_smooth[i*i_pitch+j] ) \
                        colors[p_smooth[i*i_pitch+j]] = p_smooth[A]; \
                    else \
                        colors[p_smooth[A]] = p_smooth[i*i_pitch+j]; \
                }
                CHECK( i*i_pitch+j-1 );
                CHECK( (i-1)*i_pitch+j-1 );
                CHECK( (i-1)*i_pitch+j );
                CHECK( (i-1)*i_pitch+j+1 );
                #undef CHECK
            }
            else
            {
                p_smooth[i*i_pitch+j] = 0;
            }
        }
        p_smooth[i*i_pitch+j] = 0;
    }

    /**
     * Initialise empty rectangle list
     */
    for( int i = 1; i < last; i++ )
    {
        color_x_min[i] = -1;
        color_x_max[i] = -1;
        color_y_min[i] = -1;
        color_y_max[i] = -1;
    }

    /**
     * Compute rectangle coordinates
     */
    for( int i = 0; i < i_pitch * i_lines; i++ )
    {
        if( p_smooth[i] )
        {
            while( colors[p_smooth[i]] != (int)p_smooth[i] )
                p_smooth[i] = colors[p_smooth[i]];
            if( color_x_min[p_smooth[i]] == -1 )
            {
                color_x_min[p_smooth[i]] =
                color_x_max[p_smooth[i]] = i % i_pitch;
                color_y_min[p_smooth[i]] =
                color_y_max[p_smooth[i]] = i / i_pitch;
            }
            else
            {
                int x = i % i_pitch, y = i / i_pitch;
                if( x < color_x_min[p_smooth[i]] )
                    color_x_min[p_smooth[i]] = x;
                if( x > color_x_max[p_smooth[i]] )
                    color_x_max[p_smooth[i]] = x;
                if( y < color_y_min[p_smooth[i]] )
                    color_y_min[p_smooth[i]] = y;
                if( y > color_y_max[p_smooth[i]] )
                    color_y_max[p_smooth[i]] = y;
            }
        }
    }

    /**
     * Merge overlaping rectangles
     */
    for( int i = 1; i < last; i++ )
    {
        if( colors[i] != i ) continue;
        if( color_x_min[i] == -1 ) continue;
        for( int j = i+1; j < last; j++ )
        {
            if( colors[j] != j ) continue;
            if( color_x_min[j] == -1 ) continue;
            if( __MAX( color_x_min[i], color_x_min[j] ) < __MIN( color_x_max[i], color_x_max[j] ) &&
                __MAX( color_y_min[i], color_y_min[j] ) < __MIN( color_y_max[i], color_y_max[j] ) )
            {
                color_x_min[i] = __MIN( color_x_min[i], color_x_min[j] );
                color_x_max[i] = __MAX( color_x_max[i], color_x_max[j] );
                color_y_min[i] = __MIN( color_y_min[i], color_y_min[j] );
                color_y_max[i] = __MAX( color_y_max[i], color_y_max[j] );
                color_x_min[j] = -1;
                j = 0;
            }
        }
    }

    return last;
}