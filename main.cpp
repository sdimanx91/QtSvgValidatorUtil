#include <QtSvg/QSvgRenderer>
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>

void printArgcHelp()
{
	qInfo() << "---------- using validator ----------";
	qInfo() << "android_svg_validator <svgFileName>";
}

int badResult(const QString & msg)
{
	qWarning() << "ERROR: " << msg;
	printArgcHelp();
	return 1;
}

QString parseFileName(int argc, char *argv[])
{
	if (argc < 2) {
		return QString();
	}
	return QString::fromStdString( argv[1] );
}

int main(int argc, char *argv[])
{
	const QString fileName = parseFileName(argc, argv);
	if (fileName.isEmpty()) return
		badResult(QStringLiteral("file name is not provided"));

	const QFileInfo fileInfo = QFileInfo(fileName);
	if (!fileInfo.exists())
		return badResult(QStringLiteral("file is not exists"));
	if (fileInfo.suffix() != QStringLiteral("svg"))
		return badResult(QStringLiteral("Invalid file name suffix. Expected .svg."));

	if (!QSvgRenderer(fileName).isValid())
		return badResult(QStringLiteral("Invalid svg!"));

	qInfo() << "SUCCESS: Svg file is valid";

	return 0;
}
