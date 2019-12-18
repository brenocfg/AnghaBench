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
struct messagepool {int dummy; } ;
struct databuffer {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  _return_message (struct databuffer*,struct messagepool*) ; 
 int /*<<< orphan*/  memset (struct databuffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
databuffer_clear(struct databuffer *db, struct messagepool *mp) {
	while (db->head) {
		_return_message(db,mp);
	}
	memset(db, 0, sizeof(*db));
}