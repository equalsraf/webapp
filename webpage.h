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

protected:
	virtual QString userAgentForUrl(const QUrl& url) const;
	virtual bool acceptNavigationRequest(QWebFrame *, const QNetworkRequest &,
					QWebPage::NavigationType);

private:
	QString m_userAgent;
	WebApp *m_app;
};

#endif
