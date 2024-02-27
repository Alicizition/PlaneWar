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

	//图片
	static BOOL LoadImage();
	BOOL Draw(CDC* pDC, int bPause);
	CRect GetRect();
	
	//运动
	void SetHorMotion(int nMotion);
	int GetHorMotion() const;
	void SetVerMotion(int nMotion);
	int GetVerMotion() const;
	int GetKey(int nVirtKey);
	void Move();
	void Move(CPoint pos, int MoveType);
	BOOL setControlMode(int Mode);


	int getControlMode();
	
	//开火
	BOOL Fired();
	BOOL FiredMissle();

	//血条
	int takeDamage(int dmgType);
	BOOL PisAlive();
	int Heal(int healTyle);

	int getPlaneLevel();
	void ScoreUp();

	BOOL upgrade();
	void AddScore();
	 
public:

	//飞机图信息
	static const int PLANE_WIDTH=69;
	static const int PLANE_HEIGHT=44;
	static CImageList m_Images;
private:
	/*
	//血条
	
	int    m_health;//血量
	int    m_index;
	static CImageList m_HealthBarImg;
	*/

	//血条类
	CHealth m_cHealth;


	//运动
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下

	//开火
	int    m_nWait;//发射延时
	int    m_threshod;

	int m_myMissleNum;//Missle 数量
	int m_MissleWait;//发射延时

	//等级
	int m_score;
	CLevel m_plevel;
	BOOL m_canlevelUp;
	BOOL m_zzl_flag;

private:
	int control_flag;




};
