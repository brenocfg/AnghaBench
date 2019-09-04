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
struct wined3d_matrix {float _14; float _12; float _24; float _22; float _34; float _32; float _44; float _42; float _13; float _23; float _33; float _43; int /*<<< orphan*/  _31; int /*<<< orphan*/  _41; int /*<<< orphan*/  _21; } ;
struct wined3d_gl_info {int dummy; } ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
#define  WINED3DFMT_R32G32B32A32_FLOAT 134 
#define  WINED3DFMT_R32G32B32_FLOAT 133 
#define  WINED3DFMT_R32G32_FLOAT 132 
#define  WINED3DFMT_R32_FLOAT 131 
#define  WINED3DFMT_UNKNOWN 130 
 int WINED3D_TTFF_COUNT1 ; 
#define  WINED3D_TTFF_COUNT2 129 
#define  WINED3D_TTFF_COUNT3 128 
 int WINED3D_TTFF_DISABLE ; 
 int WINED3D_TTFF_PROJECTED ; 
 int /*<<< orphan*/  get_identity_matrix (struct wined3d_matrix*) ; 

__attribute__((used)) static void compute_texture_matrix(const struct wined3d_gl_info *gl_info, const struct wined3d_matrix *matrix,
        DWORD flags, BOOL calculated_coords, BOOL transformed, enum wined3d_format_id format_id,
        BOOL ffp_proj_control, struct wined3d_matrix *out_matrix)
{
    struct wined3d_matrix mat;

    if (flags == WINED3D_TTFF_DISABLE || flags == WINED3D_TTFF_COUNT1 || transformed)
    {
        get_identity_matrix(out_matrix);
        return;
    }

    if (flags == (WINED3D_TTFF_COUNT1 | WINED3D_TTFF_PROJECTED))
    {
        ERR("Invalid texture transform flags: WINED3D_TTFF_COUNT1 | WINED3D_TTFF_PROJECTED.\n");
        return;
    }

    mat = *matrix;

    if (flags & WINED3D_TTFF_PROJECTED)
    {
        if (!ffp_proj_control)
        {
            switch (flags & ~WINED3D_TTFF_PROJECTED)
            {
                case WINED3D_TTFF_COUNT2:
                    mat._14 = mat._12;
                    mat._24 = mat._22;
                    mat._34 = mat._32;
                    mat._44 = mat._42;
                    mat._12 = mat._22 = mat._32 = mat._42 = 0.0f;
                    break;
                case WINED3D_TTFF_COUNT3:
                    mat._14 = mat._13;
                    mat._24 = mat._23;
                    mat._34 = mat._33;
                    mat._44 = mat._43;
                    mat._13 = mat._23 = mat._33 = mat._43 = 0.0f;
                    break;
            }
        }
    }
    else
    {
        /* Under Direct3D the R/Z coord can be used for translation, under
         * OpenGL we use the Q coord instead. */
        if (!calculated_coords)
        {
            switch (format_id)
            {
                /* Direct3D passes the default 1.0 in the 2nd coord, while GL
                 * passes it in the 4th. Swap 2nd and 4th coord. No need to
                 * store the value of mat._41 in mat._21 because the input
                 * value to the transformation will be 0, so the matrix value
                 * is irrelevant. */
                case WINED3DFMT_R32_FLOAT:
                    mat._41 = mat._21;
                    mat._42 = mat._22;
                    mat._43 = mat._23;
                    mat._44 = mat._24;
                    break;
                /* See above, just 3rd and 4th coord. */
                case WINED3DFMT_R32G32_FLOAT:
                    mat._41 = mat._31;
                    mat._42 = mat._32;
                    mat._43 = mat._33;
                    mat._44 = mat._34;
                    break;
                case WINED3DFMT_R32G32B32_FLOAT: /* Opengl defaults match dx defaults */
                case WINED3DFMT_R32G32B32A32_FLOAT: /* No defaults apply, all app defined */

                /* This is to prevent swapping the matrix lines and put the default 4th coord = 1.0
                 * into a bad place. The division elimination below will apply to make sure the
                 * 1.0 doesn't do anything bad. The caller will set this value if the stride is 0
                 */
                case WINED3DFMT_UNKNOWN: /* No texture coords, 0/0/0/1 defaults are passed */
                    break;
                default:
                    FIXME("Unexpected fixed function texture coord input\n");
            }
        }
        if (!ffp_proj_control)
        {
            switch (flags & ~WINED3D_TTFF_PROJECTED)
            {
                /* case WINED3D_TTFF_COUNT1: Won't ever get here. */
                case WINED3D_TTFF_COUNT2:
                    mat._13 = mat._23 = mat._33 = mat._43 = 0.0f;
                /* OpenGL divides the first 3 vertex coordinates by the 4th by
                 * default, which is essentially the same as D3DTTFF_PROJECTED.
                 * Make sure that the 4th coordinate evaluates to 1.0 to
                 * eliminate that.
                 *
                 * If the fixed function pipeline is used, the 4th value
                 * remains unused, so there is no danger in doing this. With
                 * vertex shaders we have a problem. Should an application hit
                 * that problem, the code here would have to check for pixel
                 * shaders, and the shader has to undo the default GL divide.
                 *
                 * A more serious problem occurs if the application passes 4
                 * coordinates in, and the 4th is != 1.0 (OpenGL default).
                 * This would have to be fixed with immediate mode draws. */
                default:
                    mat._14 = mat._24 = mat._34 = 0.0f; mat._44 = 1.0f;
            }
        }
    }

    *out_matrix = mat;
}