#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "j1Module.h"
#include "j1Minimap.h"
#include"j1Render.h"

struct SDL_Window;
struct SDL_Surface;

class j1Window : public j1Module
{
public:

	j1Window();

	// Destructor
	virtual ~j1Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* new_title);

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

	// Retrieve window scale
	uint GetScale() const;

	bool ToggleFullscreen();

	bool isFullscreen();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

private:
	std::string	title;
	uint		width;
	uint		height;
	uint		scale;
};

#endif // __j1WINDOW_H__