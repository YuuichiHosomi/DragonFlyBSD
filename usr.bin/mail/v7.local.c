/*
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)v7.local.c	8.1 (Berkeley) 6/6/93
 * $FreeBSD: src/usr.bin/mail/v7.local.c,v 1.2.8.3 2003/01/06 05:46:04 mikeh Exp $
 * $DragonFly: src/usr.bin/mail/v7.local.c,v 1.4 2004/09/08 03:01:11 joerg Exp $
 */

/*
 * Mail -- a mail program
 *
 * Version 7
 *
 * Local routines that are installation dependent.
 */

#include "rcv.h"
#include <fcntl.h>
#include "extern.h"

/*
 * Locate the user's mailbox file (ie, the place where new, unread
 * mail is queued).
 */
void
findmail(char *user, char *buf, int buflen)
{
	char *tmp = getenv("MAIL");

	if (tmp == NULL)
		snprintf(buf, buflen, "%s/%s", _PATH_MAILDIR, user);
	else
		strlcpy(buf, tmp, buflen);
}

/*
 * Get rid of the queued mail.
 */
void
demail(void)
{
	if (value("keep") != NULL || rm(mailname) < 0)
		close(open(mailname, O_CREAT | O_TRUNC | O_WRONLY, 0600));
}

/*
 * Discover user login name.
 */
char *
username(void)
{
	char *np;
	uid_t uid;

	if ((np = getenv("USER")) != NULL)
		return (np);
	if ((np = getenv("LOGNAME")) != NULL)
		return (np);
	if ((np = getname(uid = getuid())) != NULL)
		return (np);
	printf("Cannot associate a name with uid %u\n", (unsigned)uid);
	return (NULL);
}
