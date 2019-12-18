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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  const ATOM_data ; 
 int MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int MP4_ReadBox_Metadata( stream_t *p_stream, MP4_Box_t *p_box )
{
    const uint8_t *p_peek;
    if ( vlc_stream_Peek( p_stream, &p_peek, 16 ) < 16 )
        return 0;
    if ( vlc_stream_Read( p_stream, NULL, 8 ) < 8 )
        return 0;
    const uint32_t stoplist[] = { ATOM_data, 0 };
    return MP4_ReadBoxContainerChildren( p_stream, p_box, stoplist );
}