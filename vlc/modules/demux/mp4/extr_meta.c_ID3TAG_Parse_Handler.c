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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID3HandleTag (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int ID3TAG_Parse_Handler( uint32_t i_tag, const uint8_t *p_payload,
                                 size_t i_payload, void *p_priv )
{
    vlc_meta_t *p_meta = (vlc_meta_t *) p_priv;

    (void) ID3HandleTag( p_payload, i_payload, i_tag, p_meta, NULL );

    return VLC_SUCCESS;
}