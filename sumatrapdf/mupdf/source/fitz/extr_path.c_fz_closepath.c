#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int cmd_len; int* cmds; int /*<<< orphan*/  begin; int /*<<< orphan*/  current; scalar_t__ packed; } ;
typedef  TYPE_1__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  FZ_CURVETO 146 
#define  FZ_CURVETOCLOSE 145 
#define  FZ_CURVETOV 144 
#define  FZ_CURVETOVCLOSE 143 
#define  FZ_CURVETOY 142 
#define  FZ_CURVETOYCLOSE 141 
#define  FZ_DEGENLINETO 140 
#define  FZ_DEGENLINETOCLOSE 139 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
#define  FZ_HORIZTO 138 
#define  FZ_HORIZTOCLOSE 137 
#define  FZ_LINETO 136 
#define  FZ_LINETOCLOSE 135 
#define  FZ_MOVETO 134 
#define  FZ_MOVETOCLOSE 133 
#define  FZ_QUADTO 132 
#define  FZ_QUADTOCLOSE 131 
#define  FZ_RECTTO 130 
#define  FZ_VERTTO 129 
#define  FZ_VERTTOCLOSE 128 
 int LAST_CMD (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

void
fz_closepath(fz_context *ctx, fz_path *path)
{
	uint8_t rep;

	if (path->packed)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot modify a packed path");

	if (path->cmd_len == 0)
	{
		fz_warn(ctx, "closepath with no current point");
		return;
	}

	switch(LAST_CMD(path))
	{
	case FZ_MOVETO:
		rep = FZ_MOVETOCLOSE;
		break;
	case FZ_LINETO:
		rep = FZ_LINETOCLOSE;
		break;
	case FZ_DEGENLINETO:
		rep = FZ_DEGENLINETOCLOSE;
		break;
	case FZ_CURVETO:
		rep = FZ_CURVETOCLOSE;
		break;
	case FZ_CURVETOV:
		rep = FZ_CURVETOVCLOSE;
		break;
	case FZ_CURVETOY:
		rep = FZ_CURVETOYCLOSE;
		break;
	case FZ_HORIZTO:
		rep = FZ_HORIZTOCLOSE;
		break;
	case FZ_VERTTO:
		rep = FZ_VERTTOCLOSE;
		break;
	case FZ_QUADTO:
		rep = FZ_QUADTOCLOSE;
		break;
	case FZ_RECTTO:
		/* RectTo implies close */
		return;
	case FZ_MOVETOCLOSE:
	case FZ_LINETOCLOSE:
	case FZ_DEGENLINETOCLOSE:
	case FZ_CURVETOCLOSE:
	case FZ_CURVETOVCLOSE:
	case FZ_CURVETOYCLOSE:
	case FZ_HORIZTOCLOSE:
	case FZ_VERTTOCLOSE:
	case FZ_QUADTOCLOSE:
		/* CLOSE following a CLOSE is a NOP */
		return;
	default: /* default never happens */
	case 0:
		/* Closing an empty path is a NOP */
		return;
	}

	path->cmds[path->cmd_len-1] = rep;

	path->current = path->begin;
}