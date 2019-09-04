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
struct section {unsigned int nb_lines; struct line* lines; } ;
struct line {int dummy; } ;
struct inf_file {unsigned int nb_sections; struct section** sections; } ;

/* Variables and functions */

__attribute__((used)) static inline struct line *get_line( struct inf_file *file, unsigned int section_index,
                                     unsigned int line_index )
{
    struct section *section;

    if (section_index >= file->nb_sections) return NULL;
    section = file->sections[section_index];
    if (line_index >= section->nb_lines) return NULL;
    return &section->lines[line_index];
}