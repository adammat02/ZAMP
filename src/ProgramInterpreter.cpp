#include "ProgramInterpreter.hh"

bool ProgramInterpreter::ExecPreprocesor(const char *NazwaPliku, std::istringstream &Stream4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;

    Cmd4Preproc += NazwaPliku;

    FILE *pProc = popen(Cmd4Preproc.c_str(), "r");
    if (!pProc)
    {
        std::cerr << "Błąd: nie można uruchomić preprocesora!\n";
        return false;
    }

    while (fgets(Line, LINE_SIZE, pProc))
    {
        OTmpStrm << Line;
    }

    Stream4Cmds.str(OTmpStrm.str());
    Stream4Cmds.clear();

    return pclose(pProc) == 0;
}

bool ProgramInterpreter::ExecProgram(const char *NazwaPliku)
{
    std::istringstream Stream4Cmds;
    std::string slowo;

    if (!ExecPreprocesor(NazwaPliku, Stream4Cmds))
    {
        std::cerr << "Blad preprocesora" << std::endl;
        return false;
    }

    while (Stream4Cmds >> slowo)
    {
        std::shared_ptr<LibraryInterface> pLibInter = _LibManager.GetLibInterface(slowo);
        if (pLibInter == nullptr)
        {
            std::cerr << "Nieznaleziono wtyczki dla " << slowo << std::endl;
            return false;
        }

        std::unique_ptr<AbstractInterp4Command> pCmd(pLibInter->GetCmd());
        if (!pCmd)
        {
            std::cerr << "Niemozna utworzyc instancji polecenia" << std::endl;
            return false;
        }

        if (!pCmd->ReadParams(Stream4Cmds))
        {
            std::cerr << "Niewczytano parametrow" << std::endl;
            return false;
        }

        // if (!pCmd->ExecCmd(_Scn, NULL, _Chann2Serv))
        // {
        //     std::cerr << "Niepowodzenie wykonania polecenia" << std::endl;
        //     return false;
        // }
        pCmd->PrintCmd();
    }
    return true;
}

void ProgramInterpreter::AddLibrary(const std::string &LibName)
{
    _LibManager.AddLibInterface(LibName);
}
