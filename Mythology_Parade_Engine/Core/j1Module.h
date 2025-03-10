// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include "PugiXml\src\pugixml.hpp"

class j1App;
class UI;

class j1Module
{
public:

	j1Module() : active(false)
	{
		int hola = 0;
	}

	virtual ~j1Module()
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

	virtual void OnClick(UI* element, float argument = -1)
	{

	}

	void Disable(){
		if (active == true) {
			active = false;
			CleanUp();
		}
	}

	void Enable() {
		if (active == false) {
			active = true;
			Start();
		}
	}

public:

	std::string	name;
	bool		active;
	bool		destroy = false;

};

#endif // __j1MODULE_H__