# Created by: Yoshiro MIHIRA <sanpei@sanpei.org>
# $FreeBSD$

PORTNAME=	kanji
PORTVERSION=	1.0
CATEGORIES=	japanese x11-fonts
MASTER_SITES=   PORTS_JP/${DISTNAME}
PKGNAMEPREFIX=	ja-font-
PKGNAMESUFFIX?=	18
DISTNAME=	${PORTNAME}${PKGNAMESUFFIX}
DISTFILES?=	573.z 574.z 575.z 576.z 577.z 578.z 579.z 580.z 581.z
DIST_SUBDIR=	${DISTNAME}

MAINTAINER=	sanpei@FreeBSD.org
COMMENT=	${PKGNAMESUFFIX}-dot Kanji font

BUILD_DEPENDS=	mkbold:${PORTSDIR}/x11-fonts/mkbold-mkitalic \
		bdftopcf:${PORTSDIR}/x11-fonts/bdftopcf

USES=		fonts
FONTNAME=	misc
NO_ARCH=	yes
NO_WRKSUBDIR=	yes
EXTRACT_CMD=		${GZCAT}
EXTRACT_BEFORE_ARGS=
EXTRACT_AFTER_ARGS=	| ${SED} '/bin\/sh/,/exit 0/!d' \
			| (cd ${WRKDIR} && ${SH})
PKGINSTALL=	${WRKDIR}/pkg-install
PKGDEINSTALL=	${WRKDIR}/pkg-install
SUB_FILES=	Makefile pkg-install
SUB_LIST=	FONTSALIAS="${DATADIR}/fonts.alias.${PKGNAMESUFFIX}" \
		SRCS="${SRCS}"
PORTDOCS=	README.${PORTNAME}${PKGNAMESUFFIX}

SRCS?=		kanji18.bdf kanji16.bdf
README_FILE?=	573.z
RESIZESED_FILE?=18to16.sed

OPTIONS_DEFINE=	DOCS

post-extract:
	cd ${WRKSRC} && ${CAT} ${DISTNAME}.?? | uudecode
	${GUNZIP_CMD} ${WRKDIR}/*.Z
	${GZCAT} ${DISTDIR}/${DIST_SUBDIR}/${README_FILE} \
	    | ${SED} '/bin\/sh/,/exit 0/d' \
	    > ${WRKSRC}/README.${DISTNAME}
	cd ${WRKSRC} && \
	    ${SED} -f ${RESIZESED_FILE} < ${PORTNAME}${PKGNAMESUFFIX}.bdf \
	    > ${PORTNAME}${RESIZESED_FILE:R:C/^[0-9][0-9]to//}.bdf

pre-build: apply-slist

post-install:
	${INSTALL_DATA} ${FILESDIR}/fonts.alias.${PKGNAMESUFFIX} \
	    ${STAGEDIR}${DATADIR}/fonts.alias.${PKGNAMESUFFIX}
	@${MKDIR} ${STAGEDIR}${FONTSDIR}
	cd ${STAGEDIR}${FONTSDIR} && \
	    ${LN} -s ../../../${DATADIR_REL}/*.pcf.gz .

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC} && \
	    ${INSTALL_DATA} README.${DISTNAME} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
