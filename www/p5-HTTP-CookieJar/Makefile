# Created by: Sunpoet Po-Chuan Hsieh <sunpoet@FreeBSD.org>
# $FreeBSD$

PORTNAME=	HTTP-CookieJar
PORTVERSION=	0.007
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Minimalist HTTP user agent cookie jar

LICENSE=	APACHE20

BUILD_DEPENDS=	p5-HTTP-Date>=0:${PORTSDIR}/www/p5-HTTP-Date
RUN_DEPENDS:=	${BUILD_DEPENDS}
TEST_DEPENDS=	p5-HTTP-Message>=0:${PORTSDIR}/www/p5-HTTP-Message \
		p5-Mozilla-PublicSuffix>=0:${PORTSDIR}/dns/p5-Mozilla-PublicSuffix \
		p5-Test-Deep>=0:${PORTSDIR}/devel/p5-Test-Deep \
		p5-Test-Requires>=0:${PORTSDIR}/devel/p5-Test-Requires \
		p5-Test-Simple>=0.96:${PORTSDIR}/devel/p5-Test-Simple

NO_ARCH=	yes
USE_PERL5=	configure
USES=		perl5

.include <bsd.port.mk>
