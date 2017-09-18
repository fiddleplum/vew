#include <map>

namespace vew
{
	template <typename T>
	class ResourceCache
	{
	public:
		// Creates a new resource and returns it.
		T * add(std::string const & name);

		// Loads a resource and returns it.
		T * load(std::string const & name, std::string const & location);

		// Removes a resource by name.
		void remove(std::string const & name);

		// Removes a resource.
		void remove(T * resource);

	private:
		struct ResourceInfo
		{
			T * resource;
			int count;
		};
		std::map<std::string, ResourceInfo> resources;
	};

	// Inline Implementations

	template <typename T>
	T * ResourceCache<T>::add(std::string const & name)
	{
		auto iter = resources.find(name);
		if (iter == resources.end())
		{
			T * resource = new T();
			resources[name] = {resource, 1};
			return resource;
		}
		else
		{
			T * resource = iter.second.resource;
			iter.second.count++;
			return resource;
		}
	}

	template <typename T>
	T * ResourceCache<T>::load(std::string const & name, std::string const & location)
	{
		auto iter = resources.find(name);
		if (iter == resources.end())
		{
			T * resource = new T(location);
			resources[name] = {resource, 1};
			return resource;
		}
		else
		{
			T * resource = iter.second.resource;
			iter.second.count++;
			return resource;
		}
	}

	template <typename T>
	void ResourceCache<T>::remove(std::string const & name)
	{
		auto iter = resources.find(name);
		if (iter != resources.end())
		{
			iter.second.count--;
			if (iter.second.count == 0)
			{
				delete iter.second.resource;
				resources.erase(iter);
			}
		}
	}

	template <typename T>
	void ResourceCache<T>::remove(T * resource)
	{
		for (auto pair : resources)
		{
			if (pair.second.resource == resource)
			{
				pair.second.count--;
				if (pair.second.count == 0)
				{
					delete pair.second.resource;
					resources.erase(pair);
				}
				break;
			}
		}
	}
}