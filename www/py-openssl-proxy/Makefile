# Created by: Andrew Pantyukhin <infofarmer@FreeBSD.org>
# $FreeBSD$

PORTNAME=	openssl-proxy
PORTVERSION=	0.1
CATEGORIES=	www security python
MASTER_SITES=	CENKES
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	pyOpenSSLProxy-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	HTTPS proxy support

BROKEN=		No public distfiles
DEPRECATED=	Broken for more than 6 months
EXPIRATION_DATE=	2015-10-31

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}openssl>0:${PORTSDIR}/security/py-openssl

USES=		python:2
USE_PYTHON=	distutils autoplist

.include <bsd.port.mk>
