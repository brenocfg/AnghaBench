#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_2__ {int size; void* buffer; } ;
struct uncomplete {int read; int header; TYPE_1__ pack; struct uncomplete* next; } ;
struct queue {struct uncomplete** hash; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_DATA ; 
 int /*<<< orphan*/  TYPE_MORE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct uncomplete* find_uncomplete (struct queue*,int) ; 
 int hash_fd (int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void**,int) ; 
 int /*<<< orphan*/  push_data (int /*<<< orphan*/ *,int,void**,int,int) ; 
 int /*<<< orphan*/  push_more (int /*<<< orphan*/ *,int,void**,int) ; 
 int read_size (void**) ; 
 struct uncomplete* save_uncomplete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (struct uncomplete*) ; 
 void* skynet_malloc (int) ; 

__attribute__((used)) static int
filter_data_(lua_State *L, int fd, uint8_t * buffer, int size) {
	struct queue *q = lua_touserdata(L,1);
	struct uncomplete * uc = find_uncomplete(q, fd);
	if (uc) {
		// fill uncomplete
		if (uc->read < 0) {
			// read size
			assert(uc->read == -1);
			int pack_size = *buffer;
			pack_size |= uc->header << 8 ;
			++buffer;
			--size;
			uc->pack.size = pack_size;
			uc->pack.buffer = skynet_malloc(pack_size);
			uc->read = 0;
		}
		int need = uc->pack.size - uc->read;
		if (size < need) {
			memcpy(uc->pack.buffer + uc->read, buffer, size);
			uc->read += size;
			int h = hash_fd(fd);
			uc->next = q->hash[h];
			q->hash[h] = uc;
			return 1;
		}
		memcpy(uc->pack.buffer + uc->read, buffer, need);
		buffer += need;
		size -= need;
		if (size == 0) {
			lua_pushvalue(L, lua_upvalueindex(TYPE_DATA));
			lua_pushinteger(L, fd);
			lua_pushlightuserdata(L, uc->pack.buffer);
			lua_pushinteger(L, uc->pack.size);
			skynet_free(uc);
			return 5;
		}
		// more data
		push_data(L, fd, uc->pack.buffer, uc->pack.size, 0);
		skynet_free(uc);
		push_more(L, fd, buffer, size);
		lua_pushvalue(L, lua_upvalueindex(TYPE_MORE));
		return 2;
	} else {
		if (size == 1) {
			struct uncomplete * uc = save_uncomplete(L, fd);
			uc->read = -1;
			uc->header = *buffer;
			return 1;
		}
		int pack_size = read_size(buffer);
		buffer+=2;
		size-=2;

		if (size < pack_size) {
			struct uncomplete * uc = save_uncomplete(L, fd);
			uc->read = size;
			uc->pack.size = pack_size;
			uc->pack.buffer = skynet_malloc(pack_size);
			memcpy(uc->pack.buffer, buffer, size);
			return 1;
		}
		if (size == pack_size) {
			// just one package
			lua_pushvalue(L, lua_upvalueindex(TYPE_DATA));
			lua_pushinteger(L, fd);
			void * result = skynet_malloc(pack_size);
			memcpy(result, buffer, size);
			lua_pushlightuserdata(L, result);
			lua_pushinteger(L, size);
			return 5;
		}
		// more data
		push_data(L, fd, buffer, pack_size, 1);
		buffer += pack_size;
		size -= pack_size;
		push_more(L, fd, buffer, size);
		lua_pushvalue(L, lua_upvalueindex(TYPE_MORE));
		return 2;
	}
}