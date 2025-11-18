#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"
#include "Vector3D.hh"
#include <string>
#include <mutex>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Port.hh"

class ComChannel : public AbstractComChannel
{

  int _socket;

  std::mutex _mutex;

  bool Send(int Sk2Server, const char *sMesg);

public:
  ~ComChannel();

  /*!
   * \brief Inicjalizuje destryptor gniazda.
   *
   * Inicjalizuje destryptora pliku skojarzonego z połączeniem sieciowym z serwerem.
   * \param[in] Socket - zawiera poprawny deskryptor.
   */
  void Init(int Socket)
  {
    _socket = Socket;
  }
  /*!
   * \brief Udostępnia deskryptor pliku skojarzonego z połączeniem sieciowym z serwerem.
   *
   *  Udostępnia deskryptor skojarzonego z połączeniem sieciowym z serwerem.
   * \return Deskryptor pliku.
   */
  int GetSocket() const
  {
    return _socket;
  }
  /*!
   * \brief Zamyka dostęp gniazda.
   */
  void LockAccess()
  {
    _mutex.lock();
  }
  /*!
   * \brief Otwiera dostęp do gniazda.
   */
  void UnlockAccess()
  {
    _mutex.unlock();
  }
  /*!
   * \brief Udostępnia mutex w trybie modyfikacji.
   *
   *  Udostępnia mutex w trybie modyfikacji.
   *  Jest to przydatne, gdy planowany jest inny typ zamknięcie,
   *  np. poprzez klasę std::lock_gaurd, która daje możliwość
   *  bezpieczniejszego zamknięcia.
   */
  std::mutex &UseGuard()
  {
    return _mutex;
  }

  bool AddObj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale,
              const Vector3D &RotXYZ_deg, const Vector3D &Trans_m,
              const Vector3D &RGB);

  bool UpdateObj(const std::string &Name, const Vector3D &RotXYZ_deg, const Vector3D &Trans_m);

  bool Clear();

  bool Close();
};

#endif