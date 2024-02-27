#pragma once
#include "GameObject.h"
#include "resource.h"
#include "Health.h"
#include "Level.h"
class CBossTwo :
    public CGameObject
{

public:
	CBossTwo(int HP, int FireWait);
	~CBossTwo(void);

	BOOL Draw(CDC* pDC, int bPause);

	static BOOL LoadImage();

	CRect GetRect();

	int GetMontion() const;

	void takeDamage(int dmgType);

	int getHealth();
	BOOL enIsAlive();
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int BOSSTWO_HEIGHT = 100;
	static const int BOSSTWO_WIDTH = 144;
	static CImageList m_Images;
	int    m_nXMotion;//���� 1->���� 0->ֹͣ -1->����
	int    m_nYMotion;
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;

	int    m_nWait;
	int m_waitCtl;
	//Ѫ��
	CHealth m_chealth;

	//�л��ȼ�
public:
	static int nBossTwoMaxNum;
	static int nBossTwoCurNum;
private:
	CLevel m_enlevel;

private:
	int damageCtl;
};

