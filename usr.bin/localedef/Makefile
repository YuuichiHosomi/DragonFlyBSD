# Adapted from Illumos by John Marino <draco@marino.st>

PROG=	localedef
SRCS=	charmap.c \
	collate.c \
	ctype.c \
	localedef.c \
	messages.c \
	monetary.c \
	numeric.c \
	parser.y \
	scanner.c \
	time.c \
	wide.c

${SRCS:M*.c}: parser.h
parser.h: parser.y

CFLAGS+=	-I. -I${.CURDIR}
CFLAGS+=	-I${.CURDIR}/../../lib/libc/locale
CFLAGS+=	-I${.CURDIR}/../../lib/libc/stdtime

.if defined(BOOTSTRAPPING)
CFLAGS+=	-DBOOTSTRAPPING
.endif

.include <bsd.prog.mk>
