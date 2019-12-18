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
struct vm {int dummy; } ;
struct vatpic {struct vm* vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATPIC_LOCK_INIT (struct vatpic*) ; 
 int /*<<< orphan*/  assert (struct vatpic*) ; 
 int /*<<< orphan*/  bzero (struct vatpic*,int) ; 
 struct vatpic* malloc (int) ; 

struct vatpic *
vatpic_init(struct vm *vm)
{
	struct vatpic *vatpic;

	vatpic = malloc(sizeof(struct vatpic));
	assert(vatpic);
	bzero(vatpic, sizeof(struct vatpic));
	vatpic->vm = vm;

	VATPIC_LOCK_INIT(vatpic);

	return (vatpic);
}