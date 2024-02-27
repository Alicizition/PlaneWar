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
	
	//�ؿ�
 	int m_gameLevel;
	int m_trueLevel;

	//��ͨ���˹���
	int m_gEnemyNumControl;//ÿ����֡�����л�
	int m_gEnemyWaitControl;//�����ӳ�
	int m_gEnemyHealthCtrol;//�л�����
	
	//Boss1����
	int m_gBoss1NumControl;
	int m_gBoss1WaitControl;
	int m_gBoss1HealthControl;

	//Boss2����
	int m_gBoss2NumControl;
	int m_gBoss2WaitControl;
	int m_gBoss2HealthControl;

	//�˺�����
	int m_dmgCtl;
	
	//Ѫ������
	int m_gBloodWait;
};

