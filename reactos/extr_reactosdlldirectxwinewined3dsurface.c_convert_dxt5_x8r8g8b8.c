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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DFMT_B8G8R8X8_UNORM ; 
 int /*<<< orphan*/  wined3d_dxt5_decode (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void convert_dxt5_x8r8g8b8(const BYTE *src, BYTE *dst,
        DWORD pitch_in, DWORD pitch_out, unsigned int w, unsigned int h)
{
    wined3d_dxt5_decode(src, dst, pitch_in, pitch_out, WINED3DFMT_B8G8R8X8_UNORM, w, h);
}