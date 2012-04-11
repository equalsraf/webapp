#include "webpage.h"
#include <QtCore>
#include <QNetworkRequest>
#include "webapp.h"

WebPage::WebPage(WebApp *app)
:QWebPage(app), m_app(app)
{
}

void WebPage::setUserAgent(const QString& ua)
{
	m_userAgent = ua;
}

QString WebPage::userAgentForUrl(const QUrl& url) const
{
	if ( m_userAgent.isEmpty() ) {
		return QWebPage::userAgentForUrl(url);
	}

	return m_userAgent;
}


bool WebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &req,
					QWebPage::NavigationType)
{
	if (m_app->isAllowed(req.url())) {
		return true;
	}

	m_app->loadDisallowedUrl(req.url());
	return false;
}

