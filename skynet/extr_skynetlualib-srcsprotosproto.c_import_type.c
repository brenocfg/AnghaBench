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
typedef  int uint32_t ;
struct sproto_type {int n; int maxn; int base; struct field* f; int /*<<< orphan*/  name; } ;
struct sproto {int /*<<< orphan*/  memory; } ;
struct field {int tag; } ;

/* Variables and functions */
 int SIZEOF_FIELD ; 
 int SIZEOF_HEADER ; 
 int SIZEOF_LENGTH ; 
 int count_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * import_field (struct sproto*,struct field*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  import_string (struct sproto*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (struct sproto_type*,int /*<<< orphan*/ ,int) ; 
 struct field* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int struct_field (int /*<<< orphan*/  const*,int) ; 
 int todword (int /*<<< orphan*/  const*) ; 
 int toword (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint8_t *
import_type(struct sproto *s, struct sproto_type *t, const uint8_t * stream) {
	const uint8_t * result;
	uint32_t sz = todword(stream);
	int i;
	int fn;
	int n;
	int maxn;
	int last;
	stream += SIZEOF_LENGTH;
	result = stream + sz;
	fn = struct_field(stream, sz);
	if (fn <= 0 || fn > 2)
		return NULL;
	for (i=0;i<fn*SIZEOF_FIELD;i+=SIZEOF_FIELD) {
		// name and fields must encode to 0
		int v = toword(stream + SIZEOF_HEADER + i);
		if (v != 0)
			return NULL;
	}
	memset(t, 0, sizeof(*t));
	stream += SIZEOF_HEADER + fn * SIZEOF_FIELD;
	t->name = import_string(s, stream);
	if (fn == 1) {
		return result;
	}
	stream += todword(stream)+SIZEOF_LENGTH;	// second data
	n = count_array(stream);
	if (n<0)
		return NULL;
	stream += SIZEOF_LENGTH;
	maxn = n;
	last = -1;
	t->n = n;
	t->f = pool_alloc(&s->memory, sizeof(struct field) * n);
	for (i=0;i<n;i++) {
		int tag;
		struct field *f = &t->f[i];
		stream = import_field(s, f, stream);
		if (stream == NULL)
			return NULL;
		tag = f->tag;
		if (tag <= last)
			return NULL;	// tag must in ascending order
		if (tag > last+1) {
			++maxn;
		}
		last = tag;
	}
	t->maxn = maxn;
	t->base = t->f[0].tag;
	n = t->f[n-1].tag - t->base + 1;
	if (n != t->n) {
		t->base = -1;
	}
	return result;
}