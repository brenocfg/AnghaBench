#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_sdp; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_sdp_t ; 
 int /*<<< orphan*/  MP4_FreeBox_sdp ; 
 int /*<<< orphan*/  MP4_GETSTRINGZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 

__attribute__((used)) static int MP4_ReadBox_sdp( stream_t *p_stream, MP4_Box_t *p_box )
{
   MP4_READBOX_ENTER( MP4_Box_data_sdp_t, MP4_FreeBox_sdp );

   MP4_GETSTRINGZ( p_box->data.p_sdp->psz_text );

   MP4_READBOX_EXIT( 1 );
}