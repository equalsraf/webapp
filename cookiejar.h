#ifndef WEBAPP_COOKIEJAR
#define WEBAPP_COOKIEJAR

#include <QNetworkCookieJar>
#include "webapp.h"

class CookieJar: public QNetworkCookieJar {

public:
	CookieJar(WebApp *);
	//virtual QList<QNetworkCookie> cookiesForUrl(const QUrl&);
	virtual bool setCookiesFromUrl(const QList<QNetworkCookie> &cookies, const QUrl& url);

private:
	WebApp *m_app;

};

#endif
