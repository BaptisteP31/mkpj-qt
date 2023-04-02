#ifndef MAKEFILE_H
#define MAKEFILE_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QRegularExpression>

class Makefile
{
private:
    QString compiler;
    QVector<QString> cFlags;
    QVector<QString> ldLibs;
    //QVector<QString> ldFlags;
    QDir srcDir;
    QDir objDir;
    QDir binDir;
    QString target;

public:
    Makefile();
    Makefile(const Makefile &src);
    Makefile(QString _compiler, QVector<QString> _cFlags, QVector<QString> _ldLibs, QDir _objDir, QDir _binDir, QString _target);

    // Setters
    inline void setCompiler(QString _compiler) { compiler = _compiler; }
    inline void setFlags(QVector<QString> _flags) { cFlags = _flags; }
    inline void setLibs(QVector<QString> _libs) { ldLibs = _libs; }

    inline void addFlag(QString _flag)
    {
        if (!cFlags.contains(_flag))
            cFlags.append(_flag);
    }

    inline void addLib(QString _lib)
    {
        if (!ldLibs.contains(_lib))
            ldLibs.append(_lib);
    }


    //inline void setLdFlags(QVector<QString> _ldFlags) { ldFlags = _ldFlags; }
    //inline void addLdFlag(QString _ldFlag) { ldFlags.append(_ldFlag); }
    inline void setSrcDir(QDir _srcDir) { srcDir = _srcDir; }
    inline void setSrcDir(QString _srcDir) { setSrcDir(QDir(_srcDir)); }
    inline void setObjDir(QDir _objDir) { objDir = _objDir; }
    inline void setObjDir(QString _objDir) { setObjDir(QDir( _objDir)); }
    inline void setBinDir(QDir _binDir) { binDir = _binDir; }
    inline void setBinDir(QString _binDir) {setBinDir(QDir(_binDir)); }


    // Getters
    inline QString getCompiler() const { return compiler;}
    inline QVector<QString> getFlags() const { return cFlags; }
    inline QVector<QString> getLibs() const { return ldLibs; }
    //inline QVector<QString> getLdFlags() const { return ldFlags; }
    inline QDir getSrcDir() const { return srcDir; }
    inline QDir getObjDir() const { return objDir; }
    inline QDir getBinDir() const { return binDir; }
    inline QString getTarget() const { return target; }


    // Methods
    static Makefile parseMakefile(const QString& filename);
    QString generate();


    // Operators
    Makefile& operator=(const Makefile& src);

    friend QDebug operator<<(QDebug debug, const Makefile& makefile);
};

QDebug operator<<(QDebug debug, const Makefile& makefile);

#endif // MAKEFILE_H
