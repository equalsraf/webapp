#ifndef __WEBAPP_WEBPAGE__
#define __WEBAPP_WEBPAGE__

#include <QWebPage>

class WebPage: public QWebPage
{

public:
	void setUserAgent(const QString&);

protected:
	virtual QString userAgentForUrl(const QUrl& url) const;

private:
	QString m_userAgent;

};

#endif
