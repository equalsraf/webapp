#ifndef WEBAPP_NAM
#define WEBAPP_NAM

#include <QNetworkAccessManager>

class WebApp;

class NetworkAccessManager: public QNetworkAccessManager
{
public:
	NetworkAccessManager(WebApp *app);

private:
	WebApp *m_app;

};


#endif

