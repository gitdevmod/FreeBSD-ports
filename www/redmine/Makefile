# Created by: Bernhard Froehlich <decke@bluelife.at>
# $FreeBSD$

PORTNAME=	redmine
PORTVERSION=	2.6.9
CATEGORIES=	www
MASTER_SITES=	http://www.redmine.org/releases/

MAINTAINER=	ruby@FreeBSD.org
COMMENT=	Flexible project management web application

LICENSE=	GPLv2

RUN_DEPENDS=	rubygem-builder>=3.0.0:${PORTSDIR}/devel/rubygem-builder \
		rubygem-bundler>=0:${PORTSDIR}/sysutils/rubygem-bundler \
		rubygem-coderay>=1.0.9:${PORTSDIR}/textproc/rubygem-coderay \
		rubygem-i18n>=0.7.0:${PORTSDIR}/devel/rubygem-i18n \
		rubygem-jquery-rails>=3.1.4:${PORTSDIR}/www/rubygem-jquery-rails \
		rubygem-mime-types>=0:${PORTSDIR}/misc/rubygem-mime-types \
		rubygem-net-ldap>=0.3.1:${PORTSDIR}/net/rubygem-net-ldap \
		rubygem-rack-openid>=0:${PORTSDIR}/www/rubygem-rack-openid \
		rubygem-ruby-openid>=2.3.0:${PORTSDIR}/net/rubygem-ruby-openid \
		rubygem-rails>=3.2.22:${PORTSDIR}/www/rubygem-rails \
		rubygem-rake>=0:${PORTSDIR}/devel/rubygem-rake \
		rubygem-rbpdf>=0:${PORTSDIR}/print/rubygem-rbpdf \
		rubygem-redcarpet>=3.3.2:${PORTSDIR}/textproc/rubygem-redcarpet \
		rubygem-request_store>=1.1.0:${PORTSDIR}/devel/rubygem-request_store \
		rubygem-rubytree>=0:${PORTSDIR}/devel/rubygem-rubytree

NO_ARCH=	yes
NO_BUILD=	yes
USE_RUBY=	yes
USES=		cpe

USERS=		${WWWOWN}
GROUPS=		${WWWGRP}
PLIST_SUB=	WWWOWN=${WWWOWN} WWWGRP=${WWWGRP}
SUB_LIST=	RUBY_NAME=${RUBY_NAME}

OPTIONS_DEFINE=	MYSQL MYSQL2 POSTGRESQL RMAGIC
OPTIONS_DEFAULT=MYSQL2 RMAGIC THIN
OPTIONS_SINGLE=	WWWSERVER
OPTIONS_SINGLE_WWWSERVER=	THIN PASSENGER
POSTGRESQL_DESC=Enable PostgreSQL support
RMAGIC_DESC=	Enable Gantt charts support
THIN_DESC=	Use Thin WEB server
PASSENGER_DESC=	Use Apache/Nginx WEB server
MYSQL2_DESC=	MySQL database support (via mysql2 rubygem)
NO_OPTIONS_SORT=yes

MYSQL_RUN_DEPENDS=	rubygem-mysql>=2.8.1:${PORTSDIR}/databases/rubygem-mysql
MYSQL2_RUN_DEPENDS=	rubygem-mysql2>=0:${PORTSDIR}/databases/rubygem-mysql2
PASSENGER_RUN_DEPENDS=	passenger-config:${PORTSDIR}/www/rubygem-passenger
POSTGRESQL_RUN_DEPENDS=	rubygem-pg>=0:${PORTSDIR}/databases/rubygem-pg
RMAGIC_EXTRA_PATCHES_OFF=	${FILESDIR}/extra-patch-Gemfile
RMAGIC_RUN_DEPENDS=	rubygem-rmagick>=2.13.4:${PORTSDIR}/graphics/rubygem-rmagick
THIN_EXTRA_PATCHES=	${FILESDIR}/extra-patch-thin-Gemfile
THIN_RUN_DEPENDS=	thin:${PORTSDIR}/www/rubygem-thin
THIN_SUB_LIST=		WWWOWN=${WWWOWN} WWWGRP=${WWWGRP}
THIN_VARS=		USE_RC_SUBR=redmine

post-extract:
	@${RM} ${WRKSRC}/.hgignore ${WRKSRC}/.travis.yml
	@${MV} ${WRKSRC}/config/settings.yml ${WRKSRC}/config/settings.yml-dist

post-patch:
	@${FIND} ${WRKSRC} -name '*.bak' -o -name '*.orig' -delete

pre-install:
	${MKDIR} ${WRKSRC}/public/plugin_assets

do-install:
	${MKDIR} ${STAGEDIR}${WWWDIR}
	${MKDIR} ${STAGEDIR}${WWWDIR}/tmp/pids
	cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${WWWDIR}

post-install:
	${TOUCH} ${STAGEDIR}${WWWDIR}/Gemfile.lock
	if ! [ -r ${STAGEDIR}${WWWDIR}/config/settings.yml ]; then		\
		${INSTALL_DATA} ${STAGEDIR}${WWWDIR}/config/settings.yml-dist	\
			${STAGEDIR}${WWWDIR}/config/settings.yml;		\
	fi

.include <bsd.port.mk>
