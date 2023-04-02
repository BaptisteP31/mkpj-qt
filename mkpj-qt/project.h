#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "makefile.h"

class Project
{
private:
    QString name;
    QDir directory;
    Makefile makefile;

public:
    Project()=delete;
    Project(QString _name, QDir _directory, Makefile _makefile);
    Project(QString _name, QDir _directory);

    // Getters
    inline QString getName() const {return name;}
    inline Makefile getMakefile() const {return makefile;}
    inline QDir getDirectory() const {return directory;}

    //static Project load();

    QString toQString() const;
    void outputMakefile(QString name="Makefile");

    // This will need to change later
    friend std::ostream& operator<<(std::ostream& out, const Project pr);

    friend QDebug operator<<(QDebug debug, const Project& project);
};

std::ostream& operator<<(std::ostream& out, const Project pr);
QDebug operator<<(QDebug debug, const Project& porject);

#endif // PROJECT_H
