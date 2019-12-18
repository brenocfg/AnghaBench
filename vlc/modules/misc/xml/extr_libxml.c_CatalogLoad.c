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
typedef  int /*<<< orphan*/  xml_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlInitializeCatalog () ; 
 int /*<<< orphan*/  xmlLoadCatalog (char const*) ; 

__attribute__((used)) static void CatalogLoad( xml_t *p_xml, const char *psz_filename )
{
    VLC_UNUSED(p_xml);
    if( !psz_filename ) xmlInitializeCatalog();
    else xmlLoadCatalog( psz_filename );
}