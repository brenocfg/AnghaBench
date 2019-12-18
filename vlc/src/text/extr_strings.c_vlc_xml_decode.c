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
struct xml_entity_s {int /*<<< orphan*/  psz_entity; int /*<<< orphan*/  psz_char; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct xml_entity_s* bsearch (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_entity ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  xml_entities ; 

void vlc_xml_decode( char *psz_value )
{
    char *p_pos = psz_value;

    while ( *psz_value )
    {
        if( *psz_value == '&' )
        {
            if( psz_value[1] == '#' )
            {   /* &#DDD; or &#xHHHH; Unicode code point */
                char *psz_end;
                unsigned long cp;

                if( psz_value[2] == 'x' ) /* The x must be lower-case. */
                    cp = strtoul( psz_value + 3, &psz_end, 16 );
                else
                    cp = strtoul( psz_value + 2, &psz_end, 10 );

                if( *psz_end == ';' )
                {
                    psz_value = psz_end + 1;
                    if( cp == 0 )
                        (void)0; /* skip nulls */
                    else
                    if( cp <= 0x7F )
                    {
                        *p_pos =            cp;
                    }
                    else
                    /* Unicode code point outside ASCII.
                     * &#xxx; representation is longer than UTF-8 :) */
                    if( cp <= 0x7FF )
                    {
                        *p_pos++ = 0xC0 |  (cp >>  6);
                        *p_pos   = 0x80 |  (cp        & 0x3F);
                    }
                    else
                    if( cp <= 0xFFFF )
                    {
                        *p_pos++ = 0xE0 |  (cp >> 12);
                        *p_pos++ = 0x80 | ((cp >>  6) & 0x3F);
                        *p_pos   = 0x80 |  (cp        & 0x3F);
                    }
                    else
                    if( cp <= 0x1FFFFF ) /* Outside the BMP */
                    {   /* Unicode stops at 10FFFF, but who cares? */
                        *p_pos++ = 0xF0 |  (cp >> 18);
                        *p_pos++ = 0x80 | ((cp >> 12) & 0x3F);
                        *p_pos++ = 0x80 | ((cp >>  6) & 0x3F);
                        *p_pos   = 0x80 |  (cp        & 0x3F);
                    }
                }
                else
                {
                    /* Invalid entity number */
                    *p_pos = *psz_value;
                    psz_value++;
                }
            }
            else
            {   /* Well-known XML entity */
                const struct xml_entity_s *ent;

                ent = bsearch (psz_value + 1, xml_entities,
                               ARRAY_SIZE (xml_entities),
                               sizeof (*ent), cmp_entity);
                if (ent != NULL)
                {
                    size_t olen = strlen (ent->psz_char);
                    memcpy (p_pos, ent->psz_char, olen);
                    p_pos += olen - 1;
                    psz_value += strlen (ent->psz_entity) + 1;
                }
                else
                {   /* No match */
                    *p_pos = *psz_value;
                    psz_value++;
                }
            }
        }
        else
        {
            *p_pos = *psz_value;
            psz_value++;
        }

        p_pos++;
    }

    *p_pos = '\0';
}