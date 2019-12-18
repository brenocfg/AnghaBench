#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsUTF8 (char*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char const*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReadDir(stream_t *demux, input_item_node_t *subitems)
{
    char *line;

    while ((line = vlc_stream_ReadLine(demux->s)) != NULL)
    {
        if (!IsUTF8(line))
            goto skip;
        if (!strcmp(line, "[Reference]"))
            goto skip;

        const char *key = line;
        char *value = strchr(line, '=');
        if (value == NULL) {
            msg_Warn(demux, "unexpected entry \"%s\"", line);
            goto skip;
        }
        *(value++) = '\0';

        unsigned id;
        if (sscanf(key, "Ref%u", &id) != 1) {
            msg_Warn(demux, "unexpected entry key \"%s\"", key);
            goto skip;
        }

        if (!strncasecmp(value, "http://", 7))
            memcpy(value, "mmsh", 4); /* Force MMSH access/demux */

        input_item_t *item = input_item_New(value, value);
        input_item_node_AppendItem(subitems, item);
        input_item_Release(item);
skip:
        free(line);
    }
    return VLC_SUCCESS;
}