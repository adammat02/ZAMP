#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : _obj_name(""), _pos_x_m(0.0), _pos_y_m(0.0), _pos_z_m(0.0),
                           _angle_x_deg(0.0), _angle_y_deg(0.0), _angle_z_deg(0.0)
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _obj_name << " " << _pos_x_m << " " << _pos_y_m << " " << _pos_z_m
       << " " << _angle_x_deg << " " << _angle_y_deg << " " << _angle_z_deg << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(AbstractScene &rScn,
                         const char *sMobObjName,
                         AbstractComChannel &rComChann)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  AbstractMobileObj *pMobObj = rScn.FindMobileObj(_obj_name.c_str());
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
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if (!(Strm_CmdsList >> _obj_name))
  {
    std::cout << "Nie wczytano poprawnie nazwy obiektu." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _pos_x_m))
  {
    std::cout << "Nie wczytano poprawnie współrzędnej X." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _pos_y_m))
  {
    std::cout << "Nie wczytano poprawnie współrzędnej Y." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _pos_z_m))
  {
    std::cout << "Nie wczytano poprawnie współrzędnej Z." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _angle_x_deg))
  {
    std::cout << "Nie wczytano poprawnie kąta obrotu wokół osi X." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _angle_y_deg))
  {
    std::cout << "Nie wczytano poprawnie kąta obrotu wokół osi Y." << std::endl;
    return false;
  }
  if (!(Strm_CmdsList >> _angle_z_deg))
  {
    std::cout << "Nie wczytano poprawnie kąta obrotu wokół osi Z." << std::endl;
    return false;
  }

  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set NazwaObiektu wspX[m] wspY[m] wspZ[m] katOX[deg] katOY[deg] katOZ[deg]" << endl;
}
