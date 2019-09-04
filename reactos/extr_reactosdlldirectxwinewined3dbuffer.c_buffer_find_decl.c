#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_stream_info {int dummy; } ;
struct wined3d_state {int dummy; } ;
struct TYPE_2__ {int usage; } ;
struct wined3d_buffer {int flags; scalar_t__ stride; int /*<<< orphan*/ * conversion_map; TYPE_1__ resource; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 int WINED3DUSAGE_STATICDECL ; 
 int /*<<< orphan*/  WINED3D_BUFFER_FIXUP_XYZRHW ; 
 int WINED3D_BUFFER_HASDESC ; 
 int /*<<< orphan*/  WINED3D_FFP_BLENDINDICES ; 
 int /*<<< orphan*/  WINED3D_FFP_BLENDWEIGHT ; 
 int /*<<< orphan*/  WINED3D_FFP_DIFFUSE ; 
 int /*<<< orphan*/  WINED3D_FFP_NORMAL ; 
 int /*<<< orphan*/  WINED3D_FFP_POSITION ; 
 int /*<<< orphan*/  WINED3D_FFP_SPECULAR ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD0 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD1 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD2 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD3 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD4 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD5 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD6 ; 
 int /*<<< orphan*/  WINED3D_FFP_TEXCOORD7 ; 
 scalar_t__ buffer_check_attribute (struct wined3d_buffer*,struct wined3d_stream_info const*,struct wined3d_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL buffer_find_decl(struct wined3d_buffer *This, const struct wined3d_stream_info *si,
        const struct wined3d_state *state, DWORD fixup_flags)
{
    UINT stride_this_run = 0;
    BOOL ret = FALSE;

    /* In d3d7 the vertex buffer declaration NEVER changes because it is stored in the d3d7 vertex buffer.
     * Once we have our declaration there is no need to look it up again. Index buffers also never need
     * conversion, so once the (empty) conversion structure is created don't bother checking again
     */
    if (This->flags & WINED3D_BUFFER_HASDESC)
    {
        if(This->resource.usage & WINED3DUSAGE_STATICDECL) return FALSE;
    }

    if (!fixup_flags)
    {
        TRACE("No fixup required.\n");
        if(This->conversion_map)
        {
            heap_free(This->conversion_map);
            This->conversion_map = NULL;
            This->stride = 0;
            return TRUE;
        }

        return FALSE;
    }

    TRACE("Finding vertex buffer conversion information\n");
    /* Certain declaration types need some fixups before we can pass them to
     * opengl. This means D3DCOLOR attributes with fixed function vertex
     * processing, FLOAT4 POSITIONT with fixed function, and FLOAT16 if
     * GL_ARB_half_float_vertex is not supported.
     *
     * Note for d3d8 and d3d9:
     * The vertex buffer FVF doesn't help with finding them, we have to use
     * the decoded vertex declaration and pick the things that concern the
     * current buffer. A problem with this is that this can change between
     * draws, so we have to validate the information and reprocess the buffer
     * if it changes, and avoid false positives for performance reasons.
     * WineD3D doesn't even know the vertex buffer any more, it is managed
     * by the client libraries and passed to SetStreamSource and ProcessVertices
     * as needed.
     *
     * We have to distinguish between vertex shaders and fixed function to
     * pick the way we access the strided vertex information.
     *
     * This code sets up a per-byte array with the size of the detected
     * stride of the arrays in the buffer. For each byte we have a field
     * that marks the conversion needed on this byte. For example, the
     * following declaration with fixed function vertex processing:
     *
     *      POSITIONT, FLOAT4
     *      NORMAL, FLOAT3
     *      DIFFUSE, FLOAT16_4
     *      SPECULAR, D3DCOLOR
     *
     * Will result in
     * {                 POSITIONT                    }{             NORMAL                }{    DIFFUSE          }{SPECULAR }
     * [P][P][P][P][P][P][P][P][P][P][P][P][P][P][P][P][0][0][0][0][0][0][0][0][0][0][0][0][F][F][F][F][F][F][F][F][C][C][C][C]
     *
     * Where in this example map P means 4 component position conversion, 0
     * means no conversion, F means FLOAT16_2 conversion and C means D3DCOLOR
     * conversion (red / blue swizzle).
     *
     * If we're doing conversion and the stride changes we have to reconvert
     * the whole buffer. Note that we do not mind if the semantic changes,
     * we only care for the conversion type. So if the NORMAL is replaced
     * with a TEXCOORD, nothing has to be done, or if the DIFFUSE is replaced
     * with a D3DCOLOR BLENDWEIGHT we can happily dismiss the change. Some
     * conversion types depend on the semantic as well, for example a FLOAT4
     * texcoord needs no conversion while a FLOAT4 positiont needs one
     */

    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_POSITION,
            fixup_flags, &stride_this_run) || ret;
    fixup_flags &= ~WINED3D_BUFFER_FIXUP_XYZRHW;

    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_BLENDWEIGHT,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_BLENDINDICES,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_NORMAL,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_DIFFUSE,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_SPECULAR,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD0,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD1,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD2,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD3,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD4,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD5,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD6,
            fixup_flags, &stride_this_run) || ret;
    ret = buffer_check_attribute(This, si, state, WINED3D_FFP_TEXCOORD7,
            fixup_flags, &stride_this_run) || ret;

    if (!stride_this_run && This->conversion_map)
    {
        /* Sanity test */
        if (!ret)
            ERR("no converted attributes found, old conversion map exists, and no declaration change?\n");
        heap_free(This->conversion_map);
        This->conversion_map = NULL;
        This->stride = 0;
    }

    if (ret) TRACE("Conversion information changed\n");

    return ret;
}