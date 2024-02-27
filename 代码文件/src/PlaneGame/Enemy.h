#pragma once
#include "gameobject.h"
#include "Level.h"
#include "resource.h"
#include "Health.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(void);
	CEnemy(int HP);
	CEnemy(int HP,int FireWait);
	~CEnemy(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;
	void takeDamage(int dmgType);

	int getHealth();

	void setHealth(int amount);
	BOOL enIsAlive();
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int    m_nXMotion;//���� 1->���� 0->ֹͣ -1->����
	int    m_nYMotion;
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	//������ʱ
	int    m_nWait;
	int	   m_waitCtl;
	//Ѫ��
	CHealth m_chealth;

//�л��ȼ�

private:
	CLevel m_enlevel;

};
