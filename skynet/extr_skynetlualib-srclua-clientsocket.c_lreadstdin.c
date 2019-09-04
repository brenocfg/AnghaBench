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
struct queue {size_t head; size_t tail; char** queue; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 size_t QUEUE_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lreadstdin(lua_State *L) {
	struct queue *q = lua_touserdata(L, lua_upvalueindex(1));
	pthread_mutex_lock(&q->lock);
	if (q->head == q->tail) {
		pthread_mutex_unlock(&q->lock);
		return 0;
	}
	char * str = q->queue[q->head];
	if (++q->head >= QUEUE_SIZE) {
		q->head = 0;
	}
	pthread_mutex_unlock(&q->lock);
	lua_pushstring(L, str);
	free(str);
	return 1;
}