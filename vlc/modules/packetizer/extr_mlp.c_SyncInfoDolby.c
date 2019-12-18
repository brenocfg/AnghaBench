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
struct TYPE_3__ {int i_size; } ;
typedef  TYPE_1__ vlc_a52_header_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MLP_HEADER_SIZE ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_a52_header_Parse (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SyncInfoDolby( const uint8_t *p_buf )
{
    vlc_a52_header_t a52;
    if( vlc_a52_header_Parse( &a52, p_buf, MLP_HEADER_SIZE ) == VLC_SUCCESS )
        return a52.i_size;
    else
        return 0;
}