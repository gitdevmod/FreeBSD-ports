# Created by: Alexander Kriventsov
# $FreeBSD$

PORTNAME=	repos-style
PORTVERSION=	2.0
PORTREVISION=	2
CATEGORIES=	www
MASTER_SITES=	ftp://ftp.renatasystems.org/pub/FreeBSD/ports/distfiles/ \
		http://mirror.amdmi3.ru/distfiles/

MAINTAINER=	avk@vl.ru
COMMENT=	Stylesheet for the Subversion index web page

RUN_DEPENDS=	subversion>=0:${PORTSDIR}/devel/subversion

USES=		zip
NO_BUILD=	YES

USE_PHP=	xml
WANT_PHP_WEB=	yes

WRKSRC=		${WRKDIR}/repos-web

SUB_LIST+=	PORTNAME=${PORTNAME}
SUB_FILES+=	pkg-message

pre-install:
# Prevent installation of .orig files by deleting them.
	@${FIND} ${WRKSRC} -name '*.orig' -delete
	${MV} ${WRKSRC}/open/log/index.php ${WRKSRC}/open/log/index.dist.php

do-install:
	@${MKDIR} ${STAGEDIR}${WWWDIR}
	@(cd ${WRKSRC} && ${PAX} -r -w . ${STAGEDIR}${WWWDIR})

.include <bsd.port.mk>
