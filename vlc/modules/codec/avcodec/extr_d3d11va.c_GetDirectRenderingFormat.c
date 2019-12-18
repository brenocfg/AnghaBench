#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_va_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  d3d_format_t ;
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/  d3d_dev; } ;

/* Variables and functions */
 int D3D11_FORMAT_SUPPORT_DECODER_OUTPUT ; 
 int D3D11_FORMAT_SUPPORT_SHADER_LOAD ; 
 int /*<<< orphan*/  const* FindD3D11Format (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static const d3d_format_t *GetDirectRenderingFormat(vlc_va_t *vd, vlc_fourcc_t i_src_chroma)
{
    UINT supportFlags = D3D11_FORMAT_SUPPORT_DECODER_OUTPUT | D3D11_FORMAT_SUPPORT_SHADER_LOAD;
    return FindD3D11Format( vd, &vd->sys->d3d_dev, i_src_chroma, false, 0, 0, 0, true, supportFlags );
}