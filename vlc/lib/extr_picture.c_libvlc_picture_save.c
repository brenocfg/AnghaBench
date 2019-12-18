#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* converted; } ;
typedef  TYPE_2__ libvlc_picture_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char*) ; 

int libvlc_picture_save( const libvlc_picture_t* pic, const char* path )
{
    FILE* file = vlc_fopen( path, "wb" );
    if ( !file )
        return -1;
    size_t res = fwrite( pic->converted->p_buffer,
                         pic->converted->i_buffer, 1, file );
    fclose( file );
    return res == 1 ? 0 : -1;
}