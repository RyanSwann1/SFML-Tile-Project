#pragma once

#include <unordered_map>
#include <string>
#include <assert.h>

using ResourceName = std::string;
using ResourceCount = unsigned int;
using FileName = std::string;
using FilePath = std::string;

//hexadecimal numbers
//https://www.dropbox.com/s/qe0688gbpum5ue9/Screenshot%202016-10-05%2021.18.40.png?dl=0
//https://www.dropbox.com/s/t7zj5s4idk6h0tn/Screenshot%202016-10-05%2021.46.07.png?dl=0

template <class T>
class ResourceManager
{
public:
	ResourceManager() {}
	virtual ~ResourceManager() {}

	//Disallow copying of this class
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;


	//Change how the user gets the resource.
	//Shouldnt require two method calls

	const bool hasResource(const std::string& id) const
	{
		auto res = findResource(id);
		if (res)
		{
			return true;
		}
		return false;
	}

	const T* getResource(const std::string& id) 
	{
		//return the resource
		auto res = findResource(id);
		if (res)
		{
			++res->second;
			return res->first;
		}

		//Get the resource directly from the file path
		auto cIter = m_filePaths.find(id);
		if (cIter != m_filePaths.cend())
		{
			T* resource = loadFromFile(cIter->second);
			m_resources.emplace(id, std::make_pair(resource, 1));
			return resource;
		}

		//assert(res->first != nullptr); //Shouldn't reach this line, meaning resource/ID doesn't exist
		return nullptr;
	}

	//virtual void loadInResource(const std::string& name, const std::string& location) = 0;

	bool releaseResource(const std::string& id)
	{
		auto res = findResource(id);
		if (res)
		{
			--res->second;
			if (!res->second)
			{
				removeResource(id);
			}
			return true;
		}
		return false;
	}

	void registerFilePath(const std::string& name, const std::string& location)
	{
		if (m_filePaths.find(name) == m_filePaths.cend())
		{
			m_filePaths.emplace(std::make_pair(name, location));
		}
	}
protected:
	std::unordered_map<ResourceName, std::pair<T*, ResourceCount>> m_resources;
	std::unordered_map<FileName, FilePath> m_filePaths;

	virtual T* loadFromFile(const std::string& fileName) = 0;

	void purgeResources()
	{
		for (auto &i : m_resources)
		{
			delete i.second.first;
			i.second.first = nullptr;
		}
		m_resources.clear();
	}

private:
	std::pair<T*, ResourceCount>* findResource(const std::string& id)
	{
		auto iter = m_resources.find(id);
		return (iter != m_resources.cend() ? &iter->second : nullptr);
	}

	bool removeResource(const std::string& id)
	{
		auto iter = m_resources.find(id);
		if (iter != m_resources.cend())
		{
			delete iter->second.first;
			iter->second.first = nullptr;
			m_resources.erase(iter);
			return true;
		}
		return false;
	}
};