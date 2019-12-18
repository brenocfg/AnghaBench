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
struct RARProgramCode {struct RARProgramCode* globalbackup; struct RARProgramCode* staticdata; int /*<<< orphan*/  prog; struct RARProgramCode* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct RARProgramCode*) ; 

__attribute__((used)) static void rar_delete_program(struct RARProgramCode *prog)
{
    while (prog) {
        struct RARProgramCode *next = prog->next;
        RARDeleteProgram(prog->prog);
        free(prog->staticdata);
        free(prog->globalbackup);
        free(prog);
        prog = next;
    }
}