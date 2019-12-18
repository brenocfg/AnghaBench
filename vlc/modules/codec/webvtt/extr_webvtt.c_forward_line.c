#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  section; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* pf_header ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ;} ;
typedef  TYPE_1__ webvtt_text_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void forward_line( webvtt_text_parser_t *p, const char *psz_line, bool b_new )
{
    if( p->pf_header )
        p->pf_header( p->priv, p->section, b_new, psz_line );
}