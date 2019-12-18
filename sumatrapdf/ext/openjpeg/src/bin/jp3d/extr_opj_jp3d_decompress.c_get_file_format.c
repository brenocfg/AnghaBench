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
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
#define  BIN_DFMT 132 
#define  IMG_DFMT 131 
#define  J2K_CFMT 130 
#define  J3D_CFMT 129 
#define  PGX_DFMT 128 
 scalar_t__ strnicmp (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

int get_file_format(char *filename)
{
    int i;
    static const char *extension[] = {"pgx", "bin", "j3d", "jp3d", "j2k", "img"};
    static const int format[] = { PGX_DFMT, BIN_DFMT, J3D_CFMT, J3D_CFMT, J2K_CFMT, IMG_DFMT};
    char * ext = strrchr(filename, '.');
    if (ext) {
        ext++;
        for (i = 0; i < sizeof(format) / sizeof(format[0]); i++) {
            if (strnicmp(ext, extension[i], 3) == 0) {
                return format[i];
            }
        }
    }

    return -1;
}