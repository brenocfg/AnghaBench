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
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ platform_id; scalar_t__ encoding_id; scalar_t__ name_id; scalar_t__ language_id; int string_len; int /*<<< orphan*/ * string; } ;
typedef  scalar_t__ FT_UShort ;
typedef  int FT_UInt ;
typedef  TYPE_1__ FT_SfntName ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 scalar_t__ GetSfntNameEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int U16_AT (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int GetSfntNameString( FT_Byte *p_table, FT_UInt i_size, FT_UShort i_platform_id,
                              FT_UShort i_encoding_id, FT_UShort i_name_id, FT_UShort i_language_id,
                              FT_Byte **pp_name, FT_UInt *i_name_length )
{
    uint16_t i_name_count     = U16_AT( p_table + 2 );
    uint16_t i_storage_offset = U16_AT( p_table + 4 );
    FT_Byte *p_storage        = p_table + i_storage_offset;
    FT_Byte *p_names          = p_table + 6;

    const int i_entry_size = 12;

    for(int i = 0; i < i_name_count; ++i)
    {
        FT_SfntName sfnt_name;

        if( GetSfntNameEntry( p_names + i * i_entry_size, p_storage, p_table + i_size, &sfnt_name ) )
            return VLC_EGENERIC;

        if( sfnt_name.platform_id == i_platform_id && sfnt_name.encoding_id == i_encoding_id
         && sfnt_name.name_id == i_name_id && sfnt_name.language_id == i_language_id )
        {
            *i_name_length = sfnt_name.string_len;
            *pp_name = sfnt_name.string;

            return VLC_SUCCESS;
        }
    }

    return VLC_EGENERIC;
}