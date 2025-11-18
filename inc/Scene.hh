#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include "AbstractMobileObj.hh"
#include <string>
#include <map>
#include <memory>

class Scene : public AbstractScene
{
  typedef std::map<std::string, std::shared_ptr<AbstractMobileObj>> ObjMap;

  ObjMap _Set_MobileObjs;

public:
  ~Scene();
  /*!
   * \brief Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
   *
   *  Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
   *  \param[in] sName - pełna kwalifikowana nazwa obiektu.
   *  \return Jeśli obiekt zostanie znaleziony, to zwracany jest wskaźnik
   *          na niego. W przypadku przeciwnym zwracany jest wskaźnik \p nullptr.
   */
  AbstractMobileObj *FindMobileObj(const char *sName) const;
  /*!
   * \brief Dodaje do sceny nowy obiekt.
   *
   *  Dodaje do sceny nowy obiekt. Obiekt ten musi mieć poprawnie
   *  skonstruowaną pełną kwalifikowaną nazwę.
   *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
   */
  void AddMobileObj(AbstractMobileObj *pMobObj);
};

#endif