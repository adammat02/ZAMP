#include "preprocesor.hh"

bool ExecPreprocesor(const char* NazwaPliku, std::string &String4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;

    Cmd4Preproc += NazwaPliku;

    FILE* pProc = popen(Cmd4Preproc.c_str(), "r");
    if (!pProc) {
        std::cerr << "Błąd: nie można uruchomić preprocesora!\n";
        return false;
    }

    while (fgets(Line, LINE_SIZE, pProc)) {
        OTmpStrm << Line;
    }

    String4Cmds = OTmpStrm.str();

    return pclose(pProc) == 0;
}