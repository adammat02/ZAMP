#include <iostream>
#include "Interp4Move.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _obj_name(""), _Speed_mmS(0.0), _Distance(0.0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _obj_name << " " << _Speed_mmS  << " " << _Distance << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(AbstractScene &rScn,
                          const char *sMobObjName,
                          AbstractComChannel &rComChann)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  AbstractMobileObj * pMobObj = rScn.FindMobileObj(_obj_name.c_str());
  if (pMobObj == nullptr)
  {
    std::cout << "Nie znaleziono obiektu o nazwie: " << _obj_name << std::endl;
    return false;
  }
  PrintCmd();
  
  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if (!(Strm_CmdsList >> _obj_name))
  {
    std::cout << "Nie wczytano poprawnie nazwy obiektu " << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> _Speed_mmS))
  {
    std::cout << "Nie wczytano poprawnie predkosci " << std::endl;
    return false;
  }

  if (!(Strm_CmdsList >> _Distance))
  {
    std::cout << "Nie wczytano poprawnie odleglosci " << std::endl;
    return false;
  }

  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
