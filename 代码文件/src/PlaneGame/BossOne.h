#pragma once
#include "GameObject.h"
#include "resource.h"
#include "Health.h"
#include "Level.h"

class CBossOne :
    public CGameObject
{
public:

	
	CBossOne(int HP,int FireWait);
	~CBossOne(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;

	void takeDamage(int dmgType);

	int getHealth();
	BOOL enIsAlive();
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
public:
	static int nBossOneMaxNum;
	static int nBossOneCurNum;
private:
	static const int BOSSONE_HEIGHT = 100;
	static const int BOSSONE_WIDTH = 144;
	static CImageList m_Images;
	int    m_nXMotion;//���� 1->���� 0->ֹͣ -1->����
	int    m_nYMotion;
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	//����
	int    m_nWait;
	int m_waitCtl;
	//Ѫ��
	CHealth m_chealth;

	//�л��ȼ�
	CLevel m_enlevel;
};

