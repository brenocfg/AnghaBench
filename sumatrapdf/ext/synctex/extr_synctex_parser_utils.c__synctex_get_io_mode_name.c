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
typedef  int synctex_io_mode_t ;

/* Variables and functions */
 int synctex_io_append_mask ; 
 int synctex_io_gz_mask ; 

const char * _synctex_get_io_mode_name(synctex_io_mode_t io_mode) {
    static const char * synctex_io_modes[4] = {"r","rb","a","ab"}; 
    unsigned index = ((io_mode & synctex_io_gz_mask)?1:0) + ((io_mode & synctex_io_append_mask)?2:0);// bug pointed out by Jose Alliste
    return synctex_io_modes[index];
}