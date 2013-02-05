#include <QtGui>
#include "webapp.h"

int main(int ac, char **av)
{
	QApplication app(ac,av);

	if ( app.arguments().size() != 2 ) {
		qDebug() << "Usabe: webapp <config file>";
		return -1;
	}

	// FIXME: check file
	QSettings settings(app.arguments()[1], QSettings::IniFormat);

	if ( !settings.contains("start_url") ) {
		qDebug() << "The config file is missing a start_url option";
		return -1;
	}

	if ( !settings.contains("allowed_domains") ) {
		qDebug() << "The config file is missing an allowed_domains option";
		return -1;
	}

	WebApp wa(QUrl(settings.value("start_url").toString()));
	wa.setJavascriptEnabled( settings.value("javascript_enabled", true).toBool() );

	if ( settings.contains("user_agent") ) {
		wa.setUserAgent( settings.value("user_agent").toString() );
	}

	QList<QVariant> domains = settings.value("allowed_domains").toList();
	QList<QRegExp> allowed;
	foreach(QVariant domain, domains) {
		allowed << QRegExp(domain.toString().trimmed(), Qt::CaseInsensitive, QRegExp::Wildcard);
	}
	wa.setAllowed(allowed);

	if ( settings.contains("icon") ) {
		wa.setWindowIcon(QIcon(settings.value("icon").toString()));
	}

	wa.load();
	wa.show();

	return app.exec();
}

