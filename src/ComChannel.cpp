#include "ComChannel.hh"


bool ComChannel::Send(int Sk2Server, const char *sMesg)
{
  ssize_t IlWyslanych;
  ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0)
  {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0)
  {
    std::cerr << "*** Blad przeslania napisu." << std::endl;
    return false;
  }
  return true;
}

bool ComChannel::AddObj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale,
                        const Vector3D &RotXYZ_deg, const Vector3D &Trans_m,
                        const Vector3D &RGB)
{
  std::ostringstream stream;

  stream << "AddObj Name=" << Name << " "
         << "Shift=" << Shift << " "
         << "Scale=" << Scale << " "
         << "RotXYZ_deg=" << RotXYZ_deg << " "
         << "Trans_m=" << Trans_m << " "
         << "RGB=" << RGB << "\n";
         
  std::string msg = stream.str();
  return Send(_socket, msg.c_str());
}

bool ComChannel::UpdateObj(const std::string &Name, const Vector3D &RotXYZ_deg, const Vector3D &Trans_m)
{
  std::ostringstream stream;

  stream << "UpdateObj Name=" << Name << " "
         << "RotXYZ_deg=" << RotXYZ_deg << " "
         << "Trans_m=" << Trans_m << "\n";

  std::string msg = stream.str();
  return Send(_socket, msg.c_str());
}

bool ComChannel::Clear()
{
  const char *msg = "Clear \n";
  return Send(_socket, msg);
}

bool ComChannel::Close()
{
  const char *msg = "Close \n";
  return Send(_socket, msg);
}

ComChannel::~ComChannel()
{
  UnlockAccess();
}