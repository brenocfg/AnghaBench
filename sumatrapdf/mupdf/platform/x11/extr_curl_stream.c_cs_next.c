#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct curlstate {unsigned char* public_buffer; size_t content_length; scalar_t__ data_arrived; int current_fill_start; int buffer; int next_fill_start; int /*<<< orphan*/ * map; scalar_t__ curl_error; } ;
typedef  int int64_t ;
struct TYPE_3__ {int pos; unsigned char* rp; unsigned char* wp; struct curlstate* state; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int BLOCK_SHIFT ; 
 int BLOCK_SIZE ; 
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  FZ_ERROR_TRYLATER ; 
 int /*<<< orphan*/  HAVE_BLOCK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lock (struct curlstate*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int,size_t) ; 
 int /*<<< orphan*/  unlock (struct curlstate*) ; 

__attribute__((used)) static int cs_next(fz_context *ctx, fz_stream *stream, size_t len)
{
	struct curlstate *state = stream->state;
	size_t len_read = 0;
	int64_t read_point = stream->pos;
	int block = read_point>>BLOCK_SHIFT;
	size_t left_over = (-read_point) & (BLOCK_SIZE-1);
	unsigned char *buf = state->public_buffer;

	assert(len != 0);

	stream->rp = stream->wp = buf;
	lock(state);

	/* If we got an error from the fetching thread,
	 * throw it here (but just once). */
	if (state->curl_error)
	{
		CURLcode err = state->curl_error;
		state->curl_error = 0;
		unlock(state);
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot fetch data: %s", curl_easy_strerror(err));
	}

	if ((size_t) read_point > state->content_length)
	{
		unlock(state);
		if (state->data_arrived == 0)
			fz_throw(ctx, FZ_ERROR_TRYLATER, "read of a block we don't have (A) (offset=%ld)", read_point);
		return EOF;
	}

	if (len > sizeof(state->public_buffer))
		len = sizeof(state->public_buffer);

	if (state->map == NULL)
	{
		/* We are doing a simple linear fetch as we don't know the
		 * content length. */
		if (read_point + len > state->current_fill_start)
		{
			unlock(state);
			fz_throw(ctx, FZ_ERROR_TRYLATER, "read of a block we don't have (B) (offset=%ld)", read_point);
		}
		memcpy(buf, state->buffer + read_point, len);
		unlock(state);
		stream->wp = buf + len;
		stream->pos += len;
		if (len == 0)
			return EOF;
		return *stream->rp++;
	}

	/* We are reading from a "mapped" file */
	if (read_point + len > state->content_length)
		len = state->content_length - read_point;
	if (left_over > len)
		left_over = len;
	if (left_over > 0)
	{
		/* We are starting midway through a block */
		if (!HAVE_BLOCK(state->map, block))
		{
			state->next_fill_start = block<<BLOCK_SHIFT;
			unlock(state);
			fz_throw(ctx, FZ_ERROR_TRYLATER, "read of a block we don't have (C) (offset=%ld)", read_point);
		}
		block++;
		memcpy(buf, state->buffer + read_point, left_over);
		buf += left_over;
		read_point += left_over;
		len -= left_over;
		len_read += left_over;
	}

	/* Copy any complete blocks */
	while (len > BLOCK_SIZE)
	{
		if (!HAVE_BLOCK(state->map, block))
		{
			/* We don't have enough data to fulfill the request. */
			/* Fetch the next block from here. */
			unlock(state);
			state->next_fill_start = block<<BLOCK_SHIFT;
			stream->wp += len_read;
			stream->pos += len_read;
			/* If we haven't fetched anything, throw. */
			if (len_read == 0)
				fz_throw(ctx, FZ_ERROR_TRYLATER, "read of a block we don't have (D) (offset=%ld)", read_point);
			/* Otherwise, we got at least one byte, so we can safely return that. */
			return *stream->rp++;
		}
		block++;
		memcpy(buf, state->buffer + read_point, BLOCK_SIZE);
		buf += BLOCK_SIZE;
		read_point += BLOCK_SIZE;
		len -= BLOCK_SIZE;
		len_read += BLOCK_SIZE;
	}

	/* Copy any trailing bytes */
	if (len > 0)
	{
		if (!HAVE_BLOCK(state->map, block))
		{
			/* We don't have enough data to fulfill the request. */
			/* Fetch the next block from here. */
			unlock(state);
			state->next_fill_start = block<<BLOCK_SHIFT;
			stream->wp += len_read;
			stream->pos += len_read;
			/* If we haven't fetched anything, throw. */
			if (len_read == 0)
				fz_throw(ctx, FZ_ERROR_TRYLATER, "read of a block we don't have (E) (offset=%ld)", read_point);
			/* Otherwise, we got at least one byte, so we can safely return that. */
			return *stream->rp++;
		}
		memcpy(buf, state->buffer + read_point, len);
		len_read += len;
	}

	unlock(state);
	stream->wp += len_read;
	stream->pos += len_read;
	if (len_read == 0)
		return EOF;
	return *stream->rp++;
}