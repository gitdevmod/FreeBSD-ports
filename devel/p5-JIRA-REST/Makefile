# Created by: Brad Davis <brd@FreeBSD.org>
# $FreeBSD$

PORTNAME=	JIRA-REST
PORTVERSION=	0.011
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Extended interface to JIRA REST API

LICENSE=	ART10 GPLv1
LICENSE_COMB=	dual

BUILD_DEPENDS=	p5-Data-Util>=0:${PORTSDIR}/devel/p5-Data-Util \
		p5-HTML-TreeBuilder-LibXML>=0:${PORTSDIR}/www/p5-HTML-TreeBuilder-LibXML \
		p5-HTTP-Message>=0:${PORTSDIR}/www/p5-HTTP-Message \
		p5-JSON>=0:${PORTSDIR}/converters/p5-JSON \
		p5-REST-Client>=0:${PORTSDIR}/www/p5-REST-Client \
		p5-URI>=0:${PORTSDIR}/net/p5-URI
RUN_DEPENDS:=	${BUILD_DEPENDS}

USES=		perl5
USE_PERL5=	configure
NO_ARCH=	yes

PLIST_FILES=	%%SITE_PERL%%/JIRA/README.pod \
		%%SITE_PERL%%/JIRA/REST.pm \
		%%PERL5_MAN3%%/JIRA::README.3.gz \
		%%PERL5_MAN3%%/JIRA::REST.3.gz

.include <bsd.port.mk>
