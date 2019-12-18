#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  webvtt_dom_node_t ;
struct TYPE_23__ {struct TYPE_23__* p_next; } ;
typedef  TYPE_3__ vlc_css_rule_t ;
struct TYPE_22__ {TYPE_3__* p_first; } ;
struct TYPE_24__ {TYPE_2__ rules; } ;
typedef  TYPE_4__ vlc_css_parser_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {scalar_t__ stream; scalar_t__ ptr; int /*<<< orphan*/  length; } ;
struct parser_ctx {TYPE_11__ css; TYPE_7__* p_region; TYPE_5__* p_dec; } ;
typedef  enum webvtt_header_line_e { ____Placeholder_webvtt_header_line_e } webvtt_header_line_e ;
struct TYPE_25__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_26__ {TYPE_3__* p_css_rules; TYPE_1__* p_root; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_27__ {scalar_t__ psz_id; int /*<<< orphan*/ * p_parent; } ;
struct TYPE_21__ {int /*<<< orphan*/  p_child; } ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int WEBVTT_HEADER_REGION ; 
 int WEBVTT_HEADER_STYLE ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_css_parser_Clean (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_css_parser_Debug (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_css_parser_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_css_parser_ParseBytes (TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_memstream_close (TYPE_11__*) ; 
 int /*<<< orphan*/  vlc_memstream_open (TYPE_11__*) ; 
 int /*<<< orphan*/  vlc_memstream_putc (TYPE_11__*,char) ; 
 int /*<<< orphan*/  vlc_memstream_puts (TYPE_11__*,char const*) ; 
 int /*<<< orphan*/  webvtt_domnode_AppendLast (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  webvtt_region_Delete (TYPE_7__*) ; 
 TYPE_7__* webvtt_region_New () ; 
 int /*<<< orphan*/  webvtt_region_Parse (TYPE_7__*,char*) ; 

__attribute__((used)) static void ParserHeaderHandler( void *priv, enum webvtt_header_line_e s,
                                 bool b_new, const char *psz_line )
{
    struct parser_ctx *ctx = (struct parser_ctx *)priv;
    decoder_t *p_dec = ctx->p_dec;
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( b_new || !psz_line /* commit */ )
    {
        if( ctx->p_region )
        {
            if( ctx->p_region->psz_id )
            {
                webvtt_domnode_AppendLast( &p_sys->p_root->p_child, ctx->p_region );
                ctx->p_region->p_parent = (webvtt_dom_node_t *) p_sys->p_root;
                msg_Dbg( p_dec, "added new region %s", ctx->p_region->psz_id );
            }
            /* incomplete region decl (no id at least) */
            else webvtt_region_Delete( ctx->p_region );
            ctx->p_region = NULL;
        }
#ifdef HAVE_CSS
        else if( ctx->css.stream )
        {
            if( vlc_memstream_close( &ctx->css ) == VLC_SUCCESS )
            {
                vlc_css_parser_t p;
                vlc_css_parser_Init(&p);
                vlc_css_parser_ParseBytes( &p,
                                          (const uint8_t *) ctx->css.ptr,
                                           ctx->css.length );
#  ifdef CSS_PARSER_DEBUG
                vlc_css_parser_Debug( &p );
#  endif
                vlc_css_rule_t **pp_append = &p_sys->p_css_rules;
                while( *pp_append )
                    pp_append = &((*pp_append)->p_next);
                *pp_append = p.rules.p_first;
                p.rules.p_first = NULL;

                vlc_css_parser_Clean(&p);
                free( ctx->css.ptr );
            }
        }
#endif

        if( !psz_line )
            return;

        if( b_new )
        {
            if( s == WEBVTT_HEADER_REGION )
                ctx->p_region = webvtt_region_New();
#ifdef HAVE_CSS
            else if( s == WEBVTT_HEADER_STYLE )
                (void) vlc_memstream_open( &ctx->css );
#endif
            return;
        }
    }

    if( s == WEBVTT_HEADER_REGION && ctx->p_region )
        webvtt_region_Parse( ctx->p_region, (char*) psz_line );
#ifdef HAVE_CSS
    else if( s == WEBVTT_HEADER_STYLE && ctx->css.stream )
    {
        vlc_memstream_puts( &ctx->css, psz_line );
        vlc_memstream_putc( &ctx->css, '\n' );
    }
#endif
}