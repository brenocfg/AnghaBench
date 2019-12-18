#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_6__ {int /*<<< orphan*/  cancel; int /*<<< orphan*/  separator; int /*<<< orphan*/  data_input_stream; int /*<<< orphan*/  input_stream; } ;
typedef  TYPE_1__ DmenuModePrivateData ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  G_INPUT_STREAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_PRIORITY_LOW ; 
 int TRUE ; 
 int /*<<< orphan*/  async_close_callback ; 
 int /*<<< orphan*/  async_read_callback ; 
 int /*<<< orphan*/  g_data_input_stream_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* g_data_input_stream_read_upto (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_data_input_stream_read_upto_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_input_stream_close_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  read_add (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_dmenu_async ( DmenuModePrivateData *pd, int sync_pre_read )
{
    while ( sync_pre_read-- ) {
        gsize len   = 0;
        char  *data = g_data_input_stream_read_upto ( pd->data_input_stream, &( pd->separator ), 1, &len, NULL, NULL );
        if ( data == NULL ) {
            g_input_stream_close_async ( G_INPUT_STREAM ( pd->input_stream ), G_PRIORITY_LOW, pd->cancel, async_close_callback, pd );
            return FALSE;
        }
        g_data_input_stream_read_byte ( pd->data_input_stream, NULL, NULL );
        read_add ( pd, data, len );
        g_free ( data );
    }
    g_data_input_stream_read_upto_async ( pd->data_input_stream, &( pd->separator ), 1, G_PRIORITY_LOW, pd->cancel,
                                          async_read_callback, pd );
    return TRUE;
}