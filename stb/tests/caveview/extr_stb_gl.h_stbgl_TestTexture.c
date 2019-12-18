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
 int stbgl_TestTextureEx (int,char*,int,int,int,int,int,int,int) ; 

int stbgl_TestTexture(int w)
{
   char scale_table[] = { 10,20,30,30,35,40,5,18,25,13,7,5,3,3,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 };
   return stbgl_TestTextureEx(w, scale_table, 2, 140,130,200, 180,200,170);
}