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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int i_blob; scalar_t__ p_blob; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_1__* BOXDATA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ID3TAG_Parse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3TAG_Parse_Handler ; 
 int /*<<< orphan*/ * MP4_BoxGet (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void SetupID3v2Meta( vlc_meta_t *p_meta, MP4_Box_t *p_box )
{
    const MP4_Box_t *p_binary = MP4_BoxGet( p_box, "ID32" );
    if( p_binary == NULL || !BOXDATA(p_binary) || BOXDATA(p_binary)->i_blob < 6 + 20 + 1 )
        return;

    /* ID3v2 in 3GPP / ETSI TS 126 244 8.3, Header size 4 + 2 */
    ID3TAG_Parse( &((uint8_t *)BOXDATA(p_binary)->p_blob)[6], BOXDATA(p_binary)->i_blob - 6,
                  ID3TAG_Parse_Handler, p_meta );
}