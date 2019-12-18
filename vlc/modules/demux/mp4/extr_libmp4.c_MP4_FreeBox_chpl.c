#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int i_chapter; TYPE_2__* chapter; } ;
struct TYPE_6__ {TYPE_4__* p_chpl; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_3__ MP4_Box_t ;
typedef  TYPE_4__ MP4_Box_data_chpl_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MP4_FreeBox_chpl( MP4_Box_t *p_box )
{
    MP4_Box_data_chpl_t *p_chpl = p_box->data.p_chpl;
    for( unsigned i = 0; i < p_chpl->i_chapter; i++ )
        free( p_chpl->chapter[i].psz_name );
}