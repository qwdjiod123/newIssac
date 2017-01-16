#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## init(void) ## �ʱ�ȭ
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	
	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 �����Ѵ�
	//�׸��� ������ ������ ���ΰ��ӿ����� �ϸ� �ȴ�
	/*���߰�*/

	//SCENEMANAGER->addScene("���׽�Ʈ", new sceneTest);
	//SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
	//SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("��Ʈ��ȭ��", new cIntro);
	SCENEMANAGER->addScene("����ȭ��", new cSceneGame);
	

	/*����� ����*/
	SCENEMANAGER->changeScene("�ε�ȭ��");

	return S_OK;
}
//=============================================================
//	## release(void) ## ����
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}
//=============================================================
//	## update(void) ## ������Ʈ
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}
//=============================================================
//	## render(void) ## ����
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (������ �׳� �״�� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	
	//���Ŵ��� ����
	SCENEMANAGER->render();

//=============================================================
	//������� ������ HDC�� �׸��� (������ �״�� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}