#ifndef __WEBAPP_WEBPAGE__
#define __WEBAPP_WEBPAGE__

#include <QWebPage>

class WebApp;

class WebPage: public QWebPage
{
	Q_OBJECT
public:
	WebPage(WebApp *app);
	void setUserAgent(const QString&);
	virtual bool supportsExtension(Extension extension) const;
	virtual bool extension(Extension extension, const ExtensionOption *option=0, ExtensionReturn *output=0);

protected:
	virtual QString userAgentForUrl(const QUrl& url) const;
	virtual bool acceptNavigationRequest(QWebFrame *, const QNetworkRequest &,
					QWebPage::NavigationType);

private:
	QString m_userAgent;
	WebApp *m_app;
};

#endif
