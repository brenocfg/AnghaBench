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
typedef  int UINT ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11Device_CheckFormatSupport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool DeviceSupportsFormat(ID3D11Device *d3ddevice,
                                        DXGI_FORMAT format, UINT supportFlags)
{
    UINT i_formatSupport;
    return SUCCEEDED( ID3D11Device_CheckFormatSupport(d3ddevice, format,
                                                      &i_formatSupport) )
            && ( i_formatSupport & supportFlags ) == supportFlags;
}