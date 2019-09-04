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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int cx; int cy; } ;
struct TYPE_5__ {int cx; int cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__* HIMAGELIST ;

/* Variables and functions */
 int TILE_COUNT ; 
 int imagelist_height (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void imagelist_get_bitmap_size( HIMAGELIST himl, UINT count, SIZE *sz )
{
    sz->cx = himl->cx * TILE_COUNT;
    sz->cy = imagelist_height( count ) * himl->cy;
}