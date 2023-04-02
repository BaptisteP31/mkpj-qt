
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

QString Makefile::generate()
{
    QString makefile;

    // Compiler
    makefile.append("CC = " + compiler + '\n');

    // Compiler flags
    makefile.append("CFLAGS = ");
    for (QString &flag : cFlags)
        makefile.append(flag + " ");

    makefile.append('\n');

    // Linker libs
    makefile.append("LDLIBS = ");
    for (QString &lib : ldLibs)
        makefile.append(lib + " ");

    makefile.append('\n');

    // Directories
    makefile.append("SRC = $(wildcard " + srcDir.dirName() + "/*.cpp" + '\n');
    makefile.append("OBJ = $(SRC:" + srcDir.dirName() +"/%.cpp=" + objDir.dirName() + "/%.o)" + '\n');
    makefile.append("BIN = " + binDir.dirName() + '\n');

    // Target
    makefile.append("TARGET = " + target + '\n');

    // Non configurable part of the makefile
    makefile.append('\n');
    makefile.append("all: $(TARGET)");
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("$(TARGET): $(OBJ)");
    makefile.append('\n');
    makefile.append("   $(CC) $(LDFLAGS) -o $(BIN)/$@ $^ $(LDLIBS)");
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("obj/%.o: src/%.cpp");
    makefile.append('\n');
    makefile.append("	$(CC) $(CFLAGS) -o $@ -c $<");
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("clean:");
    makefile.append('\n');
    makefile.append("	rm -f $(OBJ) $(BIN)/$(TARGET)");
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("fclean: clean");
    makefile.append('\n');
    makefile.append("	rm -f $(TARGET) $(BIN)/$(TARGET)");
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("configure:");
    makefile.append('\n');
    makefile.append("	mkdir -p " + objDir.dirName() + " && mkdir -p " + binDir.dirName());
    makefile.append('\n');
    makefile.append('\n');
    makefile.append("install: configure all");
    makefile.append('\n');
    makefile.append("	sudo cp $(BIN)/$(TARGET) /usr/local/bin");

    return makefile;
}

