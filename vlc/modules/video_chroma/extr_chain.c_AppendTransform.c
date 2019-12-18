#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int video_transform_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  filter_chain_t ;
struct TYPE_6__ {int /*<<< orphan*/  orientation; } ;
struct TYPE_7__ {TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
typedef  int /*<<< orphan*/  config_chain_t ;

/* Variables and functions */
#define  TRANSFORM_ANTI_TRANSPOSE 134 
#define  TRANSFORM_HFLIP 133 
#define  TRANSFORM_R180 132 
#define  TRANSFORM_R270 131 
#define  TRANSFORM_R90 130 
#define  TRANSFORM_TRANSPOSE 129 
#define  TRANSFORM_VFLIP 128 
 char* config_ChainCreate (char**,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_chain_AppendFilter (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int video_format_GetTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static filter_t * AppendTransform( filter_chain_t *p_chain, const es_format_t *p_fmt1,
                                   const es_format_t *p_fmt2 )
{
    video_transform_t transform = video_format_GetTransform(p_fmt1->video.orientation, p_fmt2->video.orientation);

    const char *type;

    switch ( transform ) {

        case TRANSFORM_R90:
            type = "90";
            break;
        case TRANSFORM_R180:
            type = "180";
            break;
        case TRANSFORM_R270:
            type = "270";
            break;
        case TRANSFORM_HFLIP:
            type = "hflip";
            break;
        case TRANSFORM_VFLIP:
            type = "vflip";
            break;
        case TRANSFORM_TRANSPOSE:
            type = "transpose";
            break;
        case TRANSFORM_ANTI_TRANSPOSE:
            type = "antitranspose";
            break;
        default:
            type = NULL;
            break;
    }

    if( !type )
        return NULL;

    config_chain_t *cfg;
    char *name;
    char config[100];
    snprintf( config, 100, "transform{type=%s}", type );
    char *next = config_ChainCreate( &name, &cfg, config );

    filter_t *p_filter = filter_chain_AppendFilter( p_chain, name, cfg, p_fmt2 );

    config_ChainDestroy(cfg);
    free(name);
    free(next);

    return p_filter;
}