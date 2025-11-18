#ifndef CUBOID_HH
#define CUBOID_HH

#include "AbstractMobileObj.hh"
#include "Vector3D.hh"
#include <string>
#include <mutex>

/**
 * @brief Klasa reprezentująca prostopadłościan jako obiekt mobilny w przestrzeni 3D
 *
 * Klasa dziedziczy po AbstractMobileObj i implementuje obiekt z pozycją,
 * rotacją oraz mechanizmem blokowania dostępu (mutex).
 */
class Cuboid : public AbstractMobileObj
{
  std::string _name; ///< Nazwa obiektu
  std::mutex _mutex; ///< Mutex do synchronizacji dostępu do obiektu

  Vector3D _position; ///< Pozycja obiektu w przestrzeni 3D [m]
  Vector3D _rotation; ///< Rotacja obiektu: roll, pitch, yaw [stopnie]

public:
  /**
   * @brief Destruktor
   */
  ~Cuboid() {};
  /*!
   * \brief Udostępnia wartość kąta \e roll.
   *
   *  Udostępnia wartość kąta \e pitch reprezentuje rotację
   *  zgodnie z ruchem wskazówek zegara wokół osi \e OX.
   *  \return Wartość kąta \e roll wyrażona w stopniach.
   */
  double GetAng_Roll_deg() const
  {
    return _rotation[0];
  }
  /*!
   * \brief Udostępnia wartość kąta \e yaw.
   *
   *  Udostępnia wartość kąta \e pitch reprezentuje rotację
   *  zgodnie z ruchem wskazówek zegara wokół osi \e OY.
   *  \return Wartość kąta \e pitch wyrażona w stopniach.
   */
  double GetAng_Pitch_deg() const
  {
    return _rotation[1];
  }
  /*!
   * \brief Udostępnia wartość kąta \e yaw.
   *
   *  Udostępnia wartość kąta \e yaw reprezentuje rotację
   *  zgodnie z ruchem wskazówek zegara wokół osi \e OZ.
   *  \return Wartość kąta \e yaw wyrażona w stopniach.
   */
  double GetAng_Yaw_deg() const
  {
    return _rotation[2];
  }
  /*!
   * \brief Zmienia wartość kąta \e roll.
   *
   *  Zmienia wartość kąta \e roll.
   *  \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
   */
  void SetAng_Roll_deg(double Ang_Roll_deg)
  {
    _rotation[0] = Ang_Roll_deg;
  }
  /*!
   * \brief Zmienia wartość kąta \e pitch.
   *
   *  Zmienia wartość kąta \e pitch.
   *  \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
   */
  void SetAng_Pitch_deg(double Ang_Pitch_deg)
  {
    _rotation[1] = Ang_Pitch_deg;
  }
  /*!
   * \brief Zmienia wartość kąta \e yaw.
   *
   *  Zmienia wartość kąta \e yaw.
   *  \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
   */
  void SetAng_Yaw_deg(double Ang_Yaw_deg)
  {
    _rotation[2] = Ang_Yaw_deg;
  }

  /*!
   * \brief Udostępnia współrzędne aktualnej pozycji obiektu.
   *
   * Udostępnia współrzędne aktualnej pozycji obiektu
   * \return Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
   *         że współrzędne wyrażone są w metrach.
   */
  const Vector3D &GetPositoin_m() const
  {
    return _position;
  }
  /*!
   * \brief Zmienia współrzędne aktualnej pozycji obiektu.
   *
   * Zmienia współrzędne aktualnej pozycji obiektu.
   * \param[in] rPos - nowe współrzędne obiektu. Przyjmuje się,
   *         że współrzędne wyrażone są w metrach.
   */
  void SetPosition_m(const Vector3D &rPos)
  {
    _position = rPos;
  }

  /*!
   * \brief Zmienia nazwę obiektu.
   *
   *  Zmienia nazwę obiektu, która go identyfikuje.
   *  \param[in]  sName - nowa nazwa obiektu.
   */
  void SetName(const char *sName)
  {
    _name = sName;
  }
  /*!
   * \brief Udostępnia nazwę obiektu.
   *  Udostępnia nazwę identyfikującą obiekt.
   *  \return Nazwa obiektu.
   */
  const std::string &GetName() const
  {
    return _name;
  }

  /**
   * @brief Blokuje dostęp do obiektu (lock mutex)
   *
   * Używane do synchronizacji wielowątkowej
   */
  void LockAccess()
  {
    _mutex.lock();
  }

  /**
   * @brief Odblokowuje dostęp do obiektu (unlock mutex)
   *
   * Używane do synchronizacji wielowątkowej
   */
  void UnLockAccess()
  {
    _mutex.unlock();
  }
};

#endif // CUBOID_HH