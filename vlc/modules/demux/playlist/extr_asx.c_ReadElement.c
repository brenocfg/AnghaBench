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
typedef  int /*<<< orphan*/  xml_reader_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_xml_decode (char*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static bool ReadElement( xml_reader_t *p_xml_reader, char **ppsz_txt )
{
    const char *psz_node = NULL;

    /* Read the text node */
    int ret = xml_ReaderNextNode( p_xml_reader, &psz_node );
    if( ret <= 0 )
        return false;
    free( *ppsz_txt );
    *ppsz_txt = strdup( psz_node );
    vlc_xml_decode( *ppsz_txt );

    /* Read the end element */
    xml_ReaderNextNode( p_xml_reader, &psz_node );
    /* TODO :
     * Currently we don't check the agreement of start and end element
     * This function is only used to read the element that cannot have child
     * according to the reference.
     */
    return true;
}