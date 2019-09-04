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
typedef  scalar_t__ D3DXPARAMETER_TYPE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ D3DXPT_SAMPLER ; 
 scalar_t__ D3DXPT_SAMPLER1D ; 
 scalar_t__ D3DXPT_SAMPLER2D ; 
 scalar_t__ D3DXPT_SAMPLER3D ; 
 scalar_t__ D3DXPT_SAMPLERCUBE ; 

__attribute__((used)) static inline BOOL is_param_type_sampler(D3DXPARAMETER_TYPE type)
{
    return type == D3DXPT_SAMPLER
            || type == D3DXPT_SAMPLER1D || type == D3DXPT_SAMPLER2D
            || type == D3DXPT_SAMPLER3D || type == D3DXPT_SAMPLERCUBE;
}