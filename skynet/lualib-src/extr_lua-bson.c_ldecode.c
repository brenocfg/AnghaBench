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
typedef  int /*<<< orphan*/  uint8_t ;
struct bson_reader {int /*<<< orphan*/  member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unpack_dict (int /*<<< orphan*/ *,struct bson_reader*,int) ; 

__attribute__((used)) static int
ldecode(lua_State *L) {
	const int32_t * data = lua_touserdata(L,1);
	if (data == NULL) {
		return 0;
	}
	const uint8_t * b = (const uint8_t *)data;
	int32_t len = get_length(b);
	struct bson_reader br = { b , len };

	unpack_dict(L, &br, false);

	return 1;
}