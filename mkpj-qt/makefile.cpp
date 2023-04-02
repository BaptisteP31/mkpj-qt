
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
        //<< "LdFlags: " << makefile.getLdFlags() << "\n"
        << "LDLibs: " << makefile.getLibs() << "\n"
        << "srcDir: " << makefile.getSrcDir() << "\n"
        << "objDir: " << makefile.getObjDir() << "\n"
        << "binDir: " << makefile.getBinDir() << "\n"
        << "Target: " << makefile.getTarget() << "\n"
        ;

    return debug;
}


Makefile Makefile::parseMakefile(const QString& filename)
{
    Makefile makefile;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << filename;
        return makefile;
    }

    static QRegularExpression compilerRegex("^CC\\s*=\\s*(.*)$");
    static QRegularExpression cFlagsRegex("^CFLAGS\\s*=\\s*(.*)$");
    //static QRegularExpression ldFlagsRegex("^LDFLAGS\\s*=\\s*(.*)$");
    static QRegularExpression ldLibsRegex("^LDLIBS\\s*=\\s*(.*)$");
    static QRegularExpression srcRegex("^SRC\\s*=\\s*(.*)$");
    static QRegularExpression objRegex("^OBJ\\s*=\\s*(.*)$");
    static QRegularExpression binRegex("^BIN\\s*=\\s*(.*)$");
    static QRegularExpression targetRegex("^TARGET\\s*=\\s*(.*)$");

    while (!file.atEnd())
    {
        QString line = file.readLine().trimmed();

        if (compilerRegex.match(line).hasMatch())
        {
            makefile.compiler = compilerRegex.match(line).captured(1).trimmed();
        }
        else if (cFlagsRegex.match(line).hasMatch())
        {
            QString flags = cFlagsRegex.match(line).captured(1).trimmed();
            makefile.cFlags = flags.split(" ", Qt::SkipEmptyParts).toVector();
        }
        else if (ldLibsRegex.match(line).hasMatch())
        {
            QString libs = ldLibsRegex.match(line).captured(1).trimmed();
            makefile.ldLibs = libs.split(" ", Qt::SkipEmptyParts).toVector();
        }
        /* I have no idea why, ldflags does not function properly
        else if (ldFlagsRegex.match(line).hasMatch())
        {
            QString ldf = ldFlagsRegex.match(line).captured(1).trimmed();
            makefile.ldFlags = ldf.split(" ", Qt::SkipEmptyParts).toVector();
        }
        */
        else if (srcRegex.match(line).hasMatch())
        {
            QString src = srcRegex.match(line).captured(1).trimmed();
            makefile.srcDir = QDir(src);
        }
        else if (objRegex.match(line).hasMatch())
        {
            QString obj = objRegex.match(line).captured(1).trimmed();
            makefile.objDir = QDir(obj);
        }
        else if (binRegex.match(line).hasMatch())
        {
            QString bin = binRegex.match(line).captured(1).trimmed();
            makefile.binDir = QDir(bin);
        }
        else if (targetRegex.match(line).hasMatch())
        {
            makefile.target = targetRegex.match(line).captured(1).trimmed();
        }
    }
    return makefile;
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

    // Linker flags
    makefile.append("LDFLAGS = ");
    //for (QString &flag: ldFlags)
    //    makefile.append(flag + " ");

    makefile.append('\n');

    // Linker libs
    makefile.append("LDLIBS = ");
    for (QString &lib : ldLibs)
        makefile.append(lib + " ");

    makefile.append('\n');

    // Directories
    makefile.append("SRC = $(wildcard " + srcDir.dirName() + "/*.cpp" + '\n');
    makefile.append("OBJ = $(SRC:" + srcDir.dirName() +"/%.cpp=" + objDir.dirName() + "/%.o" + '\n');
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

