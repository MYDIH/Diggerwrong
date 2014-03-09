#pragma once

#include "GameObserver.hh"

#include <vector>

namespace diggewrong
{
   class GameObservable
   {
   private:
     std::vector<GameObserver> m_observers;

   public:
      
   };
}
