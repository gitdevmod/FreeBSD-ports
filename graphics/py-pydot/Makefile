# Created by: Stefan Walter <sw@gegenunendlich.de>
# $FreeBSD$

PORTNAME=	pydot
PORTVERSION=	1.0.28
CATEGORIES=	graphics python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Python interface to the Graphviz Dot language

LICENSE=	MIT

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}parsing>=0:${PORTSDIR}/devel/py-parsing
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}parsing>=0:${PORTSDIR}/devel/py-parsing \
		dot:${PORTSDIR}/graphics/graphviz

NO_ARCH=	yes
USE_PYTHON=	autoplist distutils
USES=		python

GH_ACCOUNT=	erocarrera
GH_TAGNAME=	ec21a11
USE_GITHUB=	yes

post-patch:
	@${REINPLACE_CMD} -e "s|__version__ = .*|__version__ = '${PORTVERSION}'|" ${WRKSRC}/pydot.py

.include <bsd.port.mk>
