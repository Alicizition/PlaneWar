// PlaneGameView.h : CPlaneGameView 类的接口
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

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;
	int my_operete_mode;


// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//获得键的状态1->down
	/*
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}*/
	
	CMyPlane*  m_pMe;
	//CHealth*   m_pMyHealth;
	CGameLevel gameLevel;
	CObList    m_ObjList[THINGS_NUM];



// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);



public:

	void drawBackGround(CDC* pMemDC);
	

	void drawMyPlane(CDC* pMemDC); //绘制战机 //398
	
	void drawOthers(CDC* pMemDC);////绘制 导弹、爆炸、敌机、子弹、物品、护盾物品 //416
	
	void creatThings();//生成敌机 //453

	void creatMyPlaneBullet();//生成战机子弹// 513

	void creatEnemyBullet();//生成敌机子弹 //543
	
	void generateBlood();  //生成血包
	
	void enemyBulletHitMyPlane();//敌机子弹击中战机 //570

	void crashMyplaneANDEnemy();//战机击中敌机// 625
	
	void myPlaneHitEnemyPlane();//子弹，导弹与敌方普通飞机碰撞
	
	void bosshurted();//boss 受伤
	void myPlaneMove();
	
	void getBlood(); //获得血包

	void myPlaneHitBossOneBall(); // 攻击敌方追踪弹

	int GetKey(int nVirtKey);
	private:
		int p;
		int pause;
private:
	cv::VideoCapture cap;
	OpenCVprocess opencvprocess;
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

