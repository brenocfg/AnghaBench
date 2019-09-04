#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_19__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_29__ {int state; char prev; int saved_comment; int looked; size_t saved; void* tag; int count; int /*<<< orphan*/  tout; int /*<<< orphan*/  css_enable; int /*<<< orphan*/  js_enable; } ;
typedef  TYPE_1__ ngx_http_trim_ctx_t ;
struct TYPE_30__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_31__ {TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_32__ {char* pos; char* last; int /*<<< orphan*/  temporary; int /*<<< orphan*/  last_in_chain; int /*<<< orphan*/  last_buf; int /*<<< orphan*/  flush; int /*<<< orphan*/  sync; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_37__ {char* data; int len; } ;
struct TYPE_36__ {int len; char* data; } ;
struct TYPE_35__ {char* data; int len; } ;
struct TYPE_34__ {int len; char* data; } ;
struct TYPE_33__ {char* data; int len; } ;
struct TYPE_28__ {char* data; int len; } ;
struct TYPE_27__ {char* data; int len; } ;
struct TYPE_26__ {char* data; int len; } ;
struct TYPE_25__ {char* data; int len; } ;
struct TYPE_24__ {size_t len; char* data; } ;
struct TYPE_23__ {char* data; } ;
struct TYPE_22__ {size_t len; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 size_t NGX_HTTP_TRIM_SAVE_HACKCSS ; 
 void* NGX_HTTP_TRIM_SAVE_JAVASCRIPT ; 
 size_t NGX_HTTP_TRIM_SAVE_JSCSS ; 
 void* NGX_HTTP_TRIM_SAVE_SLASH ; 
 void* NGX_HTTP_TRIM_SAVE_SPACE ; 
 void* NGX_HTTP_TRIM_TAG_PRE ; 
 void* NGX_HTTP_TRIM_TAG_SCRIPT ; 
 void* NGX_HTTP_TRIM_TAG_STYLE ; 
 void* NGX_HTTP_TRIM_TAG_TEXTAREA ; 
 int /*<<< orphan*/  NGX_OK ; 
 size_t ngx_buf_size (TYPE_4__*) ; 
 char* ngx_cpymem (char*,char*,size_t) ; 
 TYPE_4__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 TYPE_19__ ngx_http_trim_comment ; 
 TYPE_18__ ngx_http_trim_comment_ie ; 
 TYPE_17__ ngx_http_trim_comment_ie_end ; 
 TYPE_13__ ngx_http_trim_pre ; 
 TYPE_12__ ngx_http_trim_saved_css_hack ; 
 TYPE_11__ ngx_http_trim_saved_html ; 
 TYPE_10__ ngx_http_trim_saved_jscss ; 
 TYPE_9__ ngx_http_trim_script ; 
 TYPE_8__ ngx_http_trim_script_js ; 
 TYPE_7__ ngx_http_trim_style ; 
 TYPE_6__ ngx_http_trim_style_css ; 
 TYPE_5__ ngx_http_trim_textarea ; 
 char ngx_tolower (char) ; 
 int* trim_css_prefix ; 
 int* trim_js_prefix ; 
#define  trim_state_comment_begin 186 
#define  trim_state_comment_end 185 
#define  trim_state_comment_hack_begin 184 
#define  trim_state_comment_hack_end 183 
#define  trim_state_comment_ie_begin 182 
#define  trim_state_comment_ie_end 181 
#define  trim_state_tag 180 
#define  trim_state_tag_attribute 179 
#define  trim_state_tag_double_quote 178 
#define  trim_state_tag_pre 177 
#define  trim_state_tag_pre_angle 176 
#define  trim_state_tag_pre_begin 175 
#define  trim_state_tag_pre_end 174 
#define  trim_state_tag_pre_nest 173 
#define  trim_state_tag_s 172 
#define  trim_state_tag_script_begin 171 
#define  trim_state_tag_script_end 170 
#define  trim_state_tag_script_js_comment_begin 169 
#define  trim_state_tag_script_js_double_quote 168 
#define  trim_state_tag_script_js_double_quote_esc 167 
#define  trim_state_tag_script_js_end 166 
#define  trim_state_tag_script_js_multi_comment 165 
#define  trim_state_tag_script_js_multi_comment_end 164 
#define  trim_state_tag_script_js_re 163 
#define  trim_state_tag_script_js_re_begin 162 
#define  trim_state_tag_script_js_re_esc 161 
#define  trim_state_tag_script_js_single_comment 160 
#define  trim_state_tag_script_js_single_comment_end 159 
#define  trim_state_tag_script_js_single_quote 158 
#define  trim_state_tag_script_js_single_quote_esc 157 
#define  trim_state_tag_script_js_text 156 
#define  trim_state_tag_script_js_whitespace 155 
#define  trim_state_tag_single_quote 154 
#define  trim_state_tag_style_begin 153 
#define  trim_state_tag_style_css_comment 152 
#define  trim_state_tag_style_css_comment_begin 151 
#define  trim_state_tag_style_css_comment_begin_empty 150 
#define  trim_state_tag_style_css_comment_begin_hack 149 
#define  trim_state_tag_style_css_comment_empty 148 
#define  trim_state_tag_style_css_comment_end 147 
#define  trim_state_tag_style_css_comment_hack 146 
#define  trim_state_tag_style_css_comment_hack_text 145 
#define  trim_state_tag_style_css_comment_hack_text_begin 144 
#define  trim_state_tag_style_css_comment_hack_text_end 143 
#define  trim_state_tag_style_css_comment_hack_text_last 142 
#define  trim_state_tag_style_css_double_quote 141 
#define  trim_state_tag_style_css_double_quote_esc 140 
#define  trim_state_tag_style_css_end 139 
#define  trim_state_tag_style_css_single_quote 138 
#define  trim_state_tag_style_css_single_quote_esc 137 
#define  trim_state_tag_style_css_text 136 
#define  trim_state_tag_style_css_whitespace 135 
#define  trim_state_tag_style_end 134 
#define  trim_state_tag_text 133 
#define  trim_state_tag_textarea_begin 132 
#define  trim_state_tag_textarea_end 131 
#define  trim_state_tag_whitespace 130 
#define  trim_state_text 129 
#define  trim_state_text_whitespace 128 

__attribute__((used)) static ngx_int_t
ngx_http_trim_parse(ngx_http_request_t *r, ngx_chain_t *in,
    ngx_http_trim_ctx_t *ctx)
{
    u_char                    *read, *write, ch, look;
    size_t                     size;
    ngx_buf_t                 *b, *buf;

    b = in->buf;
    buf = in->buf;
    size = ngx_buf_size(buf);

    if (size == 0) {
        return NGX_OK;
    }

    if (!buf->temporary) {
        b = ngx_create_temp_buf(r->pool, size);
        if (b == NULL) {
            return NGX_ERROR;
        }

        b->sync = buf->sync;
        b->flush = buf->flush;
        b->last_buf = buf->last_buf;
        b->last_in_chain = buf->last_in_chain;
    }

    for (write = b->pos, read = buf->pos; read < buf->last; read++) {

        ch = ngx_tolower(*read);

        switch (ctx->state) {

        case trim_state_text:
            switch (ch) {
            case '\r':
                continue;
            case '\n':
                ctx->state = trim_state_text_whitespace;
                if (ctx->prev == '\n') {
                    continue;

                } else {
                    break;
                }
            case '\t':
            case ' ':
                ctx->state = trim_state_text_whitespace;
                continue;
            case '<':
                ctx->state = trim_state_tag;
                ctx->saved_comment = 1;
                continue;
            default:
                break;
            }
            break;

        case trim_state_tag:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                ctx->state = trim_state_text_whitespace;
                break;
            case '!':
                ctx->state = trim_state_comment_begin;
                ctx->looked = 0;        /* --> */
                ctx->saved_comment++;
                continue;
            case 'p':
                ctx->state = trim_state_tag_pre_begin;
                ctx->looked = 3;        /* </pre> */
                break;
            case 't':
                ctx->state = trim_state_tag_textarea_begin;
                ctx->looked = 3;       /* </textarea> */
                break;
            case 's':
                ctx->state = trim_state_tag_s;
                break;
            case '<':
                break;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                if ((ch >= 'a' && ch <= 'z') || ch == '/') {
                    ctx->state = trim_state_tag_text;

                } else {
                    ctx->state = trim_state_text;
                }
                break;
            }

            if ((size_t) (read - buf->pos) >= ctx->saved_comment) {
                write = ngx_cpymem(write, ngx_http_trim_saved_html.data,
                                   ctx->saved_comment);

            } else {
                ctx->saved = ctx->saved_comment;
            }

            if (ctx->state == trim_state_tag
                || ctx->state == trim_state_text_whitespace)
            {
               ctx->prev = '<';
               continue;
            }

            break;

        case trim_state_tag_text:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                ctx->state = trim_state_tag_whitespace;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_attribute:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->prev != '=') {
                    ctx->state = trim_state_tag_whitespace;
                }
                continue;
            case '\'':
                ctx->state = trim_state_tag_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_double_quote;
                break;
            case '>':
                if (ctx->tag == NGX_HTTP_TRIM_TAG_PRE) {
                    ctx->state = trim_state_tag_pre;

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_TEXTAREA) {
                    ctx->state = trim_state_tag_textarea_end;

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_SCRIPT) {
                    if (ctx->js_enable
                        && ctx->looked == ngx_http_trim_script_js.len)
                    {
                        ctx->state = trim_state_tag_script_js_text;

                    } else {
                        ctx->state = trim_state_tag_script_end;
                    }

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_STYLE) {
                    if (ctx->css_enable
                        && ctx->looked == ngx_http_trim_style_css.len)
                    {
                        ctx->state = trim_state_tag_style_css_text;

                    } else {
                        ctx->state = trim_state_tag_style_end;
                    }

                } else {
                    ctx->state = trim_state_text;
                }

                ctx->tag = 0;
                ctx->looked = 0;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_s:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                ctx->state = trim_state_tag_whitespace;
                continue;
            case 't':
                ctx->state = trim_state_tag_style_begin;
                ctx->looked = 4;    /* </style> */
                break;
            case 'c':
                ctx->state = trim_state_tag_script_begin;
                ctx->looked = 4;    /* </script> */
                break;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }
            break;

