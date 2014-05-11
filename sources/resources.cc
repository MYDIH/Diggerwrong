#include "resources.hh"

Resource::~Resource()
{}

void ResourcesPool::add(Resource* r)
{
   Pool.push_back(r);
}

void ResourcesPool::load(const std::string & basepath)
{
   for (Resource* r : Pool)
      r -> load(basepath);
}
