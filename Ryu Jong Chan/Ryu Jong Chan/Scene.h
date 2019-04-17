#pragma once

class Scene
{
private:

public:
	Scene();
	virtual ~Scene();

	virtual void init();    
	virtual void update();  
	virtual void checkCol();
	virtual void draw();    
	virtual void clear();   
	virtual void exit();   
};