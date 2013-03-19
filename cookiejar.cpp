#include "cookiejar.h"


CookieJar::CookieJar(WebApp* app)
:QNetworkCookieJar(app), m_app(app)
{

}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookies, const QUrl& url)
{
	if ( !m_app->isAllowed(url) ) {
		return false;
	}

	// Ignore Analytics cookies
	QList<QNetworkCookie> lst;
        foreach (QNetworkCookie cookie, cookies) {
		if ( !cookie.name().startsWith("__utm") ) {
			lst += cookie;
		}

	}
	QNetworkCookieJar::setCookiesFromUrl(lst, url);
	return true;
}
