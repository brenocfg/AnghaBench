#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int width; int height; int Bpp; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ bitmap ;
typedef  void* HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  copy_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int g_server_Bpp ; 
 scalar_t__ xmalloc (int) ; 

HBITMAP ui_create_bitmap(int width, int height, uint8* data)
{
  bitmap* b;

  b = (bitmap*)xmalloc(sizeof(bitmap));
  b->data = (uint8*)xmalloc(width * height * g_server_Bpp);
  b->width = width;
  b->height = height;
  b->Bpp = g_server_Bpp;
  copy_mem(b->data, data, width * height * g_server_Bpp);
  return (void*)b;
}