#pragma once
#include "gameNode.h"



class cSceneManager;



class cSound :	public gameNode
{

private:
	cSceneManager* _sm;
	

public:


	
	void SetSM(cSceneManager* ssm) { _sm = ssm; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cSound() {}
	~cSound() {}
};

