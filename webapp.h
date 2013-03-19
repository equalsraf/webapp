#ifndef __WEBAPP__
#define __WEBAPP__

#include <QWebView>
#include <QUrl>
#include <QRegExp>
#include "webpage.h"
#include "networkaccessmanager.h"

//
// TODO
// - Change user agent to Mac
// - Per app cookies
// - Set restart page

class WebApp: public QWebView
{
	Q_OBJECT
public:
	WebApp( const QUrl& start, QWidget *parent=0);

	void setJavascriptEnabled(bool enabled);
	void setAllowed(const QList<QRegExp>& allow) { m_allowed = allow; }
	void setUserAgent(const QString& ua) {m_page->setUserAgent(ua);}

	void load() {load(m_startPage);}
	void load(const QUrl&);
	void load(const QNetworkRequest& request, QNetworkAccessManager::Operation operation = QNetworkAccessManager::GetOperation, 
			const QByteArray & body = QByteArray() );

	virtual bool isAllowed(const QUrl&);
	virtual void loadDisallowedUrl(const QUrl&);
	virtual QNetworkAccessManager* networkAccessManager() { return &nam;};


protected slots:
	virtual void mouseOverLink(const QString& link, const QString& title, const QString& text);

protected:
	virtual QWebView* createWindow(QWebPage::WebWindowType) { return 0; }

protected slots:
	void linkClicked(const QUrl& );
	void viewUrlChanged(const QUrl&);
	void viewIconChanged();
	void viewLoadFinished(bool);
	void restart();
	void toggleFullscreen();

private:
	QList<QRegExp> m_allowed;
	QUrl m_startPage;
	QRegExp redirector;
	WebPage *m_page;
	NetworkAccessManager nam;
};

#endif
