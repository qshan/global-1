/*
 * Copyright (c) 1996, 1997, 1998, 1999
 *            Shigio Yamaguchi. All rights reserved.
 * Copyright (c) 1999
 *            Tama Communications Corporation. All rights reserved.
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
 *      This product includes software developed by Tama Communications
 *      Corporation and its contributors.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      dbop.h                                  12-Dec-99
 *
 */

#ifndef _DBOP_H_
#define _DBOP_H_

#include "gparam.h"
#include "db.h"
#include "regex.h"

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN   1234
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN      4321
#endif

typedef	struct {
	DB	*db;			/* descripter of DB */
	char	dbname[MAXPATHLEN+1];	/* dbname */
	char	key[MAXKEYLEN+1];	/* key */
	int	keylen;			/* key length */
	regex_t	*preg;			/* compiled regular expression */
	char	prev[MAXKEYLEN+1];	/* previous key value */
	char	*lastkey;		/* the key of last located record */
	char	*lastdat;		/* the data of last located record */
	int	openflags;		/* flags of dbop_open() */
	int	ioflags;		/* flags of dbop_first() */
	int	perm;			/* file permission */
} DBOP;

/*
 * openflags
 */
#define	DBOP_DUP	1		/* allow duplicate records	*/
#define DBOP_REMOVE	2		/* remove file when closed	*/
/*
 * ioflags
 */
#define DBOP_KEY	1		/* read key part		*/
#define DBOP_PREFIX	2		/* prefixed read		*/

DBOP	*dbop_open(const char *, int, int, int);
char	*dbop_get(DBOP *, const char *);
void	dbop_put(DBOP *, const char *, const char *);
void	dbop_del(DBOP *, const char *);
char	*dbop_first(DBOP *, const char *, regex_t *, int);
char	*dbop_next(DBOP *);
void	dbop_close(DBOP *);
#endif /* _DBOP_H_ */
