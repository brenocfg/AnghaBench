#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_stream_info_element {size_t stream_idx; TYPE_2__* format; } ;
struct wined3d_stream_info {unsigned int use_map; scalar_t__ position_transformed; struct wined3d_stream_info_element* elements; } ;
struct wined3d_state {TYPE_1__* streams; } ;
struct wined3d_buffer {scalar_t__ conversion_map; } ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
typedef  size_t UINT ;
struct TYPE_4__ {int id; } ;
struct TYPE_3__ {struct wined3d_buffer* buffer; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_D3DCOLOR ; 
 int /*<<< orphan*/  CONV_NONE ; 
 int /*<<< orphan*/  CONV_POSITIONT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int WINED3DFMT_B8G8R8A8_UNORM ; 
 int WINED3DFMT_R32G32B32A32_FLOAT ; 
 int WINED3D_BUFFER_FIXUP_D3DCOLOR ; 
 int WINED3D_BUFFER_FIXUP_XYZRHW ; 
 int /*<<< orphan*/  buffer_process_converted_attribute (struct wined3d_buffer*,int /*<<< orphan*/ ,struct wined3d_stream_info_element const*,int*) ; 
 int /*<<< orphan*/  debug_d3dformat (int) ; 

__attribute__((used)) static BOOL buffer_check_attribute(struct wined3d_buffer *This, const struct wined3d_stream_info *si,
        const struct wined3d_state *state, UINT attrib_idx, DWORD fixup_flags, DWORD *stride_this_run)
{
    const struct wined3d_stream_info_element *attrib = &si->elements[attrib_idx];
    enum wined3d_format_id format;
    BOOL ret = FALSE;

    /* Ignore attributes that do not have our vbo. After that check we can be sure that the attribute is
     * there, on nonexistent attribs the vbo is 0.
     */
    if (!(si->use_map & (1u << attrib_idx))
            || state->streams[attrib->stream_idx].buffer != This)
        return FALSE;

    format = attrib->format->id;
    /* Look for newly appeared conversion */
    if (fixup_flags & WINED3D_BUFFER_FIXUP_D3DCOLOR && format == WINED3DFMT_B8G8R8A8_UNORM)
    {
        ret = buffer_process_converted_attribute(This, CONV_D3DCOLOR, attrib, stride_this_run);
    }
    else if (fixup_flags & WINED3D_BUFFER_FIXUP_XYZRHW && si->position_transformed)
    {
        if (format != WINED3DFMT_R32G32B32A32_FLOAT)
        {
            FIXME("Unexpected format %s for transformed position.\n", debug_d3dformat(format));
            return FALSE;
        }

        ret = buffer_process_converted_attribute(This, CONV_POSITIONT, attrib, stride_this_run);
    }
    else if (This->conversion_map)
    {
        ret = buffer_process_converted_attribute(This, CONV_NONE, attrib, stride_this_run);
    }

    return ret;
}