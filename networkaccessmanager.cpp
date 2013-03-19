#include "networkaccessmanager.h"
#include "cookiejar.h"


NetworkAccessManager::NetworkAccessManager(WebApp *app)
:QNetworkAccessManager(app), m_app(app)
{
	setCookieJar(new CookieJar(app));
}


