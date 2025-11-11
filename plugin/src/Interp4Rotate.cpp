#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _obj_name(""), _axis_name(""), _rotation_speed_deg(0.0), _rotation_angle_deg(0.0)
{
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _axis_name << " " << _rotation_speed_deg << " " << _rotation_angle_deg << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn,
                            const char *sMobObjName,
                            AbstractComChannel &rComChann)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if (!(Strm_CmdsList >> _obj_name))
  {
    std::cout << "Nie wczytano poprawnie nazwy obiektu " << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _axis_name))
  {
    std::cout << "Nie wczytano poprawnie nazwy osi " << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _rotation_speed_deg))
  {
    std::cout << "Nie wczytano poprawnie predkosci katowej " << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _rotation_angle_deg))
  {
    std::cout << "Nie wczytano poprawnie kata obrotu " << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate NazwaObiektu NazwaOsi SzybkoscKatowa[deg/s] KatObrotu[deg]" << endl;
}
