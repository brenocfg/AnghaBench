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
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReadDVD_VR( stream_t *p_stream, input_item_node_t *node )
{
    const char *psz_location = StreamLocation(p_stream);

    size_t len = strlen( psz_location );
    char *psz_url = strdup( psz_location );

    if( unlikely( psz_url == NULL ) )
        return VLC_EGENERIC;

    strcpy( &psz_url[len - 12], "VR_MOVIE.VRO" );

    input_item_t *p_input = input_item_New( psz_url, psz_url );
    if( p_input )
    {
        input_item_node_AppendItem( node, p_input );
        input_item_Release( p_input );
    }

    free( psz_url );

    return VLC_SUCCESS;
}