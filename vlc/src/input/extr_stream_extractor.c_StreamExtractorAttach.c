#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * source; int /*<<< orphan*/  identifier; } ;
struct stream_extractor_private {int /*<<< orphan*/ * wrapper; int /*<<< orphan*/  module; void* object; TYPE_1__ directory; int /*<<< orphan*/ * pf_clean; int /*<<< orphan*/  pf_init; TYPE_1__ extractor; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 void* VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  module_need (void*,char const*,char const*,int) ; 
 scalar_t__ se_AttachWrapper (struct stream_extractor_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * se_CleanStream ; 
 int /*<<< orphan*/  se_InitDirectory ; 
 int /*<<< orphan*/  se_InitStream ; 
 int /*<<< orphan*/  se_Release (struct stream_extractor_private*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 
 struct stream_extractor_private* vlc_custom_create (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  vlc_object_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
StreamExtractorAttach( stream_t** source, char const* identifier,
    char const* module_name )
{
    const bool extractor = identifier != NULL;
    char const* capability = extractor ? "stream_extractor"
                                       : "stream_directory";

    struct stream_extractor_private* priv = vlc_custom_create(
        vlc_object_parent(*source), sizeof( *priv ), capability );

    if( unlikely( !priv ) )
        return VLC_ENOMEM;

    if( extractor )
    {
        priv->object = VLC_OBJECT( &priv->extractor );

        priv->pf_init = se_InitStream;
        priv->pf_clean = se_CleanStream;

        priv->extractor.source = *source;
        priv->extractor.identifier = strdup( identifier );

        if( unlikely( !priv->extractor.identifier ) )
            goto error;
    }
    else
    {
        priv->object = VLC_OBJECT( &priv->directory );

        priv->pf_init = se_InitDirectory;
        priv->pf_clean = NULL;

        priv->directory.source = *source;
    }

    priv->module = module_need( priv->object, capability, module_name, true );

    if( !priv->module || se_AttachWrapper( priv, *source ) )
        goto error;

    *source = priv->wrapper;
    return VLC_SUCCESS;

error:
    se_Release( priv );
    return VLC_EGENERIC;
}