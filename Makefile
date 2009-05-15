# $Id: Makefile 2 2007-04-17 21:22:08Z chhsiao $
# $FreeBSD: src/usr.sbin/bluetooth/wiimoted/Makefile,v 1.4.2.1 2006/10/09 21:00:17 emax Exp $

PROG=		bsdmoted
NO_MAN=
#MAN=		bsdmoted.8
#		wiimoted.conf.5
SRCS=		bsdmoted.c client.c wiimote.c hid.c kbd.c lexer.l parser.y server.c \
		session.c

CFLAGS+=	-I${.CURDIR}
WARNS?=		6
DEBUG_FLAGS=	-g

DPADD=          ${LIBBLUETOOTH} ${LIBSDP}
LDADD=		-lbluetooth -lusbhid

DESTDIR=	/usr/local/sbin

.include <bsd.prog.mk>
