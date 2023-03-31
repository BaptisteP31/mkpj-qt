
#include "makefile.h"

Makefile::Makefile()
    : compiler("g++")
    , srcDir("src")
    , objDir("obj")
    , binDir("bin")
    , target("main")
{

}

Makefile::Makefile(const Makefile &src)
    : compiler(src.compiler)
    , cFlags(src.cFlags)
    , ldLibs(src.ldLibs)
    , srcDir(src.srcDir)
    , objDir(src.objDir)
    , binDir(src.binDir)
    , target(src.target)
{

}

Makefile::Makefile(QString _compiler, QVector<QString> _cFlags, QVector<QString> _ldLibs, QDir _objDir, QDir _binDir, QString _target)
    : compiler(_compiler)
    , cFlags(_cFlags)
    , ldLibs(_ldLibs)
    , objDir(_objDir)
    , binDir(_binDir)
    , target(_target)
{

}

Makefile& Makefile::operator=(const Makefile& src)
{
    compiler = src.compiler;
    cFlags = src.cFlags;
    ldLibs = src.ldLibs;
    srcDir = src.srcDir;
    objDir = src.srcDir;
    binDir = src.binDir;
    target = src.target;

    return *this;
}

QDebug operator<<(QDebug debug, const Makefile& makefile) {
    debug
        << "Compiler: " << makefile.getCompiler() << "\n"
        << "CFlags: " << makefile.getFlags() << "\n"
        << "LDLibs: " << makefile.getLibs() << "\n"
        << "srcDir: " << makefile.getSrcDir() << "\n"
        << "objDir: " << makefile.getObjDir() << "\n"
        << "binDir: " << makefile.getBinDir() << "\n"
        << "Target: " << makefile.getTarget() << "\n"
        ;

    return debug;
}

