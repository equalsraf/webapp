#include "webapp.h"
#include <QAction>
#include <QWebFrame>
#include <QtCore>
#include <QDesktopServices>
#include <QNetworkRequest>
#include <QShortcut>

WebApp::WebApp(const QUrl& start, QWidget *parent)
:QWebView(parent), m_startPage(start)
{
	m_page = new WebPage(this);
	setPage(m_page);

	connect(m_page, SIGNAL(linkHovered(QString, QString, QString)),
		this, SLOT(mouseOverLink(QString, QString, QString)));

	QWebSettings *s = settings()->globalSettings();

	s->setAttribute( QWebSettings::DnsPrefetchEnabled, true);
	s->setAttribute( QWebSettings::PrivateBrowsingEnabled, true);

	QList<QWebPage::WebAction> actions;
	actions << QWebPage::OpenLinkInNewWindow
		<< QWebPage::OpenFrameInNewWindow
		<< QWebPage::OpenImageInNewWindow
		<< QWebPage::Back
		<< QWebPage::Forward
		<< QWebPage::Stop
		<< QWebPage::StopScheduledPageRefresh;

	foreach( QWebPage::WebAction webaction, actions ) {
		QAction *act = pageAction(webaction);

		if ( act ) {
			act->setVisible(false);
			act->setEnabled(false);
		}
	}

	QShortcut *f5 = new QShortcut( QKeySequence::Refresh, this);
	connect(f5, SIGNAL(activated()), 
			this, SLOT(restart()));

	connect(this, SIGNAL(titleChanged(QString)),
			this, SLOT(setWindowTitle(QString)));
	connect(this, SIGNAL(iconChanged()),
			this, SLOT(viewIconChanged()));
	connect(this, SIGNAL(loadFinished(bool)),
			this, SLOT(viewLoadFinished(bool)));

	page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAsNeeded);

	connect( page(), SIGNAL(linkClicked(QUrl)),
			this, SLOT(linkClicked(QUrl)));
	page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);

	connect(this, SIGNAL(urlChanged(QUrl)),
			this, SLOT(viewUrlChanged(QUrl)));
}

void WebApp::restart()
{
	load(m_startPage);
}

void WebApp::setJavascriptEnabled(bool enabled)
{
	QWebSettings *s = settings()->globalSettings();
	s->setAttribute( QWebSettings::JavascriptEnabled, enabled);
}

void WebApp::load(const QUrl& url)
{
	if ( isAllowed(url) ) {
		QWebView::load(url);
	} else {
		loadDisallowedUrl(url);
	}
}

void WebApp::load(const QNetworkRequest& request, QNetworkAccessManager::Operation operation, const QByteArray& body)
{
	if ( isAllowed(request.url().host()) ) {
		QWebView::load(request, operation, body);
	} else {
		qDebug() << "request blocked";
	}
}

void WebApp::loadDisallowedUrl(const QUrl& url)
{
	qDebug()  << __func__ << url;

	if ( url.isRelative() ) {
		return;
	} else if ( url.scheme() == "about" ) {
		return;
	}

	QDesktopServices::openUrl(url);
}

void WebApp::viewUrlChanged(const QUrl& url)
{
	qDebug() << __func__ << url;
	//setWindowModified(true);
}

void WebApp::linkClicked(const QUrl& url)
{
	if ( isAllowed(url) ) {
		load(url);
	} else {
		loadDisallowedUrl(url);
	}
}

bool WebApp::isAllowed(const QUrl& u)
{
	QUrl test_url = u;
	if (u.isRelative()) {
		test_url = url().resolved(u);
	}

	foreach( QRegExp exp, m_allowed ) {

		if ( exp.exactMatch(test_url.host()) ) {
			return true;
		}
	}

	return false;
}

void WebApp::viewIconChanged()
{
	setWindowIcon(icon());
}

void WebApp::viewLoadFinished(bool ok)
{
	qDebug() << __func__ << ok;
}

void WebApp::mouseOverLink(const QString& link, const QString& title, const QString& text)
{
	setToolTip(link);
}

