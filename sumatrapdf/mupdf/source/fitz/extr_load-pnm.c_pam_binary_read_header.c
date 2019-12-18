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
struct info {scalar_t__ tupletype; scalar_t__ maxval; scalar_t__ depth; scalar_t__ height; scalar_t__ width; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
#define  TOKEN_DEPTH 133 
#define  TOKEN_ENDHDR 132 
#define  TOKEN_HEIGHT 131 
#define  TOKEN_MAXVAL 130 
#define  TOKEN_TUPLTYPE 129 
 int TOKEN_UNKNOWN ; 
#define  TOKEN_WIDTH 128 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 unsigned char* pnm_read_number (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,scalar_t__*) ; 
 unsigned char* pnm_read_token (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,int*) ; 
 unsigned char* pnm_read_tupletype (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,scalar_t__*) ; 
 unsigned char* pnm_read_white (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const unsigned char *
pam_binary_read_header(fz_context *ctx, struct info *pnm, const unsigned char *p, const unsigned char *e)
{
	int token = TOKEN_UNKNOWN;

	pnm->width = 0;
	pnm->height = 0;
	pnm->depth = 0;
	pnm->maxval = 0;
	pnm->tupletype = 0;

	while (p < e && token != TOKEN_ENDHDR)
	{
		p = pnm_read_token(ctx, p, e, &token);
		p = pnm_read_white(ctx, p, e, 0);
		switch (token)
		{
		case TOKEN_WIDTH: p = pnm_read_number(ctx, p, e, &pnm->width); break;
		case TOKEN_HEIGHT: p = pnm_read_number(ctx, p, e, &pnm->height); break;
		case TOKEN_DEPTH: p = pnm_read_number(ctx, p, e, &pnm->depth); break;
		case TOKEN_MAXVAL: p = pnm_read_number(ctx, p, e, &pnm->maxval); break;
		case TOKEN_TUPLTYPE: p = pnm_read_tupletype(ctx, p, e, &pnm->tupletype); break;
		case TOKEN_ENDHDR: break;
		default: fz_throw(ctx, FZ_ERROR_GENERIC, "unknown header token in pnm image");
		}

		if (token != TOKEN_ENDHDR)
			p = pnm_read_white(ctx, p, e, 0);
	}

	return p;
}