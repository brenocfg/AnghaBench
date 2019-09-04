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
typedef  char uint32_t ;
struct rfb_softc {int cfd; int /*<<< orphan*/  zstream; scalar_t__ enc_zlib_ok; int /*<<< orphan*/ * zbuf; scalar_t__ password; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/ * pthread_t ;
typedef  int /*<<< orphan*/  challenge ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CCCryptorStatus ;

/* Variables and functions */
 int AUTH_LENGTH ; 
 int /*<<< orphan*/  CCCrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,unsigned char*,int,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int PASSWD_LENGTH ; 
 scalar_t__ RFB_ZLIB_BUFSZ ; 
#define  SECURITY_TYPE_NONE 129 
#define  SECURITY_TYPE_VNC_AUTH 128 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  arc4random_buf (unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (unsigned char*,char) ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 char htonl (int) ; 
 int /*<<< orphan*/  kCCAlgorithmDES ; 
 int /*<<< orphan*/  kCCEncrypt ; 
 int /*<<< orphan*/  kCCOptionECBMode ; 
 int /*<<< orphan*/  kCCSuccess ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int pthread_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rfb_softc*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  rfb_recv_cuttext_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_recv_key_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_recv_ptr_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_recv_set_encodings_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_recv_set_pixfmt_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_recv_update_msg (struct rfb_softc*,int,int) ; 
 int /*<<< orphan*/  rfb_send_screen (struct rfb_softc*,int,int) ; 
 int /*<<< orphan*/  rfb_send_server_init_msg (int) ; 
 int /*<<< orphan*/  rfb_wr_thr ; 
 long stream_read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  stream_write (int,...) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,scalar_t__,int) ; 

__attribute__((used)) static void
rfb_handle(struct rfb_softc *rc, int cfd)
{
	const char *vbuf = "RFB 003.008\n";
	unsigned char buf[80];
	char *message = NULL;

	unsigned char challenge[AUTH_LENGTH];
	unsigned char keystr[PASSWD_LENGTH];
	unsigned char crypt_expected[AUTH_LENGTH];

    size_t dataOutSize;
    int i;
    CCCryptorStatus cryptoResult;

	pthread_t tid = NULL;
	uint32_t sres = 0;
	long len;
	int perror = 1;

	rc->cfd = cfd;

	/* 1a. Send server version */
	stream_write(cfd, vbuf, (ssize_t)strlen(vbuf));

	/* 1b. Read client version */
	len = read(cfd, buf, sizeof(buf));

	/* 2a. Send security type */
	buf[0] = 1;
	if (rc->password)
		buf[1] = SECURITY_TYPE_VNC_AUTH;
	else
		buf[1] = SECURITY_TYPE_NONE;

	stream_write(cfd, buf, 2);

	/* 2b. Read agreed security type */
	len = stream_read(cfd, buf, 1);

	/* 2c. Do VNC authentication */
	switch (buf[0]) {
	case SECURITY_TYPE_NONE:
		sres = 0;
		break;
	case SECURITY_TYPE_VNC_AUTH:
		/*
		 * The client encrypts the challenge with DES, using a password
		 * supplied by the user as the key.
		 * To form the key, the password is truncated to
		 * eight characters, or padded with null bytes on the right.
		 * The client then sends the resulting 16-bytes response.
		 */
		strncpy((char *)keystr, rc->password, PASSWD_LENGTH);

		/* VNC clients encrypts the challenge with all the bit fields
		 * in each byte of the password mirrored.
		 * Here we flip each byte of the keystr.
		 */
		for (i = 0; i < PASSWD_LENGTH; i++) {
			keystr[i] = (keystr[i] & 0xF0) >> 4
				  | (unsigned char)((keystr[i] & 0x0F) << 4);
			keystr[i] = (keystr[i] & 0xCC) >> 2
				  | (unsigned char)((keystr[i] & 0x33) << 2);
			keystr[i] = (keystr[i] & 0xAA) >> 1
				  | (unsigned char)((keystr[i] & 0x55) << 1);
		}

		/* Initialize a 16-byte random challenge */
		arc4random_buf(challenge, sizeof(challenge));
		stream_write(cfd, challenge, AUTH_LENGTH);

		/* Receive the 16-byte challenge response */
		stream_read(cfd, buf, AUTH_LENGTH);

		memcpy(crypt_expected, challenge, AUTH_LENGTH);

        cryptoResult = CCCrypt(kCCEncrypt, kCCAlgorithmDES, kCCOptionECBMode,
                               keystr, PASSWD_LENGTH,
                               NULL,
                               challenge, AUTH_LENGTH,
                               crypt_expected, AUTH_LENGTH,
                               &dataOutSize);

        if (cryptoResult != kCCSuccess) {
            message = "Auth Failed: Internal Error.";
            sres = htonl(1);
        } else if (memcmp(crypt_expected, buf, AUTH_LENGTH) != 0) {
			message = "Auth Failed: Invalid Password.";
			sres = htonl(1);
        } else {
			sres = 0;
        }
        break;
	}

	/* 2d. Write back a status */
	stream_write(cfd, &sres, 4);

	if (sres) {
		be32enc(buf, (uint32_t)strlen(message));
		stream_write(cfd, buf, 4);
		stream_write(cfd, message, (ssize_t)strlen(message));
		goto done;
	}

	/* 3a. Read client shared-flag byte */
	len = stream_read(cfd, buf, 1);

	/* 4a. Write server-init info */
	rfb_send_server_init_msg(cfd);

	if (!rc->zbuf) {
		rc->zbuf = malloc(RFB_ZLIB_BUFSZ + 16);
		assert(rc->zbuf != NULL);
	}

	rfb_send_screen(rc, cfd, 1);

	perror = pthread_create(&tid, NULL, rfb_wr_thr, rc);
    if (perror != 0) {
        goto done;
    }

        /* Now read in client requests. 1st byte identifies type */
	for (;;) {
		len = read(cfd, buf, 1);
		if (len <= 0) {
			DPRINTF(("rfb client exiting\r\n"));
			break;
		}

		switch (buf[0]) {
		case 0:
			rfb_recv_set_pixfmt_msg(rc, cfd);
			break;
		case 2:
			rfb_recv_set_encodings_msg(rc, cfd);
			break;
		case 3:
			rfb_recv_update_msg(rc, cfd, 1);
			break;
		case 4:
			rfb_recv_key_msg(rc, cfd);
			break;
		case 5:
			rfb_recv_ptr_msg(rc, cfd);
			break;
		case 6:
			rfb_recv_cuttext_msg(rc, cfd);
			break;
		default:
			WPRINTF(("rfb unknown cli-code %d!\n", buf[0] & 0xff));
			goto done;
		}
	}
done:
	rc->cfd = -1;
	if (perror == 0)
		pthread_join(tid, NULL);
	if (rc->enc_zlib_ok)
		deflateEnd(&rc->zstream);
}