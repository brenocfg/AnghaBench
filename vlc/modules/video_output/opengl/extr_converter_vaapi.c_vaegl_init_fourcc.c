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
struct priv {unsigned int fourcc; void** drm_fourccs; } ;
typedef  int /*<<< orphan*/  opengl_tex_converter_t ;

/* Variables and functions */
#define  VA_FOURCC_422H 135 
#define  VA_FOURCC_444P 134 
#define  VA_FOURCC_BGRA 133 
#define  VA_FOURCC_NV12 132 
#define  VA_FOURCC_P010 131 
#define  VA_FOURCC_RGBA 130 
#define  VA_FOURCC_UYVY 129 
#define  VA_FOURCC_YV12 128 
 int VLC_EGENERIC ; 
 void* VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int
vaegl_init_fourcc(const opengl_tex_converter_t *tc, struct priv *priv,
                  unsigned va_fourcc)
{
    (void) tc;
    switch (va_fourcc)
    {
        case VA_FOURCC_NV12:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '8', ' ', ' ');
            priv->drm_fourccs[1] = VLC_FOURCC('G', 'R', '8', '8');
            break;
        case VA_FOURCC_P010:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '1', '6', ' ');
            priv->drm_fourccs[1] = VLC_FOURCC('G', 'R', '3', '2');
            break;
#if 0
        /* TODO: the following fourcc are not handled for now */
        case VA_FOURCC_RGBA:
            priv->drm_fourccs[0] = VLC_FOURCC('G', 'R', '3', '2');
            break;
        case VA_FOURCC_BGRA:
            priv->drm_fourccs[0] = VLC_FOURCC('G', 'R', '3', '2');
            break;
        case VA_FOURCC_YV12:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '8', ' ', ' ');
            priv->drm_fourccs[1] = VLC_FOURCC('R', '8', ' ', ' ');
            priv->drm_fourccs[2] = VLC_FOURCC('R', '8', ' ', ' ');
            break;
        case VA_FOURCC_422H:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '8', ' ', ' ');
            priv->drm_fourccs[1] = VLC_FOURCC('R', '8', ' ', ' ');
            priv->drm_fourccs[2] = VLC_FOURCC('R', '8', ' ', ' ');
            break;
        case VA_FOURCC_UYVY:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '1', '6', ' ');
            break;
        case VA_FOURCC_444P:
            priv->drm_fourccs[0] = VLC_FOURCC('R', '1', '6', ' ');
            priv->drm_fourccs[1] = VLC_FOURCC('R', '1', '6', ' ');
            priv->drm_fourccs[2] = VLC_FOURCC('R', '1', '6', ' ');
            break;
#endif
        default: return VLC_EGENERIC;
    }
    priv->fourcc = va_fourcc;
    return VLC_SUCCESS;
}