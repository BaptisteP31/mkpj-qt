#include "project.h"

Project::Project(QString _name, QDir _directory)
    : name(_name), directory(_directory)
{
    if(!directory.exists(name))
        directory.mkpath(name);
    else
        qDebug() << "The directory already exists !";
}

std::ostream& operator<<(std::ostream& out, const Project pr) {
    out << pr.toQString().toStdString();
    return out;
}


QString Project::toQString() const {
    return QString(name);
}
