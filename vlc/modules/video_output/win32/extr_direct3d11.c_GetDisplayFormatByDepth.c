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
typedef  TYPE_2__ vout_display_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  d3d_format_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  d3d_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_FORMAT_SUPPORT_SHADER_LOAD ; 
 int /*<<< orphan*/  D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT ; 
 int /*<<< orphan*/  const* FindD3D11Format (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const d3d_format_t *GetDisplayFormatByDepth(vout_display_t *vd, uint8_t bit_depth,
                                                   uint8_t widthDenominator,
                                                   uint8_t heightDenominator,
                                                   bool from_processor,
                                                   bool rgb_only)
{
    UINT supportFlags = D3D11_FORMAT_SUPPORT_SHADER_LOAD;
    if (from_processor)
        supportFlags |= D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT;
    return FindD3D11Format( vd, &vd->sys->d3d_dev, 0, rgb_only,
                            bit_depth, widthDenominator, heightDenominator,
                            false, supportFlags );
}