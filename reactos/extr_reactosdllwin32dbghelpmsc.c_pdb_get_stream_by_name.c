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
struct pdb_stream_name {int index; scalar_t__ name; } ;
struct pdb_file_info {struct pdb_stream_name* stream_dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static unsigned pdb_get_stream_by_name(const struct pdb_file_info* pdb_file, const char* name)
{
    struct pdb_stream_name*     psn;

    for (psn = pdb_file->stream_dict; psn && psn->name; psn++)
    {
        if (!strcmp(psn->name, name)) return psn->index;
    }
    return -1;
}