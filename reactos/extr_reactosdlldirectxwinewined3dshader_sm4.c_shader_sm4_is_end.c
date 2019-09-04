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
struct wined3d_sm4_data {int /*<<< orphan*/  const* end; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL shader_sm4_is_end(void *data, const DWORD **ptr)
{
    struct wined3d_sm4_data *priv = data;
    return *ptr == priv->end;
}