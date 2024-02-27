#pragma once
class CGameLevel
{
public:
	CGameLevel();
	~CGameLevel();

	void allControl();
	
	void GameLevelUp();

	/////////////////////////////////////////////////Boss1
	int getBoss1NumCtl();
	int getBoss1HPCtl();
	int getBoss1FireWt();
	///////////////////////////////////////////////////Boss2
	int getBoss2NumCtl();
	int getBoss2HPCtl();
	int getBoss2FireWt();

	/////////////////////////////////////////////////////////////blood
	int getBloodNumCtl();
	////////////////////////////////////////////////////////////Enemy
	int getEnemyHPCtl();
	int getEnemyNumCtl();
	int getEnemyFireWt();

	////////////////////////////////////////////////////////////damage
	int getDamageCtl();
	int getGameLevel();
	void Draw(CDC* pDC);

private:
	
	//关卡
 	int m_gameLevel;
	int m_trueLevel;

	//普通敌人管理
	int m_gEnemyNumControl;//每多少帧产生敌机
	int m_gEnemyWaitControl;//开火延迟
	int m_gEnemyHealthCtrol;//敌机生命
	
	//Boss1管理
	int m_gBoss1NumControl;
	int m_gBoss1WaitControl;
	int m_gBoss1HealthControl;

	//Boss2管理
	int m_gBoss2NumControl;
	int m_gBoss2WaitControl;
	int m_gBoss2HealthControl;

	//伤害管理
	int m_dmgCtl;
	
	//血包管理
	int m_gBloodWait;
};

