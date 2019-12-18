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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ XDeintNxNDetect (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  XDeintNxNField (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  XDeintNxNFrame (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static inline void XDeintNxN( uint8_t *dst, int i_dst, uint8_t *src, int i_src,
                              int i_width, int i_height )
{
    if( XDeintNxNDetect( src, i_src, i_width, i_height ) )
        XDeintNxNField( dst, i_dst, src, i_src, i_width, i_height );
    else
        XDeintNxNFrame( dst, i_dst, src, i_src, i_width, i_height );
}