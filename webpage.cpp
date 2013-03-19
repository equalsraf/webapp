#include "webpage.h"
#include <QtCore>
#include <QNetworkRequest>
#include <QWebFrame>
#include "webapp.h"

WebPage::WebPage(WebApp *app)
:QWebPage(app), m_app(app)
{
	setNetworkAccessManager(m_app->networkAccessManager());
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
					QWebPage::NavigationType t)
{
	if (m_app->isAllowed(req.url())) {
		return QWebPage::acceptNavigationRequest(frame, req, t);
	}

	if ( t == QWebPage::NavigationTypeLinkClicked ) {
		m_app->loadDisallowedUrl(req.url());
	}
	return false;
}



