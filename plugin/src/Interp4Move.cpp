#include <iostream>
#include <unistd.h>
#include "Interp4Move.hh"
#include "Vector3D.hh"

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
  cout << GetCmdName() << " " << _obj_name << " " << _Speed_mmS << " " << _Distance << endl;
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
  AbstractMobileObj *pMobObj = rScn.FindMobileObj(_obj_name.c_str());
  if (pMobObj == nullptr)
  {
    std::cout << "Nie znaleziono obiektu o nazwie: " << _obj_name << std::endl;
    return false;
  }

  double step_dist = _Distance / N;
  double step_time_us = std::fabs(_Distance / _Speed_mmS) * 1e6 / N;
  Vector3D current_pos = pMobObj->GetPositoin_m();
  double current_x_deg = pMobObj->GetAng_Roll_deg();
  double current_y_deg = pMobObj->GetAng_Pitch_deg();
  double current_z_deg = pMobObj->GetAng_Yaw_deg();

  for (int i = 0; i < N; ++i)
  {
    pMobObj->LockAccess();

    current_pos[0] += step_dist * cos(current_y_deg * M_PI / 180.0) * cos(current_z_deg * M_PI / 180.0);
    current_pos[1] += step_dist * cos(current_y_deg * M_PI / 180.0) * sin(current_z_deg * M_PI / 180.0);
    current_pos[2] -= step_dist * sin(current_y_deg * M_PI / 180.0);

    pMobObj->SetPosition_m(current_pos);

    rComChann.LockAccess();

    if (!rComChann.UpdateObj(_obj_name, Vector3D(current_x_deg, current_y_deg, current_z_deg),
                             current_pos))
    {
      std::cout << "Blad aktualizacji obiektu o nazwie: " << _obj_name << std::endl;
      rComChann.UnlockAccess();
      pMobObj->UnLockAccess();
      return false;
    }

    rComChann.UnlockAccess();
    pMobObj->UnLockAccess();

    usleep(step_time_us);
  }

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
