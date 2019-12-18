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
typedef  scalar_t__ vlc_iconv_t ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 size_t vlc_iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  vlc_iconv_close (scalar_t__) ; 
 scalar_t__ vlc_iconv_open (char*,char const*) ; 

char *FromCharset(const char *charset, const void *data, size_t data_size)
{
    vlc_iconv_t handle = vlc_iconv_open ("UTF-8", charset);
    if (handle == (vlc_iconv_t)(-1))
        return NULL;

    char *out = NULL;
    for(unsigned mul = 4; mul < 8; mul++ )
    {
        size_t in_size = data_size;
        const char *in = data;
        size_t out_max = mul * data_size;
        char *tmp = out = malloc (1 + out_max);
        if (!out)
            break;

        if (vlc_iconv (handle, &in, &in_size, &tmp, &out_max) != (size_t)(-1)) {
            *tmp = '\0';
            break;
        }
        free(out);
        out = NULL;

        if (errno != E2BIG)
            break;
    }
    vlc_iconv_close(handle);
    return out;
}