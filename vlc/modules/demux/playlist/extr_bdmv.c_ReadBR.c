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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 char* StreamLocation (int /*<<< orphan*/ *) ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_INPUT_OPTION_TRUSTED ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_AddOption (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 char* strndup (char const*,scalar_t__) ; 

__attribute__((used)) static int ReadBR( stream_t *p_stream, input_item_node_t *node )
{
    const char *psz_loc = StreamLocation(p_stream);

    // 10 character in INDEX.BDMV, 5 character in BDMV/, subtract 15
    char *psz_url = strndup( psz_loc, strlen( psz_loc) - 15 );
    if( !psz_url )
        return VLC_ENOMEM;

    input_item_t *p_input = input_item_New( psz_url, psz_url );
    input_item_AddOption( p_input, "demux=bluray", VLC_INPUT_OPTION_TRUSTED );
    input_item_node_AppendItem( node, p_input );
    input_item_Release( p_input );

    free( psz_url );

    return VLC_SUCCESS;
}