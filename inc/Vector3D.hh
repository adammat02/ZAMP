#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"
#include <iostream>

/*!
 * \file
 * \brief Deklaracja klasy Vector3D
 */

/*!
 * \brief Klasa Vector3D dla przestrzeni 3D
 */
class Vector3D : public geom::Vector<double, 3>
{
public:
  Vector3D()
  {
    (*this)[0] = 0.0;
    (*this)[1] = 0.0;
    (*this)[2] = 0.0;
  }

  Vector3D(double x, double y, double z)
  {
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
  }

  /*!
   * \brief Operator wejścia - wczytuje 3 wartości oddzielone spacjami
   */
  friend std::istream &operator>>(std::istream &is, Vector3D &vec)
  {
    is >> vec[0] >> vec[1] >> vec[2];
    return is;
  }

  /*!
   * \brief Operator wyjścia - wypisuje 3 wartości oddzielone spacjami
   */
  friend std::ostream &operator<<(std::ostream &os, const Vector3D &vec)
  {
    os << vec[0] << " " << vec[1] << " " << vec[2];
    return os;
  }
};

#endif
