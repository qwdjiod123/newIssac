#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{		
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{			
			//로딩이 완료 됐으니 씬변경
			SCENEMANAGER->changeScene("인트로화면");
		}		
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

	//전우형이미지
	_loading->loadFrameImage("동전1", "w_coin.bmp", 245, 30, 7, 1, true, RGB(255, 0, 255));;
	_loading->loadImage("폭탄", "w_bomb.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폭탄2", "w_bomb2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폭탄3", "w_bomb3.bmp", 4600, 200, 23, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("열쇠", "w_key.bmp", 280, 40, 7, 1, true, RGB(255, 0, 255));	
	_loading->loadImage("동전99", "w_coin99.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("썩은고기", "w_meat.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("구렁텅이의군주", "w_fly.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("박사의조정기", "w_remocon.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("박사의조정기2", "w_missileBomb.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("박사의조정기3", "w_rocket.bmp", 100, 200, true, RGB(255, 0, 255));
	_loading->loadImage("모래시계", "w_sandclock.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("카드", "w_card.bmp", 30, 35, true, RGB(255, 0, 255));
	_loading->loadImage("유황", "w_devil.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("보물상자", "w_box.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("보물상자2", "w_box2.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("하트2", "w_heart2.bmp", 35, 30, true, RGB(255, 0, 255));
	_loading->loadImage("하트", "w_heart.bmp", 35, 30, true, RGB(255, 0, 255));
	_loading->loadFrameImage("슬롯", "w_slot.bmp", 900, 100, 9, 1, true, RGB(255, 0, 255));
	_loading->loadImage("돌맹이", "w_rock.bmp", 50, 40, true, RGB(255, 0, 255));
	_loading->loadImage("상점캐릭터", "w_shop.bmp", 50, 100, true, RGB(255, 0, 255));
	_loading->loadImage("상점2", "w_shop2.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->loadImage("상점3", "w_shop3.bmp", 40, 40, true, RGB(255, 0, 255));
	

	//백그라운드 이미지
	//_loading->loadImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("총알", "ball.bmp", 10, 10);
	_loading->loadImage("map1", "inGameInfo.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map2", "map2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map3", "map3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("폭탄", "bomb.bmp", 50, 50);
	_loading->loadImage("열쇠", "key.bmp", 50, 50);
	//플레이어 이미지 
	_loading->loadImage("아이작왼쪽얼굴", "아이작LEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작오른쪽얼굴", "아이작옆.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작IDLE", "아이작IDLE.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작뒷통수", "아이작뒷통수.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작몸통", "몸통.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작왼쪽몸통", "WALKLEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작오른쪽몸통", "아이작RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작UPDOWN", "아이작UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("아이작ITEM", "아이작ItemPickUp.bmp", PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작STATUP", "아이작STATUP.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작HURT", "아이작HURT.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	//유황플레이어
	_loading->loadImage("유황왼쪽얼굴", "유황LEFTFIRE.bmp", PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황오른쪽얼굴", "유황RIGHTFIRE.bmp", PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황IDLEFIRE", "유황IDLEFIRE.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));

	_loading->loadImage("유황IDLE", "유황IDLE.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황뒷통수", "유황뒷통수.bmp", PLAYERHEADSIZEX + 20, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황몸통", "유황몸통.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황왼쪽몸통", "아이작유황LEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황오른쪽몸통", "아이작유황RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황UPDOWN", "아이작유황UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("유황ITEM", "유황ItemPickUp.bmp", PLAYERHEADSIZEX, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황STATUP", "유황StatUp.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황HURT", "유황HURT.bmp", PLAYERHEADSIZEX * 2, PLAYERSIZEY + PLAYERHEADSIZEY, 2, 1, true, RGB(255, 0, 255));
	//총알이미지 
	_loading->loadImage("기본총알", "기본총알.bmp", 26, 26, true, RGB(255, 0, 255));
	_loading->loadImage("큰총알", "큰총알.bmp", 35, 35, true, RGB(255, 0, 255));
	//총알효과
	_loading->loadFrameImage("큰총알효과", "총알효과.bmp", 2080, 130, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("작은총알효과", "작은총알효과.bmp", 728, 52, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("혈사좌우", "혈사기둥옆.bmp", 56 * 7, 80, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("혈사상하", "혈사기둥.bmp", 80, 56 * 7, 4, 1, true, RGB(255, 0, 255));
	//날개
	_loading->loadFrameImage("아이작날개", "아이작날개프레임.bmp", 515, 41, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황날개", "유황날개프레임.bmp", 515, 41, 5, 1, true, RGB(255, 0, 255));
	//죽을때 모션 추가 
	_loading->loadFrameImage("아이작DEAD", "아이작DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("아이작DEAD2", "아이작DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황DEAD", "유황DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("유황DEAD2", "유황DEAD.bmp", PLAYERHEADSIZEX * 3, PLAYERSIZEY + PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	//몬스터에 대한 이미지
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

	//2017/01/14/ 언식이 추가

	//인트로 이미지
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
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
}
