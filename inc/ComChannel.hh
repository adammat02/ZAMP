#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"

class ComChannel : public AbstractComChannel
{

  int _socket;
  
  std::mutex _mutex;

public:
  ~ComChannel() {}

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
};

#endif