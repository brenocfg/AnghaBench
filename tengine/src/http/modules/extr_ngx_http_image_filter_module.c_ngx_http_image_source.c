#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_8__ {int type; int /*<<< orphan*/  image; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ ngx_http_image_filter_ctx_t ;
typedef  int /*<<< orphan*/ * gdImagePtr ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
#define  NGX_HTTP_IMAGE_GIF 131 
#define  NGX_HTTP_IMAGE_JPEG 130 
#define  NGX_HTTP_IMAGE_PNG 129 
#define  NGX_HTTP_IMAGE_WEBP 128 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/ * gdImageCreateFromGifPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdImageCreateFromJpegPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdImageCreateFromPngPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdImageCreateFromWebpPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static gdImagePtr
ngx_http_image_source(ngx_http_request_t *r, ngx_http_image_filter_ctx_t *ctx)
{
    char        *failed;
    gdImagePtr   img;

    img = NULL;

    switch (ctx->type) {

    case NGX_HTTP_IMAGE_JPEG:
        img = gdImageCreateFromJpegPtr(ctx->length, ctx->image);
        failed = "gdImageCreateFromJpegPtr() failed";
        break;

    case NGX_HTTP_IMAGE_GIF:
        img = gdImageCreateFromGifPtr(ctx->length, ctx->image);
        failed = "gdImageCreateFromGifPtr() failed";
        break;

    case NGX_HTTP_IMAGE_PNG:
        img = gdImageCreateFromPngPtr(ctx->length, ctx->image);
        failed = "gdImageCreateFromPngPtr() failed";
        break;

    case NGX_HTTP_IMAGE_WEBP:
#if (NGX_HAVE_GD_WEBP)
        img = gdImageCreateFromWebpPtr(ctx->length, ctx->image);
        failed = "gdImageCreateFromWebpPtr() failed";
#else
        failed = "nginx was built without GD WebP support";
#endif
        break;

    default:
        failed = "unknown image type";
        break;
    }

    if (img == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, failed);
    }

    return img;
}