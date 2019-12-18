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
struct TYPE_3__ {int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (void*) ; 

void
  af_shaper_buf_destroy( FT_Face  face,
                         void*    buf )
  {
    FT_Memory  memory = face->memory;


    FT_FREE( buf );
  }