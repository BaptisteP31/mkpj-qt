#include "project.h"

Project::Project(QString _name, QDir _directory, Makefile _makefile)
    : name(_name), directory(_directory), makefile(_makefile)
{
    if(!directory.exists(name))
        directory.mkpath(name);
    else
        qDebug() << "The directory already exists !";
}

Project::Project(QString _name, QDir _directory)
    : name(_name), directory(_directory)
{

}

std::ostream& operator<<(std::ostream& out, const Project pr) {
    out << pr.toQString().toStdString();
    return out;
}


QString Project::toQString() const {
    return QString(name);
}

void Project::outputMakefile(QString name)
{
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Unable to write to " + name.toStdString());

    QTextStream out(&file);
    out << makefile.generate();
}

QDebug operator<<(QDebug debug, const Project& project)
{
    debug << project.name << " at " << project.directory << "\n" << project.makefile;
    return debug;
}
