#ifndef MAKEFILE_H
#define MAKEFILE_H

#include <QString>
#include <QVector>
#include <QDir>

class makefile
{
private:
    QString compiler;
    QVector<QString> cFlags;
    QVector<QString> ldLibs;
    QDir srcDir;
    QDir objDir;
    QDir binDir;
    QString target;

public:
    makefile();

    // Setters
    void setCompiler(QString _compiler);
    void setFlags(QVector<QString> flags);
    void addFlag(QString _flag);
    void setLibs(QString _libs);
    void addLib(QString _lib);
    void setSrcDir(QDir _srcDir);
    inline void setSrcDir(QString _srcDir) { setSrcDir(QDir(_srcDir)); }
    void setObjDir(QDir _objDir);
    inline void setObjDir(QString _objDir) { setObjDir(QDir( _objDir)); }
    void setBinDir(QDir _binDir);
    inline void setBinDir(QString _binDir) {setBinDir(QDir(_binDir)); }


    // Getters
    inline QString getCompiler() const { return compiler;}
    inline QVector<QString> getFlags() const { return cFlags; }
    inline QVector<QString> getLibs() const { return ldLibs; }
    inline QDir getSrcDir() const { return srcDir; }
    inline QDir getObjDir() const { return objDir; }
    inline QDir getBinDir() const { return binDir; }
    inline QString getTarget() const { return target; }

};

#endif // MAKEFILE_H
