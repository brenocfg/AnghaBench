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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ i_tag; int /*<<< orphan*/  psz; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int ID3LinkFrameTagHandler (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int*) ; 
 char* ID3TextConv (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const,char**) ; 
 char* ID3TextConvert (int /*<<< orphan*/  const*,size_t,char**) ; 
 int ID3TextTagHandler (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* ID3_tag_to_metatype ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ vlc_meta_GetExtraCount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ID3HandleTag( const uint8_t *p_buf, size_t i_buf,
                          uint32_t i_tag,
                          vlc_meta_t *p_meta, bool *pb_updated )
{
    if( i_tag == VLC_FOURCC('W', 'X', 'X', 'X') )
    {
        return ID3LinkFrameTagHandler( p_buf, i_buf, p_meta, pb_updated );
    }
    else if( i_tag == VLC_FOURCC('T', 'X', 'X', 'X') )
    {
        char *psz_key_alloc;
        const char *psz_key = ID3TextConvert( p_buf, i_buf, &psz_key_alloc );
        if( psz_key )
        {
            const size_t i_len = strlen( psz_key ) + 2;
            if( i_len < i_buf )
            {
                /* Only set those which are known as non binary */
                if( !strncasecmp( psz_key, "REPLAYGAIN_", 11 ) )
                {
                    char *psz_val_alloc;
                    const char *psz_val = ID3TextConv( &p_buf[i_len], i_buf - i_len,
                                                       p_buf[0], &psz_val_alloc );
                    if( psz_val )
                    {
                        vlc_meta_AddExtra( p_meta, psz_key, psz_val );
                        free( psz_val_alloc );
                    }
                }
            }
            free( psz_key_alloc );
            return (vlc_meta_GetExtraCount( p_meta ) > 0);
        }
    }
    else if ( ((const char *) &i_tag)[0] == 'T' )
    {
        for( size_t i=0; i<ARRAY_SIZE(ID3_tag_to_metatype); i++ )
        {
            if( ID3_tag_to_metatype[i].i_tag == i_tag )
                return ID3TextTagHandler( p_buf, i_buf,
                                          ID3_tag_to_metatype[i].type,
                                          ID3_tag_to_metatype[i].psz,
                                          p_meta, pb_updated );
        }
    }

    return false;
}