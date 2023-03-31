
#include "makefile.h"

Makefile::Makefile()
    : compiler("g++")
    , srcDir("src")
    , objDir("obj")
    , binDir("bin")
    , target("main")
{

}

Makefile::Makefile(Makefile &src)
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

