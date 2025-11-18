#include "Scene.hh"

AbstractMobileObj *Scene::FindMobileObj(const char *sName) const
{
  ObjMap::const_iterator it = _Set_MobileObjs.find(sName);
  if (it != _Set_MobileObjs.end())
  {
    return it->second.get();
  }
  return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj)
{
  if (!pMobObj)
  {
    std::cerr << "!!! Wskaźnik do obiektu mobilnego jest nullptr." << std::endl;
    return;
  }

  std::string name = pMobObj->GetName();
  if (name.empty())
  {
    std::cerr << "!!! Niepoprawna nazwa obiektu mobilnego." << std::endl;
    return;
  }

  std::shared_ptr<AbstractMobileObj> pObj = std::shared_ptr<AbstractMobileObj>(pMobObj);

  _Set_MobileObjs[name] = pObj;
}