        case trim_state_comment_begin:
            look = ngx_http_trim_comment.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_comment.len - 1) { /* --> */
                    ctx->state = trim_state_comment_hack_begin;
                    ctx->looked = 0;
                }

                ctx->saved_comment++;
                continue;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                ctx->state = trim_state_tag_whitespace;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }

            if ((size_t) (read - buf->pos) >= ctx->saved_comment) {
                write = ngx_cpymem(write, ngx_http_trim_saved_html.data,
                                   ctx->saved_comment);

            } else {
                ctx->saved = ctx->saved_comment;
            }

            break;

        case trim_state_comment_hack_begin:
            switch (ch) {
            case '#':
                ctx->state = trim_state_comment_hack_end;
                ctx->looked = 0;
                break;
            case 'e':
                ctx->state = trim_state_comment_hack_end;
                ctx->looked = 0;
                break;
            case '[':
                ctx->state = trim_state_comment_ie_begin;
                ctx->looked = 1;
                ctx->saved_comment++;
                continue;
            case '-':
                ctx->state = trim_state_comment_end;
                ctx->looked = 1;
                continue;
            default:
                ctx->state = trim_state_comment_end;
                ctx->looked = 0;
                continue;
            }

            if ((size_t) (read - buf->pos) >= ctx->saved_comment) {
                write = ngx_cpymem(write, ngx_http_trim_saved_html.data,
                                   ctx->saved_comment);

            } else {
                ctx->saved = ctx->saved_comment;
            }

