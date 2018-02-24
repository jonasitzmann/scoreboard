#include <QString>
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
void ErrorHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    const char* msg = str.toStdString().c_str();
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s\n", msg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "\033[1;33mWarning\033[0m: %s\n", msg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "\033[31mCritical\033[0m: %s\n", msg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "\033[31mFatal\033[0m: %s\n", msg);
            abort();
    }
}
#endif // ERRORHANDLER_H
