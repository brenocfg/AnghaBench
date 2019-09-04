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

/* Variables and functions */
 int stbgl_TexImage2D_Extra (int,int,int,void*,int /*<<< orphan*/ ,char*,int) ; 

int stbgl_TexImage2D(int texid, int w, int h, void *data, char *props)
{
   return stbgl_TexImage2D_Extra(texid, w, h, data, 0, props,1);
}