#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  psz_notice; int /*<<< orphan*/  rgs_language; } ;
struct TYPE_5__ {TYPE_4__* p_cprt; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_cprt_t ; 
 int /*<<< orphan*/  MP4_FreeBox_cprt ; 
 int /*<<< orphan*/  MP4_GET2BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETSTRINGZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_4__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int /*<<< orphan*/  decodeQtLanguageCode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MP4_ReadBox_cprt( stream_t *p_stream, MP4_Box_t *p_box )
{
    uint16_t i_language;
    bool b_mac;

    MP4_READBOX_ENTER( MP4_Box_data_cprt_t, MP4_FreeBox_cprt );

    MP4_GETVERSIONFLAGS( p_box->data.p_cprt );

    MP4_GET2BYTES( i_language );
    decodeQtLanguageCode( i_language, p_box->data.p_cprt->rgs_language, &b_mac );

    MP4_GETSTRINGZ( p_box->data.p_cprt->psz_notice );

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"cprt\" language %3.3s notice %s",
                      p_box->data.p_cprt->rgs_language,
                      p_box->data.p_cprt->psz_notice );

#endif
    MP4_READBOX_EXIT( 1 );
}