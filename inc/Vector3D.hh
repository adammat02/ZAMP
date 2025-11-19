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
  /*!
   * \brief Konstruktor z trzema współrzędnymi
   *
   * Konstruktor tworzy wektor 3-wymiarowy o podanych współrzędnych.
   * \param X - współrzędna X wektora,
   * \param Y - współrzędna Y wektora,
   * \param Z - współrzędna Z wektora.
   */
  Vector3D(double X = 0.0, double Y = 0.0, double Z = 0.0)
  {
    (*this)[0] = X;
    (*this)[1] = Y;
    (*this)[2] = Z;
  }

  /*!
   * \brief Wczytuje współrzędne wektora z tekstowego strumienia wejściowego.
   *
   * Wczytuje współrzędne wektora z tekstowego strumienia wejściowego.
   * \param IStrm - strumień wejściowy, z którego wczytywane są współrzędne wektora.
   * \return  referencja do strumienia wejściowego.
   */
  friend std::istream &operator>>(std::istream &IStrm, Vector3D &Vec)
  {
    IStrm >> Vec[0] >> Vec[1] >> Vec[2];
    return IStrm;
  }
};

#endif
