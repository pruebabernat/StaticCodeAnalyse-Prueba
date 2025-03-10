#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "p2Point.h"
#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include"j1Input.h"
#include "EntityManager.h"

// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		std::string name;
		int value;
	};

	~Properties()
	{
		for (std::list<Property*>::iterator it = list.begin(); it != list.end(); it++)
		{
			if (it._Ptr->_Myval != nullptr) 
			{
				RELEASE(it._Ptr->_Myval);
			}
		}

		list.clear();
	}

	int Get(const char* name, int default_value = 0);

	std::list<Property*>	list;
};

// ----------------------------------------------------
struct MapLayer
{
	
	std::string	name;
	int			width;
	int			height;
	uint*		data;
	Properties	properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	std::string			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	std::list<TileSet*>	tilesets;

	std::list<MapLayer*>	downLayers;
	std::list<MapLayer*>	topLayers;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	fPoint MapToWorld(float x, float y) const;
	iPoint WorldToMap(int x, int y) const;

	iPoint GetMousePositionOnMap();
	iPoint TileCenterPoint(iPoint);

	iPoint GetTilesHalfSize();
	fPoint GetTilesHalfSizeFloat();

	SDL_Rect GetMapRect();

	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer);

	TileSet* GetTilesetFromTileId(int id);

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	void DrawMapLayer(int layerIndex);

public:

	int GetMapMaxLenght();
	MapData data;

private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__