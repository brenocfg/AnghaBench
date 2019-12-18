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
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ParseLine (char*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReadDir(stream_t *s, input_item_node_t *subitems)
{
    char *line;

    while ((line = vlc_stream_ReadLine(s->s)) != NULL)
    {
        input_item_t *item = ParseLine(line);
        free(line);
        if (item == NULL)
            continue;

        input_item_node_AppendItem(subitems, item);
        input_item_Release(item);
    }

    return VLC_SUCCESS;
}