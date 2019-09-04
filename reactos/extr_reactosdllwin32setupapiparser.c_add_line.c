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
struct section {int nb_lines; int alloc_lines; struct line* lines; } ;
struct line {int key_field; scalar_t__ nb_fields; int /*<<< orphan*/  first_field; } ;
struct inf_file {int nb_sections; int /*<<< orphan*/  nb_fields; struct section** sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct section* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct section*,int) ; 

__attribute__((used)) static struct line *add_line( struct inf_file *file, int section_index )
{
    struct section *section;
    struct line *line;

    ASSERT( section_index >= 0 && section_index < file->nb_sections );

    section = file->sections[section_index];
    if (section->nb_lines == section->alloc_lines)  /* need to grow the section */
    {
        int size = sizeof(*section) - sizeof(section->lines) + 2*section->alloc_lines*sizeof(*line);
        if (!(section = HeapReAlloc( GetProcessHeap(), 0, section, size ))) return NULL;
        section->alloc_lines *= 2;
        file->sections[section_index] = section;
    }
    line = &section->lines[section->nb_lines++];
    line->first_field = file->nb_fields;
    line->nb_fields   = 0;
    line->key_field   = -1;
    return line;
}