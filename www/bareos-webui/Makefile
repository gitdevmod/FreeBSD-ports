# Created by: Alonso Cardenas <acm@FreeBSD.org>
# $FreeBSD$

PORTNAME=	bareos-webui
DISTVERSION=	14.2.1
PORTREVISION=	0
CATEGORIES=	www sysutils

USE_GITHUB=	yes
GH_ACCOUNT=	bareos
GH_PROJECT=	bareos-webui
GH_TAGNAME=	c826a4cbd4ff7340fb9b020ca824c9c48bd52948

MAINTAINER=	acm@FreeBSD.org
COMMENT=	A PHP-Frontend to manage Bareos over the web

LICENSE=	AGPLv3 # or later
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		tar:tgz
USE_PHP=	openssl
NO_BUILD=	yes
NO_ARCH=	yes
NO_WRKSUBDIR=	yes

BAREOSWEB_HOME?=${WWWDIR}
BAREOSWEBUIDIR=	${BAREOSWEB_HOME:S|${PREFIX}/||}
SUB_FILES=	pkg-message
PLIST_SUB=	WWWOWN=${WWWOWN} WWWGRP=${WWWGRP} BAREOSWEBUIDIR=${BAREOSWEBUIDIR}
SUB_LIST=	BAREOSWEBUIDIR=${BAREOSWEBUIDIR}

OPTIONS_DEFINE=		MYSQL PGSQL ZENDFRAMEWORK
OPTIONS_DEFAULT=	PGSQL
ZENDFRAMEWORK_DESC=	Install zend framework	

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MMYSQL}
USE_PHP+=	pdo_mysql
.endif

.if ${PORT_OPTIONS:MPGSQL}
USE_PHP+=	pdo_pgsql
.endif

.if ${PORT_OPTIONS:MZENDFRAMEWORK}
RUN_DEPENDS=	${LOCALBASE}/share/ZendFramework/bin/classmap_generator.php:${PORTSDIR}/www/zend-framework
.endif

post-extract:
	${RM} ${WRKSRC}/config/autoload/.gitignore
	${RM} ${WRKSRC}/data/cache/.gitignore
	${RM} ${WRKSRC}/vendor/.gitignore

post-patch:
	@${REINPLACE_CMD} -e 's|/etc/|${LOCALBASE}/etc/|g' ${WRKSRC}/config/autoload/global.php

do-install:
	@${ECHO} "Installing in ${BAREOSWEB_HOME}"
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${MKDIR} ${STAGEDIR}${BAREOSWEB_HOME}
	cd ${WRKSRC} && ${COPYTREE_SHARE} "config data module public vendor" \
		${STAGEDIR}${BAREOSWEB_HOME}
	${INSTALL_DATA} ${WRKSRC}/*.php ${STAGEDIR}${BAREOSWEB_HOME}
	${INSTALL_DATA} ${WRKSRC}/composer* ${STAGEDIR}${BAREOSWEB_HOME}
	${INSTALL_DATA} ${WRKSRC}/phpunit.xml ${STAGEDIR}${BAREOSWEB_HOME}
	${INSTALL_DATA} ${WRKSRC}/install/directors.ini ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKSRC}/install/bareos/bareos-webui.conf ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKSRC}/install/apache/bareos-webui.conf ${STAGEDIR}${ETCDIR}/apache-bareos-webui.conf

.include <bsd.port.mk>
