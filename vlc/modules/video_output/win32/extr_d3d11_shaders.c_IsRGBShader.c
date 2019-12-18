#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* resourceFormat; scalar_t__ formatTexture; } ;
typedef  TYPE_1__ d3d_format_t ;

/* Variables and functions */
 scalar_t__ DXGI_FORMAT_R16_UNORM ; 
 scalar_t__ DXGI_FORMAT_R8_UNORM ; 
 scalar_t__ DXGI_FORMAT_YUY2 ; 

bool IsRGBShader(const d3d_format_t *cfg)
{
    return cfg->resourceFormat[0] != DXGI_FORMAT_R8_UNORM &&
           cfg->resourceFormat[0] != DXGI_FORMAT_R16_UNORM &&
           cfg->formatTexture != DXGI_FORMAT_YUY2;
}