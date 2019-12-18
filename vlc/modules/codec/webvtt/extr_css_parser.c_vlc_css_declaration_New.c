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
struct TYPE_4__ {int /*<<< orphan*/  psz_property; } ;
typedef  TYPE_1__ vlc_css_declaration_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

vlc_css_declaration_t * vlc_css_declaration_New( const char *psz )
{
    vlc_css_declaration_t *p_decl = calloc(1, sizeof(*p_decl));
    p_decl->psz_property = strdup(psz);
    return p_decl;
}