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
typedef  void uint8_t ;
struct blockif_req {int br_iovcnt; int /*<<< orphan*/  (* br_callback ) (struct blockif_req*,int) ;scalar_t__ br_resid; scalar_t__ br_offset; TYPE_1__* br_iov; } ;
struct blockif_elem {int be_op; int /*<<< orphan*/  be_status; struct blockif_req* be_req; } ;
struct blockif_ctxt {int /*<<< orphan*/  bc_candelete; int /*<<< orphan*/  bc_fd; int /*<<< orphan*/  bc_ischr; int /*<<< orphan*/  bc_rdonly; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
#define  BOP_DELETE 131 
#define  BOP_FLUSH 130 
#define  BOP_READ 129 
#define  BOP_WRITE 128 
 int /*<<< orphan*/  BST_DONE ; 
 int /*<<< orphan*/  DKIOCSYNCHRONIZECACHE ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 scalar_t__ MAXPHYS ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  pread (int /*<<< orphan*/ ,void*,size_t,scalar_t__) ; 
 scalar_t__ preadv (int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  pwrite (int /*<<< orphan*/ ,void*,size_t,scalar_t__) ; 
 scalar_t__ pwritev (int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct blockif_req*,int) ; 

__attribute__((used)) static void
blockif_proc(struct blockif_ctxt *bc, struct blockif_elem *be, uint8_t *buf)
{
	struct blockif_req *br;
	// off_t arg[2];
	ssize_t clen, len, off, boff, voff;
	int i, err;

	br = be->be_req;
	if (br->br_iovcnt <= 1)
		buf = NULL;
	err = 0;
	switch (be->be_op) {
	case BOP_READ:
		if (buf == NULL) {
			if ((len = preadv(bc->bc_fd, br->br_iov, br->br_iovcnt,
				   br->br_offset)) < 0)
				err = errno;
			else
				br->br_resid -= len;
			break;
		}
		i = 0;
		off = voff = 0;
		while (br->br_resid > 0) {
			len = MIN(br->br_resid, MAXPHYS);
			if (pread(bc->bc_fd, buf, ((size_t) len), br->br_offset + off) < 0)
			{
				err = errno;
				break;
			}
			boff = 0;
			do {
				clen = MIN((len - boff),
					(((ssize_t) br->br_iov[i].iov_len) - voff));
				memcpy(((void *) (((uintptr_t) br->br_iov[i].iov_base) +
					((size_t) voff))), buf + boff, clen);
				if (clen < (((ssize_t) br->br_iov[i].iov_len) - voff))
					voff += clen;
				else {
					i++;
					voff = 0;
				}
				boff += clen;
			} while (boff < len);
			off += len;
			br->br_resid -= len;
		}
		break;
	case BOP_WRITE:
		if (bc->bc_rdonly) {
			err = EROFS;
			break;
		}
		if (buf == NULL) {
			if ((len = pwritev(bc->bc_fd, br->br_iov, br->br_iovcnt,
				    br->br_offset)) < 0)
				err = errno;
			else
				br->br_resid -= len;
			break;
		}
		i = 0;
		off = voff = 0;
		while (br->br_resid > 0) {
			len = MIN(br->br_resid, MAXPHYS);
			boff = 0;
			do {
				clen = MIN((len - boff),
					(((ssize_t) br->br_iov[i].iov_len) - voff));
				memcpy((buf + boff),
					((void *) (((uintptr_t) br->br_iov[i].iov_base) +
						((size_t) voff))), clen);
				if (clen < (((ssize_t) br->br_iov[i].iov_len) - voff))
					voff += clen;
				else {
					i++;
					voff = 0;
				}
				boff += clen;
			} while (boff < len);
			if (pwrite(bc->bc_fd, buf, ((size_t) len), br->br_offset +
			    off) < 0) {
				err = errno;
				break;
			}
			off += len;
			br->br_resid -= len;
		}
		break;
	case BOP_FLUSH:
		if (bc->bc_ischr) {
			if (ioctl(bc->bc_fd, DKIOCSYNCHRONIZECACHE))
				err = errno;
		} else if (fsync(bc->bc_fd))
			err = errno;
		break;
	case BOP_DELETE:
		if (!bc->bc_candelete) {
			err = EOPNOTSUPP;
		// } else if (bc->bc_rdonly) {
		// 	err = EROFS;
		// } else if (bc->bc_ischr) {
		// 	arg[0] = br->br_offset;
		// 	arg[1] = br->br_resid;
		// 	if (ioctl(bc->bc_fd, DIOCGDELETE, arg)) {
		// 		err = errno;
		// 	} else {
		// 		br->br_resid = 0;
		// 	}
		} else {
			err = EOPNOTSUPP;
		}
		break;
	}

	be->be_status = BST_DONE;

	(*br->br_callback)(br, err);
}