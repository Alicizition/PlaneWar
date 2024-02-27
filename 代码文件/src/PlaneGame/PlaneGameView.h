// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once
#include "Health.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
#include "OpenCVprocess.h"
#include"Blood.h"
#include "PlaneGame.h"
#include "PlaneGameDoc.h"
#include "MyMissle.h"
#include "BossOne.h"
#include "BossOneBall.h"
#include "BossTwo.h"
#include "BossTwoBall.h"
#include "GameLevel.h"
#include "resource.h"

#define THINGS_NUM 10
class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType { enEnemy, enBomb, enBall, enExplosion, enBlood, enMyMissle, enBossOne, enBossOneBall,enBossTwo,enBossTwoBall };

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;
	int my_operete_mode;


// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//��ü���״̬1->down
	/*
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}*/
	
	CMyPlane*  m_pMe;
	//CHealth*   m_pMyHealth;
	CGameLevel gameLevel;
	CObList    m_ObjList[THINGS_NUM];



// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);



public:

	void drawBackGround(CDC* pMemDC);
	

	void drawMyPlane(CDC* pMemDC); //����ս�� //398
	
	void drawOthers(CDC* pMemDC);////���� ��������ը���л����ӵ�����Ʒ��������Ʒ //416
	
	void creatThings();//���ɵл� //453

	void creatMyPlaneBullet();//����ս���ӵ�// 513

	void creatEnemyBullet();//���ɵл��ӵ� //543
	
	void generateBlood();  //����Ѫ��
	
	void enemyBulletHitMyPlane();//�л��ӵ�����ս�� //570

	void crashMyplaneANDEnemy();//ս�����ел�// 625
	
	void myPlaneHitEnemyPlane();//�ӵ���������з���ͨ�ɻ���ײ
	
	void bosshurted();//boss ����
	void myPlaneMove();
	
	void getBlood(); //���Ѫ��

	void myPlaneHitBossOneBall(); // �����з�׷�ٵ�

	int GetKey(int nVirtKey);
	private:
		int p;
		int pause;
private:
	cv::VideoCapture cap;
	OpenCVprocess opencvprocess;
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

