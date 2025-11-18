#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "ProgramInterpreter.hh"
#include "xmlinterp.hh"
#include "Configuration.hh"
#include "Cuboid.hh"

using namespace xercesc;

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

bool ProgramInterpreter::OpenConnection()
{
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    int Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (Socket < 0)
    {
        std::cerr << "*** Blad otwarcia gniazda." << std::endl;
        return false;
    }

    _Chann2Serv.Init(Socket);

    if (connect(Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
        std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
        return false;
    }
    return true;
}

bool ProgramInterpreter::init()
{
    if (!OpenConnection())
    {
        return false;
    }
    return true;
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

        if (!pCmd->ExecCmd(_Scn, NULL, _Chann2Serv))
        {
            std::cerr << "Niepowodzenie wykonania polecenia" << std::endl;
            return false;
        }
    }
    return true;
}

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ProgramInterpreter::Read_XML_Config(const char *sFileName)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException &toCatch)
    {
        char *message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during initialization! :\n";
        std::cerr << "Exception message is: \n"
                  << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    SAX2XMLReader *pParser = XMLReaderFactory::createXMLReader();

    pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(XMLUni::fgXercesDynamic, false);
    pParser->setFeature(XMLUni::fgXercesSchema, true);
    pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

    pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

    Configuration rConfig;

    DefaultHandler *pHandler = new XMLInterp4Config(rConfig);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try
    {

        if (!pParser->loadGrammar("config/config.xsd",
                                  xercesc::Grammar::SchemaGrammarType, true))
        {
            std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
                      << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
                      << std::endl;
            return false;
        }
        pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
        pParser->parse(sFileName);
    }
    catch (const XMLException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        std::cerr << "Informacja o wyjatku: \n"
                  << "   " << sMessage << "\n";
        XMLString::release(&sMessage);
        return false;
    }
    catch (const SAXParseException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

        std::cerr << "Blad! " << std::endl
                  << "    Plik:  " << sSystemId << std::endl
                  << "   Linia: " << Exception.getLineNumber() << std::endl
                  << " Kolumna: " << Exception.getColumnNumber() << std::endl
                  << " Informacja: " << sMessage
                  << std::endl;

        XMLString::release(&sMessage);
        XMLString::release(&sSystemId);
        return false;
    }
    catch (...)
    {
        std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
        return false;
    }

    // Dalej obsluzenie configu
    for (const std::string &path : rConfig.GetLibraryPaths())
    {
        _LibManager.AddLibInterface(path);
    }

    _Chann2Serv.Clear();
    for (const CuboidConfig &cuboid : rConfig.GetCuboids())
    {
        Cuboid *pCuboid = new Cuboid();
        pCuboid->SetName(cuboid.Name.c_str());
        pCuboid->SetPosition_m(cuboid.Trans_m);
        pCuboid->SetAng_Roll_deg(cuboid.RotXYZ_deg[0]);
        pCuboid->SetAng_Pitch_deg(cuboid.RotXYZ_deg[1]);
        pCuboid->SetAng_Yaw_deg(cuboid.RotXYZ_deg[2]);

        if (_Chann2Serv.AddObj(cuboid.Name, cuboid.Shift, cuboid.Scale,
                               cuboid.RotXYZ_deg, cuboid.Trans_m,
                               cuboid.RGB))
        {
            _Scn.AddMobileObj(pCuboid);
            std::cout << "Dodano obiekt: " << cuboid.Name << std::endl;
        }
        else
        {
            std::cerr << "Nie dodano obiektu: " << cuboid.Name << std::endl;
        }
    }

    delete pParser;
    delete pHandler;
    return true;
}

ProgramInterpreter::~ProgramInterpreter()
{
    _Chann2Serv.Close();

    close(_Chann2Serv.GetSocket());
}