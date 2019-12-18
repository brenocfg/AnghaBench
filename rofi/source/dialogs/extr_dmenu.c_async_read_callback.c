#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  scalar_t__ gpointer ;
struct TYPE_5__ {int /*<<< orphan*/  cancel; int /*<<< orphan*/  separator; int /*<<< orphan*/  data_input_stream; } ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int /*<<< orphan*/  GError ;
typedef  int /*<<< orphan*/  GDataInputStream ;
typedef  int /*<<< orphan*/  GAsyncResult ;
typedef  TYPE_1__ DmenuModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  G_INPUT_STREAM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_PRIORITY_LOW ; 
 int /*<<< orphan*/  async_close_callback ; 
 int /*<<< orphan*/  g_cancellable_is_cancelled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_data_input_stream_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_data_input_stream_read_upto_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__),TYPE_1__*) ; 
 char* g_data_input_stream_read_upto_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_input_stream_close_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  read_add (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_get_active () ; 
 int /*<<< orphan*/  rofi_view_reload () ; 
 int /*<<< orphan*/  rofi_view_set_overlay (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_read_callback ( GObject *source_object, GAsyncResult *res, gpointer user_data )
{
    GDataInputStream     *stream = (GDataInputStream *) source_object;
    DmenuModePrivateData *pd     = (DmenuModePrivateData *) user_data;
    gsize                len;
    char                 *data = g_data_input_stream_read_upto_finish ( stream, res, &len, NULL );
    if ( data != NULL ) {
        // Absorb separator, already in buffer so should not block.
        g_data_input_stream_read_byte ( stream, NULL, NULL );
        read_add ( pd, data, len );
        g_free ( data );
        rofi_view_reload ();

        g_data_input_stream_read_upto_async ( pd->data_input_stream, &( pd->separator ), 1, G_PRIORITY_LOW, pd->cancel,
                                              async_read_callback, pd );
        return;
    }
    else {
        GError *error = NULL;
        // Absorb separator, already in buffer so should not block.
        // If error == NULL end of stream..
        g_data_input_stream_read_byte ( stream, NULL, &error );
        if (  error == NULL ) {
            // Add empty line.
            read_add ( pd, "", 0 );
            rofi_view_reload ();

            g_data_input_stream_read_upto_async ( pd->data_input_stream, &( pd->separator ), 1, G_PRIORITY_LOW, pd->cancel,
                                                  async_read_callback, pd );
            return;
        }
        else {
            g_error_free ( error );
        }
    }
    if ( !g_cancellable_is_cancelled ( pd->cancel ) ) {
        // Hack, don't use get active.
        g_debug ( "Clearing overlay" );
        rofi_view_set_overlay ( rofi_view_get_active (), NULL );
        g_input_stream_close_async ( G_INPUT_STREAM ( stream ), G_PRIORITY_LOW, pd->cancel, async_close_callback, pd );
    }
}