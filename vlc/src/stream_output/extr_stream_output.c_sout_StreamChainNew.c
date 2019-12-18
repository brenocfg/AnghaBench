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
typedef  int /*<<< orphan*/  vlc_array_t ;
typedef  char sout_stream_t ;
typedef  int /*<<< orphan*/  sout_instance_t ;
typedef  char config_chain_t ;

/* Variables and functions */
 char* config_ChainCreate (char**,char**,char*) ; 
 int /*<<< orphan*/  config_ChainDestroy (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sout_StreamDelete (char*) ; 
 char* sout_StreamNew (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_array_append_or_abort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 int vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 char* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

sout_stream_t *sout_StreamChainNew(sout_instance_t *p_sout, const char *psz_chain,
                                sout_stream_t *p_next, sout_stream_t **pp_last)
{
    if(!psz_chain || !*psz_chain)
    {
        if(pp_last) *pp_last = NULL;
        return p_next;
    }

    char *psz_parser = strdup(psz_chain);
    if(!psz_parser)
        return NULL;

    vlc_array_t cfg, name;
    vlc_array_init(&cfg);
    vlc_array_init(&name);

    /* parse chain */
    while(psz_parser)
    {
        config_chain_t *p_cfg;
        char *psz_name;
        char *psz_rest_chain = config_ChainCreate( &psz_name, &p_cfg, psz_parser );
        free( psz_parser );
        psz_parser = psz_rest_chain;

        vlc_array_append_or_abort(&cfg, p_cfg);
        vlc_array_append_or_abort(&name, psz_name);
    }

    size_t i = vlc_array_count(&name);
    vlc_array_t module;
    vlc_array_init(&module);
    while(i--)
    {
        p_next = sout_StreamNew( p_sout, vlc_array_item_at_index(&name, i),
            vlc_array_item_at_index(&cfg, i), p_next);

        if(!p_next)
            goto error;

        if(i == vlc_array_count(&name) - 1 && pp_last)
            *pp_last = p_next;   /* last module created in the chain */

        vlc_array_append_or_abort(&module, p_next);
    }

    vlc_array_clear(&name);
    vlc_array_clear(&cfg);
    vlc_array_clear(&module);

    return p_next;

error:

    i++;    /* last module couldn't be created */

    /* destroy all modules created, starting with the last one */
    int modules = vlc_array_count(&module);
    while(modules--)
        sout_StreamDelete(vlc_array_item_at_index(&module, modules));
    vlc_array_clear(&module);

    /* then destroy all names and config which weren't destroyed by
     * sout_StreamDelete */
    while(i--)
    {
        free(vlc_array_item_at_index(&name, i));
        config_ChainDestroy(vlc_array_item_at_index(&cfg, i));
    }
    vlc_array_clear(&name);
    vlc_array_clear(&cfg);

    return NULL;
}