            break;

        case trim_state_comment_ie_begin:
            look = ngx_http_trim_comment_ie.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_comment_ie.len) { /* [if */
                    ctx->state = trim_state_comment_ie_end;
                    ctx->looked = 0;

                    if ((size_t) (read - buf->pos) >= ctx->saved_comment) {
                        write = ngx_cpymem(write, ngx_http_trim_saved_html.data,
                                           ctx->saved_comment);

                    } else {
                         ctx->saved = ctx->saved_comment;
                    }

                    break;
                }

                ctx->saved_comment++;
                continue;
            }

            switch (ch) {
            case '-':
                ctx->state = trim_state_comment_end;
                ctx->looked = 1;
                break;
            default:
                ctx->state = trim_state_comment_end;
                ctx->looked = 0;
                break;
            }

            continue;

        case trim_state_tag_pre_begin:
            look = ngx_http_trim_pre.data[ctx->looked++];    /* <pre> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_pre.len) {
                    ctx->state = trim_state_tag_pre;
                    ctx->count = 1;
                    ctx->looked = 0;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_pre.len) {
                    ctx->tag = NGX_HTTP_TRIM_TAG_PRE;
                    ctx->count = 1;
                }

                ctx->state = trim_state_tag_whitespace;
                ctx->looked = 0;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }
            break;

        case trim_state_tag_textarea_begin:
            look = ngx_http_trim_textarea.data[ctx->looked++]; /* <textarea> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_textarea.len) {
                    ctx->state = trim_state_tag_textarea_end;
                    ctx->looked = 0;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_textarea.len) {
                    ctx->tag = NGX_HTTP_TRIM_TAG_TEXTAREA;
                }

                ctx->state = trim_state_tag_whitespace;
                ctx->looked = 0;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }
            break;

        case trim_state_tag_script_begin:
            look = ngx_http_trim_script.data[ctx->looked++];    /* <script> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_script.len) {
                    if (ctx->js_enable) {
                        ctx->state = trim_state_tag_script_js_text;

                    } else {
                        ctx->state = trim_state_tag_script_end;
                    }

                    ctx->looked = 0;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->tag = NGX_HTTP_TRIM_TAG_SCRIPT;
                }

                ctx->state = trim_state_tag_whitespace;
                ctx->looked = 0;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }
            break;

        case trim_state_tag_script_js_text:
            switch (ch) {
            case '\r':
                continue;
            case '\n':
            case '\t':
            case ' ':
                ctx->state = trim_state_tag_script_js_whitespace;
                if (trim_js_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f))
                    || ctx->prev == ch)
                {
                    continue;

                } else {
                    break;
                }
            case '\'':
                ctx->state = trim_state_tag_script_js_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_script_js_double_quote;
                break;
            case '<':
                ctx->state = trim_state_tag_script_js_end;
                ctx->looked = 1;
                break;
            case '/':
                if (trim_js_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f))
                    || ctx->prev == '+' || ctx->prev == '-')
                {
                    ctx->state = trim_state_tag_script_js_re_begin;

                } else {
                    ctx->state = trim_state_tag_script_js_comment_begin;
                }
                continue;
            default:
                break;
            }
            break;

        case trim_state_tag_script_js_single_quote:
            switch (ch) {
            case '\\':
                ctx->state = trim_state_tag_script_js_single_quote_esc;
                break;
            case '\'':
                ctx->state = trim_state_tag_script_js_text;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_script_js_double_quote:
            switch (ch) {
            case '\\':
                ctx->state = trim_state_tag_script_js_double_quote_esc;
                break;
            case '"':
                ctx->state = trim_state_tag_script_js_text;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_script_js_single_quote_esc:
            ctx->state = trim_state_tag_script_js_single_quote;
            break;

        case trim_state_tag_script_js_double_quote_esc:
            ctx->state = trim_state_tag_script_js_double_quote;
            break;

        case trim_state_tag_script_js_re_begin:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_script_js_single_comment;
                continue;
            case '*':
                ctx->state = trim_state_tag_script_js_multi_comment;
                continue;
            case '\\':
                ctx->state = trim_state_tag_script_js_re_esc;
                if (read > buf->pos) {
                    *write++ = '/';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SLASH;
                }
                break;
            default:
                ctx->state = trim_state_tag_script_js_re;
                if (read > buf->pos) {
                    *write++ = '/';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SLASH;
                }
                break;
             }
             break;

        case trim_state_tag_script_js_re:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_script_js_text;
                break;
            case '\\':
                ctx->state = trim_state_tag_script_js_re_esc;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_script_js_re_esc:
            ctx->state = trim_state_tag_script_js_re;
            break;

        case trim_state_tag_script_js_comment_begin:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_script_js_single_comment;
                continue;
            case '*':
                ctx->state = trim_state_tag_script_js_multi_comment;
                continue;
            default:
                ctx->state = trim_state_tag_script_js_text;
                if (read > buf->pos) {
                    *write++ = '/';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SLASH;
                }
                break;
             }
             break;

        case trim_state_tag_script_js_single_comment:
            switch (ch) {
            case '<':
                ctx->looked = 1;
                ctx->state = trim_state_tag_script_js_single_comment_end;
                continue;
            case '\n':
                ctx->state = trim_state_tag_script_js_text;
                if (trim_js_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f))
                    || ctx->prev == ch)
                {
                    continue;

                } else {
                    break;
                }
            default:
                continue;
            }
            break;

        case trim_state_tag_script_js_single_comment_end:
            look = ngx_http_trim_script.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_text;
                    ctx->looked = 0;

                    if ((size_t) (read - buf->pos)
                        >= ngx_http_trim_script.len - 1)
                    {
                        write = ngx_cpymem(write, ngx_http_trim_script.data,
                                           ngx_http_trim_script.len - 1);

                    } else {
                        ctx->saved = NGX_HTTP_TRIM_SAVE_JAVASCRIPT;
                    }

                    break;
                }

                continue;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_tag_whitespace;

                    if ((size_t) (read - buf->pos)
                        >= ngx_http_trim_script.len - 1)
                    {
                        write = ngx_cpymem(write, ngx_http_trim_script.data,
                                           ngx_http_trim_script.len - 1);

                    } else {
                        ctx->saved = NGX_HTTP_TRIM_SAVE_JAVASCRIPT;
                    }

                    ctx->prev = 't';
                    ctx->looked = 0;
                    continue;
                }
                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->state = trim_state_tag_script_js_single_comment;
                ctx->looked = 0;
                break;
            }

            continue;

        case trim_state_tag_script_js_multi_comment:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_script_js_multi_comment_end;
                break;
            default:
                break;
            }
            continue;

        case trim_state_tag_script_js_multi_comment_end:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_script_js_text;
                break;
            case '*':
                break;
            default:
                ctx->state = trim_state_tag_script_js_multi_comment;
                break;
            }
            continue;

        case trim_state_tag_script_end:
            look = ngx_http_trim_script.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_tag_script_js_end:
            look = ngx_http_trim_script.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_script.len) {
                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->state = trim_state_tag_script_js_text;
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_tag_script_js_whitespace:
            switch (ch) {
            case '\n':
                if (trim_js_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f))
                    || ctx->prev == ch)
                {
                    continue;

                } else {
                    break;
                }
            case '\r':
            case '\t':
            case ' ':
                 continue;
            case '\'':
                ctx->state = trim_state_tag_script_js_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_script_js_double_quote;
                break;
            case '<':
                ctx->state = trim_state_tag_script_js_end;
                ctx->looked = 1;
                break;
            case '/':
                if (trim_js_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f))
                    || ctx->prev == '+' || ctx->prev == '-')
                {
                    ctx->state = trim_state_tag_script_js_re_begin;

                } else {
                    ctx->state = trim_state_tag_script_js_comment_begin;
                }
                continue;
            default:
                ctx->state = trim_state_tag_script_js_text;
                break;
            }
            break;

        case trim_state_tag_style_begin:
            look = ngx_http_trim_style.data[ctx->looked++];    /* <style> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_style.len) {
                    if (ctx->css_enable) {
                        ctx->state = trim_state_tag_style_css_text;

                    } else {
                        ctx->state = trim_state_tag_style_end;
                    }

                    ctx->looked = 0;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_style.len) {
                    ctx->tag = NGX_HTTP_TRIM_TAG_STYLE;
                }

                ctx->state = trim_state_tag_whitespace;
                ctx->looked = 0;
                continue;
            case '>':
                ctx->state = trim_state_text;
                break;
            default:
                ctx->state = trim_state_tag_text;
                break;
            }
            break;

        case trim_state_tag_style_css_text:
            switch (ch) {
            case '\r':
                continue;
            case '\n':
            case '\t':
            case ' ':
                if (!(trim_css_prefix[ctx->prev >> 5] & (1 << (ctx->prev & 0x1f)))) {
                    ctx->state = trim_state_tag_style_css_whitespace;
                }
                continue;
            case '\'':
                ctx->state = trim_state_tag_style_css_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_style_css_double_quote;
                break;
            case '<':
                ctx->state = trim_state_tag_style_css_end;
                ctx->looked = 1;
                break;
            case '/':
                ctx->state = trim_state_tag_style_css_comment_begin;
                continue;
            default:
                break;
            }
            break;

        case trim_state_tag_style_css_single_quote:
            switch (ch) {
            case '\\':
                ctx->state = trim_state_tag_style_css_single_quote_esc;
                break;
            case '\'':
                ctx->state = trim_state_tag_style_css_text;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_style_css_double_quote:
            switch (ch) {
            case '\\':
                ctx->state = trim_state_tag_style_css_double_quote_esc;
                break;
            case '"':
                ctx->state = trim_state_tag_style_css_text;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_style_css_single_quote_esc:
            ctx->state = trim_state_tag_style_css_single_quote;
            break;

        case trim_state_tag_style_css_double_quote_esc:
            ctx->state = trim_state_tag_style_css_double_quote;
            break;

        case trim_state_tag_style_css_comment_begin:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_begin_empty;
                continue;
            case '/':
                ctx->state = trim_state_tag_style_css_comment_begin;
                break;
            default:
                ctx->state = trim_state_tag_style_css_text;
                break;
            }

            if (read > buf->pos) {
                *write++ = '/';

            } else {
                ctx->saved = NGX_HTTP_TRIM_SAVE_SLASH;
            }

            if (ch == '/') {
                continue;

            }
            break;

        case trim_state_tag_style_css_comment_begin_empty:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_empty;
                break;
            case '\\':
                ctx->state = trim_state_tag_style_css_comment_begin_hack;
                break;
            default:
                ctx->state = trim_state_tag_style_css_comment;
                break;
            }
            continue;

        case trim_state_tag_style_css_comment:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_end;
                break;
            case '\\':
                ctx->state = trim_state_tag_style_css_comment_begin_hack;
                break;
            default:
                break;
            }
            continue;

        case trim_state_tag_style_css_comment_empty:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_style_css_text;

                if ((size_t) (read - buf->pos)
                    >= ngx_http_trim_saved_jscss.len)
                {
                    write = ngx_cpymem(write, ngx_http_trim_saved_jscss.data,
                                       ngx_http_trim_saved_jscss.len);

                } else {
                     ctx->saved = NGX_HTTP_TRIM_SAVE_JSCSS;
                }
                break;
            case '*':
                ctx->state = trim_state_tag_style_css_comment_end;
                continue;
            case '\\':
                ctx->state = trim_state_tag_style_css_comment_begin_hack;
                continue;
            default:
                ctx->state = trim_state_tag_style_css_comment;
                continue;
            }
            break;

        case trim_state_tag_style_css_comment_begin_hack:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_hack;
                break;
            default:
                ctx->state = trim_state_tag_style_css_comment;
                break;
            }
            continue;

        case trim_state_tag_style_css_comment_hack:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_style_css_comment_hack_text;

                if ((size_t) (read - buf->pos)
                    >= ngx_http_trim_saved_css_hack.len)
                {
                    write = ngx_cpymem(write, ngx_http_trim_saved_css_hack.data,
                                       ngx_http_trim_saved_css_hack.len);

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_HACKCSS;
                }
                break;
            case '*':
                ctx->state = trim_state_tag_style_css_comment_end;
                continue;
            case '\\':
                ctx->state = trim_state_tag_style_css_comment_begin_hack;
                continue;
            default:
                ctx->state = trim_state_tag_style_css_comment;
                continue;
            }
            break;

        case trim_state_tag_style_css_comment_hack_text:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_style_css_comment_hack_text_begin;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_style_css_comment_hack_text_begin:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_hack_text_end;
                break;
            case '/':
                break;
            default:
                ctx->state = trim_state_tag_style_css_comment_hack_text;
                break;
            }
            break;

        case trim_state_tag_style_css_comment_hack_text_end:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_hack_text_last;
                break;
            default:
                continue;
            }
            break;

        case trim_state_tag_style_css_comment_hack_text_last:
            switch (ch) {
            case '*':
                ctx->state = trim_state_tag_style_css_comment_hack_text_last;
                break;
            case '/':
                ctx->state = trim_state_tag_style_css_text;
                break;
            default:
                ctx->state = trim_state_tag_style_css_comment_hack_text_end;
                break;
            }
            break;

        case trim_state_tag_style_css_comment_end:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_style_css_text;
                break;
            case '*':
                break;
            case '\\':
                ctx->state = trim_state_tag_style_css_comment_begin_hack;
                break;
            default:
                ctx->state = trim_state_tag_style_css_comment;
                break;
            }
            continue;

        case trim_state_tag_style_css_whitespace:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                 continue;
            case '\'':
                ctx->state = trim_state_tag_style_css_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_style_css_double_quote;
                break;
            case '<':
                ctx->state = trim_state_tag_style_css_end;
                ctx->looked = 1;
                break;
            case '/':
                ctx->state = trim_state_tag_style_css_comment_begin;
                break;
            default:
                ctx->state = trim_state_tag_style_css_text;
                break;
            }

            if (!(trim_css_prefix[ch >> 5] & (1 << (ch & 0x1f)))) {
                if (read > buf->pos) {
                    *write++ = ' ';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SPACE;
                }
            }

            if (ch == '/') {
                continue;
            }

            break;

        case trim_state_tag_style_end:
            look = ngx_http_trim_style.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_style.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_style.len) {
                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_tag_style_css_end:
            look = ngx_http_trim_style.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_style.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_style.len) {
                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->state = trim_state_tag_style_css_text;
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_comment_end:
            look = ngx_http_trim_comment.data[ctx->looked++];  /* --> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_comment.len) {
                    ctx->state = trim_state_text;
                }
                continue;
            }

            switch (ch) {
            case '-':
                ctx->looked--;
                break;
            default:
                ctx->looked = 0;
                break;
            }
            continue;

        case trim_state_comment_ie_end:        /*  <![endif]-->  */
            look = ngx_http_trim_comment_ie_end.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_comment_ie_end.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_comment_hack_end:
            look = ngx_http_trim_comment.data[ctx->looked++];  /* --> */
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_comment.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '-':
                ctx->looked--;
                break;
            default:
                ctx->looked = 0;
                break;
            }

            break;

        case trim_state_tag_pre:
            switch (ch) {
            case '<':
                ctx->state = trim_state_tag_pre_angle;
                break;
            default:
                break;
            }
            break;

        case trim_state_tag_pre_angle:
            switch (ch) {
            case '/':
                ctx->state = trim_state_tag_pre_end;
                ctx->looked = 2;
                break;
            case 'p':
                ctx->state = trim_state_tag_pre_nest;
                ctx->looked = 3;
                break;
            case '<':
                break;
            default:
                ctx->state = trim_state_tag_pre;
                break;
            }
            break;

        case trim_state_tag_pre_nest:
            look = ngx_http_trim_pre.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_pre.len) {
                    ctx->count++;
                    ctx->state = trim_state_tag_pre;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_pre.len) {
                    ctx->count++;
                    ctx->tag = NGX_HTTP_TRIM_TAG_PRE;
                    ctx->state = trim_state_tag_whitespace;
                    continue;

                } else {
                    ctx->state = trim_state_tag_pre;
                }

                break;
            case '<':
                ctx->state = trim_state_tag_pre_angle;
                break;
            default:
                ctx->state = trim_state_tag_pre;
                break;
            }
            break;

        case trim_state_tag_pre_end:
            look = ngx_http_trim_pre.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_pre.len) {
                    if (--ctx->count > 0) {
                        ctx->state = trim_state_tag_pre;

                    } else {
                        ctx->state = trim_state_text;
                    }
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_pre.len) {
                    if (--ctx->count > 0 ) {
                        ctx->tag = NGX_HTTP_TRIM_TAG_PRE;
                    }

                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->state = trim_state_tag_pre_angle;
                break;
            default:
                ctx->state = trim_state_tag_pre;
                break;
            }
            break;

        case trim_state_tag_textarea_end:
            look = ngx_http_trim_textarea.data[ctx->looked++];
            if (ch == look) {
                if (ctx->looked == ngx_http_trim_textarea.len) {
                    ctx->state = trim_state_text;
                }
                break;
            }

            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                if (ctx->looked == ngx_http_trim_textarea.len) {
                    ctx->state = trim_state_tag_whitespace;
                    ctx->looked = 0;
                    continue;
                }

                ctx->looked = 0;
                break;
            case '<':
                ctx->looked = 1;
                break;
            default:
                ctx->looked = 0;
                break;
            }
            break;

        case trim_state_text_whitespace:
            switch (ch) {
            case '\r':
            case '\t':
            case ' ':
                continue;
            case '\n':
                if (ctx->prev == '\n') {
                    continue;

                } else {
                    break;
                }
            case '<':
                ctx->state = trim_state_tag;
                ctx->saved_comment = 1;
                break;
            default:
                ctx->state = trim_state_text;
                break;
            }

            if (ch != '\n' && ctx->prev != '\n') {
                if (read > buf->pos) {
                    *write++ = ' ';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SPACE;
                }
            }

            if (ch == '<') {
                continue;
            }

            break;

        case trim_state_tag_whitespace:
            switch (ch) {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                continue;
            case '\'':
                ctx->state = trim_state_tag_single_quote;
                break;
            case '"':
                ctx->state = trim_state_tag_double_quote;
                break;
            case '>':
                if (ctx->tag == NGX_HTTP_TRIM_TAG_PRE) {
                    ctx->state = trim_state_tag_pre;

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_TEXTAREA) {
                    ctx->state = trim_state_tag_textarea_end;

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_SCRIPT) {
                    if (ctx->js_enable
                        && ctx->looked == ngx_http_trim_script_js.len)
                    {
                        ctx->state = trim_state_tag_script_js_text;

                    } else {
                        ctx->state = trim_state_tag_script_end;
                    }

                } else if (ctx->tag == NGX_HTTP_TRIM_TAG_STYLE) {
                    if (ctx->css_enable
                        && ctx->looked == ngx_http_trim_style_css.len)
                    {
                        ctx->state = trim_state_tag_style_css_text;

                    } else {
                        ctx->state = trim_state_tag_style_end;
                    }

                } else {
                    ctx->state = trim_state_text;
                }

                ctx->tag = 0;
                ctx->looked = 0;
                break;
            default:
                ctx->state = trim_state_tag_attribute;
                break;
            }

            if (ch != '>' && ch != '=') {
                if (read > buf->pos) {
                    *write++ = ' ';

                } else {
                    ctx->saved = NGX_HTTP_TRIM_SAVE_SPACE;
                }
            }

            break;

        case trim_state_tag_single_quote:
            switch (ch) {
            case '\'':
                ctx->state = trim_state_tag_attribute;
                break;
            default:
                break;
            }

            if (ctx->js_enable && ctx->tag == NGX_HTTP_TRIM_TAG_SCRIPT) {
                if (ctx->looked != ngx_http_trim_script_js.len) {
                    look = ngx_http_trim_script_js.data[ctx->looked++];
                    if (ch != look) {
                        ctx->looked = 0;
                    }
                }
            }

            if (ctx->css_enable && ctx->tag == NGX_HTTP_TRIM_TAG_STYLE) {
                if (ctx->looked != ngx_http_trim_style_css.len) {
                    look = ngx_http_trim_style_css.data[ctx->looked++];
                    if (ch != look) {
                        ctx->looked = 0;
                    }
                }
            }

            break;

        case trim_state_tag_double_quote:
            switch (ch) {
            case '"':
                ctx->state = trim_state_tag_attribute;
                break;
            default:
                break;
            }

            if (ctx->js_enable && ctx->tag == NGX_HTTP_TRIM_TAG_SCRIPT) {
                if (ctx->looked != ngx_http_trim_script_js.len) {
                    look = ngx_http_trim_script_js.data[ctx->looked++];
                    if (ch != look) {
                        ctx->looked = 0;
                    }
                }
            }

            if (ctx->css_enable && ctx->tag == NGX_HTTP_TRIM_TAG_STYLE) {
                if (ctx->looked != ngx_http_trim_style_css.len) {
                    look = ngx_http_trim_style_css.data[ctx->looked++];
                    if (ch != look) {
                        ctx->looked = 0;
                    }
                }
            }

            break;

        default:
            break;
        }

        *write++ = *read;
         ctx->prev = *read;
    }

    if (!buf->temporary) {
        in->buf = b;
        buf->pos = buf->last;
    }

    b->last = write;
    ctx->tout += b->last - b->pos;

    return NGX_OK;
}