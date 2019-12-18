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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ stream_extractor_AttachParsed (int /*<<< orphan*/ **,char const*,char const**) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_NewURL (int /*<<< orphan*/ *,char const*) ; 

stream_t *(vlc_stream_NewMRL)(vlc_object_t* parent, const char* mrl )
{
    stream_t* stream = vlc_stream_NewURL( parent, mrl );

    if( stream == NULL )
        return NULL;

    char const* anchor = strchr( mrl, '#' );

    if( anchor == NULL )
        return stream;

    char const* extra;
    if( stream_extractor_AttachParsed( &stream, anchor + 1, &extra ) )
    {
        msg_Err( parent, "unable to open %s", mrl );
        vlc_stream_Delete( stream );
        return NULL;
    }

    if( extra && *extra )
        msg_Warn( parent, "ignoring extra fragment data: %s", extra );

    return stream;
}