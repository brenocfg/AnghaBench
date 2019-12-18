#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_tracklist_entries; int i_track_id; int /*<<< orphan*/ ** pp_tracklist; int /*<<< orphan*/  psz_base; } ;
typedef  TYPE_1__ xspf_sys_t ;
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_8__ {int /*<<< orphan*/  s; int /*<<< orphan*/  psz_url; TYPE_1__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 scalar_t__ XML_READER_STARTELEM ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 scalar_t__ parse_playlist_node (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xml_ReaderCreate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_ReaderDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xml_ReaderIsEmptyElement (int /*<<< orphan*/ *) ; 
 scalar_t__ xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int ReadDir(stream_t *p_stream, input_item_node_t *p_subitems)
{
    xspf_sys_t *sys = p_stream->p_sys;
    int i_ret = -1;
    xml_reader_t *p_xml_reader = NULL;
    const char *name = NULL;

    sys->pp_tracklist = NULL;
    sys->i_tracklist_entries = 0;
    sys->i_track_id = -1;
    sys->psz_base = strdup(p_stream->psz_url);

    /* create new xml parser from stream */
    p_xml_reader = xml_ReaderCreate(p_stream, p_stream->s);
    if (!p_xml_reader)
        goto end;

    /* locating the root node */
    if (xml_ReaderNextNode(p_xml_reader, &name) != XML_READER_STARTELEM)
    {
        msg_Err(p_stream, "can't read xml stream");
        goto end;
    }

    /* checking root node name */
    if (strcmp(name, "playlist"))
    {
        msg_Err(p_stream, "invalid root node name <%s>", name);
        goto end;
    }

    if(xml_ReaderIsEmptyElement(p_xml_reader))
        goto end;

    i_ret = parse_playlist_node(p_stream, p_subitems,
                                 p_xml_reader, "playlist", false ) ? 0 : -1;

    for (int i = 0 ; i < sys->i_tracklist_entries ; i++)
    {
        input_item_t *p_new_input = sys->pp_tracklist[i];
        if (p_new_input)
        {
            input_item_node_AppendItem(p_subitems, p_new_input);
        }
    }

end:
    if (p_xml_reader)
        xml_ReaderDelete(p_xml_reader);
    return i_ret; /* Needed for correct operation of go back */
}