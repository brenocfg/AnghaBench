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
#define  BMP_DFMT 136 
#define  J2K_CFMT 135 
#define  JP2_CFMT 134 
#define  PGX_DFMT 133 
#define  PNG_DFMT 132 
#define  PXM_DFMT 131 
#define  RAW_DFMT 130 
#define  TGA_DFMT 129 
#define  TIF_DFMT 128 
 scalar_t__ strcasecmp (char*,char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int get_file_format(char *filename)
{
    unsigned int i;
    static const char *extension[] = {
        "pgx", "pnm", "pgm", "ppm", "pbm", "pam", "bmp", "tif", "raw", "tga", "png", "j2k", "jp2", "j2c", "jpc"
    };
    static const int format[] = {
        PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT, TIF_DFMT, RAW_DFMT, TGA_DFMT, PNG_DFMT, J2K_CFMT, JP2_CFMT, J2K_CFMT, J2K_CFMT
    };
    char * ext = strrchr(filename, '.');
    if (ext == NULL) {
        return -1;
    }
    ext++;
    for (i = 0; i < sizeof(format) / sizeof(*format); i++) {
        if (strcasecmp(ext, extension[i]) == 0) {
            return format[i];
        }
    }
    return -1;
}