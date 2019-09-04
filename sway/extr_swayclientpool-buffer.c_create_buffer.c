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
typedef  int uint32_t ;
struct wl_shm_pool {int dummy; } ;
struct wl_shm {int dummy; } ;
struct pool_buffer {size_t size; int width; int height; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cairo; int /*<<< orphan*/  pango; int /*<<< orphan*/  surface; void* data; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_listener ; 
 int /*<<< orphan*/  cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_image_surface_create_for_data (void*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int create_pool_file (size_t,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_cairo_create_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  wl_buffer_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pool_buffer*) ; 
 struct wl_shm_pool* wl_shm_create_pool (struct wl_shm*,int,size_t) ; 
 int /*<<< orphan*/  wl_shm_pool_create_buffer (struct wl_shm_pool*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  wl_shm_pool_destroy (struct wl_shm_pool*) ; 

__attribute__((used)) static struct pool_buffer *create_buffer(struct wl_shm *shm,
		struct pool_buffer *buf, int32_t width, int32_t height,
		uint32_t format) {
	uint32_t stride = width * 4;
	size_t size = stride * height;

	char *name;
	int fd = create_pool_file(size, &name);
	assert(fd != -1);
	void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
	buf->buffer = wl_shm_pool_create_buffer(pool, 0,
			width, height, stride, format);
	wl_shm_pool_destroy(pool);
	close(fd);
	unlink(name);
	free(name);

	buf->size = size;
	buf->width = width;
	buf->height = height;
	buf->data = data;
	buf->surface = cairo_image_surface_create_for_data(data,
			CAIRO_FORMAT_ARGB32, width, height, stride);
	buf->cairo = cairo_create(buf->surface);
	buf->pango = pango_cairo_create_context(buf->cairo);

	wl_buffer_add_listener(buf->buffer, &buffer_listener, buf);
	return buf;
}