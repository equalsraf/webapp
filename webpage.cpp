#include "webpage.h"


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

