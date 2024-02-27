#pragma once
#include "GameObject.h"
#include "Level.h"
#include "Health.h"
#include "Blood.h"

class CMyPlane :public CGameObject
{
public:
	CMyPlane(void);
	~CMyPlane(void);

	//ͼƬ
	static BOOL LoadImage();
	BOOL Draw(CDC* pDC, int bPause);
	CRect GetRect();
	
	//�˶�
	void SetHorMotion(int nMotion);
	int GetHorMotion() const;
	void SetVerMotion(int nMotion);
	int GetVerMotion() const;
	int GetKey(int nVirtKey);
	void Move();
	void Move(CPoint pos, int MoveType);
	BOOL setControlMode(int Mode);


	int getControlMode();
	
	//����
	BOOL Fired();
	BOOL FiredMissle();

	//Ѫ��
	int takeDamage(int dmgType);
	BOOL PisAlive();
	int Heal(int healTyle);

	int getPlaneLevel();
	void ScoreUp();

	BOOL upgrade();
	void AddScore();
	 
public:

	//�ɻ�ͼ��Ϣ
	static const int PLANE_WIDTH=69;
	static const int PLANE_HEIGHT=44;
	static CImageList m_Images;
private:
	/*
	//Ѫ��
	
	int    m_health;//Ѫ��
	int    m_index;
	static CImageList m_HealthBarImg;
	*/

	//Ѫ����
	CHealth m_cHealth;


	//�˶�
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��

	//����
	int    m_nWait;//������ʱ
	int    m_threshod;

	int m_myMissleNum;//Missle ����
	int m_MissleWait;//������ʱ

	//�ȼ�
	int m_score;
	CLevel m_plevel;
	BOOL m_canlevelUp;
	BOOL m_zzl_flag;

private:
	int control_flag;




};
