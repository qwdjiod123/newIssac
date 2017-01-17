#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	if (_loading->loadingDone())
	{		
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{			
			//�ε��� �Ϸ� ������ ������
			SCENEMANAGER->changeScene("��Ʈ��ȭ��");
		}		
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ ����� ����
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

	//�������̹���
	_loading->loadFrameImage("����1", "w_coin.bmp", 245, 30, 7, 1, true, RGB(255, 0, 255));;
	_loading->loadImage("��ź", "w_bomb.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ź2", "w_bomb2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ź3", "w_bomb3.bmp", 4600, 200, 23, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "w_key.bmp", 280, 40, 7, 1, true, RGB(255, 0, 255));	
	_loading->loadImage("����99", "w_coin99.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("�������", "w_meat.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("���������Ǳ���", "w_fly.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("�ڻ���������", "w_remocon.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("�ڻ���������2", "w_missileBomb.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("�ڻ���������3", "w_rocket.bmp", 100, 200, true, RGB(255, 0, 255));
	_loading->loadImage("�𷡽ð�", "w_sandclock.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("ī��", "w_card.bmp", 30, 35, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ", "w_devil.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("��������", "w_box.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("��������2", "w_box2.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ2", "w_heart2.bmp", 35, 30, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ", "w_heart.bmp", 35, 30, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "w_slot.bmp", 900, 100, 9, 1, true, RGB(255, 0, 255));
	_loading->loadImage("������", "w_rock.bmp", 50, 40, true, RGB(255, 0, 255));
	_loading->loadImage("����ĳ����", "w_shop.bmp", 50, 100, true, RGB(255, 0, 255));
	_loading->loadImage("����2", "w_shop2.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("����3", "w_shop3.bmp", 40, 40, true, RGB(255, 0, 255));
	

	//��׶��� �̹���
	//_loading->loadImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("�Ѿ�", "ball.bmp", 10, 10);
	_loading->loadImage("map1", "inGameInfo.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map2", "map2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map3", "map3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("��ź", "bomb.bmp", 50, 50);
	_loading->loadImage("����", "key.bmp", 50, 50);
	//�÷��̾� �̹��� 
	_loading->loadImage("�����ۿ��ʾ�", "������LEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����ۿ����ʾ�", "�����ۿ�.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("������IDLE", "������IDLE.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۵����", "�����۵����.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۸���", "����.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ��ʸ���", "WALKLEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ����ʸ���", "������RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������UPDOWN", "������UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("������ITEM", "������ItemPickUp.bmp", PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������STATUP", "������STATUP.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������HURT", "������HURT.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	//��Ȳ�÷��̾�
	_loading->loadImage("��Ȳ���ʾ�", "��ȲLEFTFIRE.bmp", PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ�����ʾ�", "��ȲRIGHTFIRE.bmp", PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��ȲIDLEFIRE", "��ȲIDLEFIRE.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));

	_loading->loadImage("��ȲIDLE", "��ȲIDLE.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ�����", "��Ȳ�����.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ����", "��Ȳ����.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��Ȳ���ʸ���", "��������ȲLEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��Ȳ�����ʸ���", "��������ȲRIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ȲUPDOWN", "��������ȲUPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("��ȲITEM", "��ȲItemPickUp.bmp", PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ȲSTATUP", "��ȲStatUp.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ȲHURT", "��ȲHURT.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	//�Ѿ��̹��� 
	_loading->loadImage("�⺻�Ѿ�", "�⺻�Ѿ�.bmp", 26, 26, true, RGB(255, 0, 255));
	_loading->loadImage("ū�Ѿ�", "ū�Ѿ�.bmp", 35, 35, true, RGB(255, 0, 255));
	//�Ѿ�ȿ��
	_loading->loadFrameImage("ū�Ѿ�ȿ��", "�Ѿ�ȿ��.bmp", 2080, 130, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����Ѿ�ȿ��", "�����Ѿ�ȿ��.bmp", 728, 52, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����¿�", "�����տ�.bmp", 56 * 7, 80, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�������", "������.bmp", 80, 56 * 7, 4, 1, true, RGB(255, 0, 255));
	//����
	_loading->loadFrameImage("�����۳���", "�����۳���������.bmp", 515, 41, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��Ȳ����", "��Ȳ����������.bmp", 515, 41, 5, 1, true, RGB(255, 0, 255));
	//������ ��� �߰� 
	_loading->loadFrameImage("������DEAD", "������DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("������DEAD2", "������DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ȲDEAD", "��ȲDEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("��ȲDEAD2", "��ȲDEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	//���Ϳ� ���� �̹���
	_loading->loadFrameImage("wormH", "wormH.bmp", 504, 40, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormD", "wormD.bmp", 600, 28, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDA", "wormDA.bmp", 27, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormHA", "wormHA.bmp", 39, 62, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormU", "wormU.bmp", 27, 31, 1, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("wormHR", "wormHR.bmp", 504, 40, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDR", "wormDR.bmp", 600, 28, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDAR", "wormDAR.bmp", 27, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormHAR", "wormHAR.bmp", 39, 62, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormUR", "wormUR.bmp", 27, 31, 1, 1, true, RGB(255, 0, 255));


	_loading->loadImage("shootEnemy", "shootEnemy.bmp", 41, 36, true, RGB(255, 0, 255));
	_loading->loadFrameImage("shootEnemyAnime", "shootEnemyAnime.bmp", 368, 45, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("shootEnemyR", "shootEnemyR.bmp", 41, 36, true, RGB(255, 0, 255));
	_loading->loadFrameImage("shootEnemyAnimeR", "shootEnemyAnimeR.bmp", 368, 45, 8, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("fly", "fly.bmp", 84, 21, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flyR", "flyR.bmp", 84, 21, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("enemyBullet", "enemyBullet.bmp", 45, 15, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bulletEffect", "bulletEffect.bmp", 444, 74, 6, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("monstroAll", "monstroAll.bmp", 228, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroJumpMotion", "monstroJumpMotion.bmp", 816, 122, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroShootAnime", "monstroShootAnime.bmp", 408, 97, 3, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("monstroAllR", "monstroAllR.bmp", 228, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroJumpMotionR", "monstroJumpMotionR.bmp", 816, 122, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroShootAnimeR", "monstroShootAnimeR.bmp", 408, 97, 3, 1, true, RGB(255, 0, 255));


	_loading->loadImage("emptyHP", "emptyHP.bmp", 309, 33, true, RGB(255, 0, 255));
	_loading->loadImage("HP", "HP.bmp", 276, 18, true, RGB(255, 0, 255));

	_loading->loadImage("shadowB", "shadowB.bmp", 15, 4, true, RGB(255, 0, 255));
	_loading->loadImage("shadowBOSS", "shadowBOSS.bmp", 150, 36, true, RGB(255, 0, 255));

	//2017/01/14/ ����� �߰�

	//��Ʈ�� �̹���
	_loading->loadImage("intro1Part1", "intro1Part1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro1Part2", "intro1Part2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro1Part3", "intro1Part3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro1Part4", "intro1Part4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro1Part5", "intro1Part5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro2Part1", "intro2Part1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro2Part2", "intro2Part2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro2Part3", "intro2Part3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro2Part4", "intro2Part4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro2Part5", "intro2Part5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro3Part1", "intro3Part1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro3Part2", "intro3Part2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro3Part3", "intro3Part3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro3Part4", "intro3Part4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro3Part5", "intro3Part5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part1", "intro4Part1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part2", "intro4Part2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part3", "intro4Part3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part4", "intro4Part4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part5", "intro4Part5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part6", "intro4Part6.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part7", "intro4Part7.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro4Part8", "intro4Part8.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro5Part1", "intro5Part1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("intro5Part2", "intro5Part2.bmp", WINSIZEX, WINSIZEY);

	_loading->loadImage("startAfter1", "startAfter1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter2", "startAfter2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter3", "startAfter3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter4", "startAfter4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter5", "startAfter5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter6", "startAfter6.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter7", "startAfter7.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter8", "startAfter8.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter9", "startAfter9.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter10", "startAfter10.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter11", "startAfter11.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter12", "startAfter12.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter13", "startAfter13.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter14", "startAfter14.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter15", "startAfter15.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter16", "startAfter16.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter17", "startAfter17.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("startAfter18", "startAfter18.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("characterChange", "characterChange.bmp", WINSIZEX, WINSIZEY);

	_loading->loadImage("UI", "UI.bmp", 800, 90);
	_loading->loadImage("inGameInfo", "inGameInfo.bmp", 800, 510);
	_loading->loadImage("inGameInfoPX", "inGameInfoPX.bmp", 800, 510);
	_loading->loadImage("inGameInfoMini", "inGameInfoMini.bmp", 300, 80);
	_loading->loadImage("firstMap", "firstMap.bmp", 800, 510);
	_loading->loadImage("secondMap", "secondMap.bmp", 800, 510);
	_loading->loadImage("thirdMap", "thirdMap.bmp", 800, 510);
	_loading->loadImage("fourthMap", "fourthMap.bmp", 800, 510);
	_loading->loadImage("fifthMap", "fifthMap.bmp", 800, 510);
	_loading->loadImage("sixthMap", "sixthMap.bmp", 800, 510);
	_loading->loadImage("seventhMap", "seventhMap.bmp", 800, 510);
	_loading->loadImage("eighthMap", "eighthMap.bmp", 800, 510);

	_loading->loadImage("firstMapPX", "firstMapPX.bmp", 800, 510);
	_loading->loadImage("secondMapPX", "secondMapPX.bmp", 800, 510);
	_loading->loadImage("thirdMapPX", "thirdMapPX.bmp", 800, 510);
	_loading->loadImage("fourthMapPX", "fourthMapPX.bmp", 800, 510);
	_loading->loadImage("fifthMapPX", "fifthMapPX.bmp", 800, 510);
	_loading->loadImage("sixthMapPX", "sixthMapPX.bmp", 800, 510);
	_loading->loadImage("seventhMapPX", "seventhMapPX.bmp", 800, 510);
	_loading->loadImage("eighthMapPX", "eighthMapPX.bmp", 800, 510);
	_loading->loadImage("firstMapMini", "firstMapMini.bmp", 300, 80);
	_loading->loadImage("sixthMapMini", "sixthMapMini.bmp", 300, 80);

	_loading->loadImage("blackMini", "blackMini.bmp", 33, 14);
	_loading->loadImage("whiteMini", "whiteMini.bmp", 33, 14);
	_loading->loadImage("grayMini", "grayMini.bmp", 33, 14);
	_loading->loadImage("scMini", "scMini.bmp", 17, 15, true, RGB(128, 128, 255));
	_loading->loadImage("kingMini", "kingMini.bmp", 22, 18, true, RGB(128, 128, 255));
	_loading->loadImage("itemMini", "itemMini.bmp", 19, 21, true, RGB(128, 128, 255));

	_loading->loadImage("emptyHeart", "emptyHeart.bmp", 32, 26);
	_loading->loadImage("fullHeart", "fullHeart.bmp", 31, 25);
	_loading->loadImage("halfHeart", "halfHeart.bmp", 33, 26);

	_loading->loadImage("mainGame", "mainGame.bmp", 800, 600);
	_loading->loadImage("mother", "mother.bmp", 1600, 320, true, RGB(128, 128, 255));
	_loading->loadImage("fly", "fly.bmp", 260, 130, true, RGB(128, 128, 255));
	_loading->loadImage("start", "start.bmp", 163, 64, true, RGB(128, 128, 255));
	_loading->loadImage("select", "select.bmp", 150, 150, true, RGB(128, 128, 255));

	_loading->loadImage("sandclock", "sandclock.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("remocon", "remocon.bmp", 40, 40, true, RGB(255, 0, 255));

	_loading->loadImage("doorTop", "doorTop.bmp", 170, 400, true, RGB(128, 128, 255));
	_loading->loadImage("doorBottom", "doorBottom.bmp", 170, 400, true, RGB(128, 128, 255));
	_loading->loadImage("doorLeft", "doorLeft.bmp", 400, 170, true, RGB(128, 128, 255));
	_loading->loadImage("doorRight", "doorRight.bmp", 400, 170, true, RGB(128, 128, 255));
}
//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
}
