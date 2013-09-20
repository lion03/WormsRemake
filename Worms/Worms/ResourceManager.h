/**
\file	ResourceManager.h

\brief	Declares the resource manager class.
*/

#pragma once
#include <memory>
#include <map>
template<class ResourceType>

/**
\brief	Manager for resources.
*/

class ResourceManager
{
public:

	typedef std::shared_ptr<ResourceType> ResourcePtr;

	typedef std::map<std::string,std::shared_ptr<ResourceType > > ResourceMap;

	/**
	 \brief	Finalizes an instance of the ResourceManager class.
	 */

	virtual ~ResourceManager(void){
		m_Resources.clear();
	};

	/**
	 \brief	Gets the instence.
	
	 \return	null if it fails, else the instence.
	 */

	static ResourceManager* getInstence(void){
		static ResourceManager<ResourceType> m_ResourceManager;
		return &m_ResourceManager;
	}

	void registerResource(ResourceType resource,const std::string& name){

		this->m_Resources.insert(std::make_pair(name, std::make_shared<ResourceType>(resource)));
	};

	/**
	 \brief	Registers the resource.
	
	 \param	path	Full pathname of the file.
	 \param	name	The name.
	 */

	void registerResource(const std::string &path,const std::string& name){
		ResourceType* resource =new ResourceType();

		resource->loadFromFile(path);

		this->m_Resources.insert(std::make_pair(name, ResourcePtr(resource)));
	};

	/**
	 \brief	Gets a resource.
	
	 \param	name	The name.
	
	 \return	The resource.
	 */

	ResourcePtr getResource(const std::string &name){

		auto temp = this->m_Resources[name];

		if(temp)
			return temp;

		return nullptr;

	}

	ResourceMap* getResourceMap(void) {return &m_Resources;}


private:

	/**
	 \brief	Initializes a new instance of the ResourceManager class.
	 */

	ResourceManager(void){};


	static ResourceMap m_Resources;

};

template<class T>

std::map<std::string,std::shared_ptr<T> > ResourceManager<T>::m_Resources;

/**
// End of ResourceManager.h
 */

