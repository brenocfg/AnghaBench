#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  int /*<<< orphan*/ * png_FILE_p ;
struct TYPE_4__ {int /*<<< orphan*/  io_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_io_ptr (TYPE_1__*) ; 

__attribute__((used)) static void
jbig2_png_flush(png_structp png_ptr)
{
#if OLD_LIB_PNG
    png_FILE_p f = (png_FILE_p) png_ptr->io_ptr;
#else
    png_FILE_p f = (png_FILE_p) png_get_io_ptr(png_ptr);
#endif

    if (f != NULL)
        fflush(f);
}