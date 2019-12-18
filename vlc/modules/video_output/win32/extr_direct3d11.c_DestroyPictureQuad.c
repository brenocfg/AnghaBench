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
struct TYPE_3__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  d3d_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ReleaseQuad (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DestroyPictureQuad(picture_t *p_picture)
{
    D3D11_ReleaseQuad( (d3d_quad_t *) p_picture->p_sys );
}