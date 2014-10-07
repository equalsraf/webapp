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

bool WebPage::supportsExtension(Extension extension) const
{
	if ( extension == QWebPage::ErrorPageExtension ) {
		return true;
	}
	return QWebPage::supportsExtension(extension);
}

bool WebPage::extension(Extension extension, const ExtensionOption *option, ExtensionReturn *output)
{
	if (extension != ErrorPageExtension) {
		return QWebPage::extension(extension, option, output);
	}

	const ErrorPageExtensionOption *opt = static_cast<const ErrorPageExtensionOption*>(option);
	ErrorPageExtensionReturn *ret = static_cast<ErrorPageExtensionReturn*>(output);
	ret->content = opt->errorString.toUtf8();
	qDebug() << __func__ << opt->errorString ;
	return true;
}

