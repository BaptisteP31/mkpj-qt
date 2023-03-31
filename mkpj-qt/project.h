#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>

class Project
{
private:
    QString name;
    QDir directory;

public:
    Project()=delete;
    Project(QString _name, QDir _directory);

    //static Project load();

    QString toQString() const;

    inline QString getName() const {return name;}

    // This will need to change later
    friend std::ostream& operator<<(std::ostream& out, const Project pr);
};

std::ostream& operator<<(std::ostream& out, const Project pr);

#endif // PROJECT_H
