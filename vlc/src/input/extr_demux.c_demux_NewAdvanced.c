#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_demux_private {int /*<<< orphan*/ * module; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_8__ {char const* psz_name; char const* psz_location; char* psz_filepath; int b_preparsing; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * pf_control; int /*<<< orphan*/ * pf_demux; int /*<<< orphan*/ * out; int /*<<< orphan*/ * s; int /*<<< orphan*/ * psz_url; int /*<<< orphan*/ * p_input_item; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 char* DemuxNameFromExtension (char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_DestroyDemux ; 
 char* demux_NameFromMimeType (char*) ; 
 int /*<<< orphan*/  demux_Probe ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_path (char const*) ; 
 int /*<<< orphan*/ * input_GetItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  stream_CommonDelete (TYPE_1__*) ; 
 char* stream_MimeType (int /*<<< orphan*/ *) ; 
 char* strrchr (char*,char) ; 
 char* strstr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_module_load (TYPE_1__*,char*,char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* vlc_stream_CustomNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 struct vlc_demux_private* vlc_stream_Private (TYPE_1__*) ; 

demux_t *demux_NewAdvanced( vlc_object_t *p_obj, input_thread_t *p_input,
                            const char *psz_demux, const char *url,
                            stream_t *s, es_out_t *out, bool b_preparsing )
{
    struct vlc_demux_private *priv;
    demux_t *p_demux = vlc_stream_CustomNew(p_obj, demux_DestroyDemux,
                                            sizeof (*priv), "demux");

    if (unlikely(p_demux == NULL))
        return NULL;

    assert(s != NULL);
    priv = vlc_stream_Private(p_demux);

    if (!strcasecmp( psz_demux, "any" ) || !psz_demux[0])
    {   /* Look up demux by mime-type for hard to detect formats */
        char *type = stream_MimeType( s );
        if( type != NULL )
        {
            psz_demux = demux_NameFromMimeType( type );
            free( type );
        }
    }

    p_demux->p_input_item = p_input ? input_GetItem(p_input) : NULL;
    p_demux->psz_name = strdup( psz_demux );
    if (unlikely(p_demux->psz_name == NULL))
        goto error;

    p_demux->psz_url = strdup(url);
    if (unlikely(p_demux->psz_url == NULL))
        goto error;

    const char *p = strstr(p_demux->psz_url, "://");
    p_demux->psz_location = (p != NULL) ? (p + 3) : "";
    p_demux->psz_filepath = get_path(p_demux->psz_location); /* parse URL */

    if( !b_preparsing )
        msg_Dbg( p_obj, "creating demux \"%s\", URL: %s, path: %s",
                 psz_demux, url, p_demux->psz_filepath );

    p_demux->s              = s;
    p_demux->out            = out;
    p_demux->b_preparsing   = b_preparsing;

    p_demux->pf_demux   = NULL;
    p_demux->pf_control = NULL;
    p_demux->p_sys      = NULL;

    const char *psz_module = NULL;

    if( !strcmp( p_demux->psz_name, "any" ) && p_demux->psz_filepath )
    {
        char const* psz_ext = strrchr( p_demux->psz_filepath, '.' );

        if( psz_ext )
            psz_module = DemuxNameFromExtension( psz_ext + 1, b_preparsing );
    }

    if( psz_module == NULL )
        psz_module = p_demux->psz_name;

    priv->module = vlc_module_load(p_demux, "demux", psz_module,
        !strcmp(psz_module, p_demux->psz_name), demux_Probe, p_demux);

    if (priv->module == NULL)
    {
        free( p_demux->psz_filepath );
        goto error;
    }

    return p_demux;
error:
    free( p_demux->psz_name );
    stream_CommonDelete( p_demux );
    return NULL;
}