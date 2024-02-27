// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView
static int imagelocation = 0;
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
void CPlaneGameView::StopGame()
{
	
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	if(cap.isOpened())
		cap.release();
}

BOOL CPlaneGameView::InitGame()
{
	/*cv::Mat src = cv::imread("D:\\A桌面\\视频组\\山东科技大学.png");
	cv::imshow("ddd", src);*/
	
	
	CRect rc;
	GetClientRect(rc);
	
	//MessageBox(/*TEXT("一、键盘操作，上下左右键移动战机，按下空格键发射子弹，炸毁敌机得分，\n\n二、吃掉游戏中掉落物可以增加生命或者技能\n\n三、战机生命值初始为5，血量初始值为100\n\n四、游戏过程中，可是随时按下Esc键退出\n\n五、游戏支持同时按下Z与空格键，发射多个子弹（在掉落物中获得技能）\n\n六、游戏中按下X键，进入无敌模式，按下C键，退出无敌模式\n\n七、游戏中按下V键，进行清屏，清屏不进行分数累积（清屏不含BOSS）\n\n八、本游戏增加了形战争模式（敌机形，BOSS不形）欢迎体验"),*/
	//	TEXT("飞机大战——游戏说明"), MB_OK);//开始时弹出对话框介绍游戏说明
	int t = MessageBox(TEXT(" 你想体验体感操控吗？\n	YES进入体感控制模式, NO进入键控模式"), TEXT("O(∩_∩)O~"), MB_YESNO);
	p = 0;
	//暂停
	pause = 1;
	//t == 6 yes
	// t == 7 no
	if(t == 6)
	{
		MessageBox(TEXT(" 请确保您已打开摄像头，并且手边有一个绿色物品"));
		cap.open(0);
		opencvprocess.ImgProcessInit();
	}
	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CHealth::LoadImage();
	CBlood::LoadImage();
	CMyMissle::LoadImage();
	CBossOne::LoadImage();
	CBossOne::LoadImage();
	CBossOneBall::LoadImage();
	CBossTwo::LoadImage();
	CBossTwoBall::LoadImage();

	//产生主角(战机)
	m_pMe = new CMyPlane;
	m_pMe->setControlMode(t);

	//m_pMyHealth = new CHealth;
	/*cv::VideoCapture cap(0);
	cv::Mat frame;
	cap >> frame;
	imshow("frame", frame);
	cv::waitKey(0);*/
	//启动游戏
	SetTimer(1,30,NULL);

	return TRUE;
}



void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	
	//绘制天空 (背景)区域和颜色
	drawBackGround(pMemDC);
	//绘制 我方ball、爆炸、敌机、子弹, 血包
	drawOthers(pMemDC);
	//绘制我方战机
	drawMyPlane(pMemDC);


	//绘制关卡
	gameLevel.Draw(pMemDC);
	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	if (m_pMe == NULL) return;
	int beforeLevel = m_pMe->getPlaneLevel();

	//我机移动
	myPlaneMove();
	//产生敌机,Boss1,Boss2，产生血包
	creatThings();
	//产生战机导弹
	creatMyPlaneBullet();
	//敌机发射子弹
	creatEnemyBullet();
	//敌机子弹炸掉战机
	enemyBulletHitMyPlane();
	//敌机碰撞我机
	crashMyplaneANDEnemy();
	//战机导弹炸掉敌机
	myPlaneHitEnemyPlane();
	myPlaneHitBossOneBall();
	//我方获得血包
	getBlood();
	//boss受伤
	bosshurted();
	//进入下一关
	if (m_pMe == NULL) return;
	if(m_petPlaneLevel() > beforeLevel)
		gameLevel.GameLevelUp();

		//gameLevel.GameLevelUp(m_pMe->getPlaneLevel());
	
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	/*
	UpdateFrame(m_pMemDC);
	AI();
	CView::OnTimer(nIDEvent);
	*/
	if (GetKey('P') == 1)//按下了p键
	{
		if (p <= 0 && pause == 1)
			pause = 0;
		else
			if (p <= 0 && pause == 0)
			{
				pause = 1;
			}
		p = 2;
	}
	if (p > -1)
		p--;

	//刷新游戏帧画面: 在内存DC上绘图
	if (pause == 1)
	{
		UpdateFrame(m_pMemDC);
		AI();
	}
	CView::OnTimer(nIDEvent);


}


void CPlaneGameView::drawBackGround(CDC* pMemDC)
{
	pMemDC->FillSolidRect(0, 0, GAME_WIDTH, GAME_HEIGHT, RGB(35, 27, 27));
	//绘制背景图片
	CDC memDC;
	memDC.CreateCompatibleDC(pMemDC);
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_BACKGROUND);
	CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);
	pMemDC->BitBlt(0, imagelocation, GAME_WIDTH, GAME_HEIGHT - imagelocation, &memDC, 0, 0, SRCCOPY);
	pMemDC->BitBlt(0, 0, GAME_WIDTH, imagelocation, &memDC, 0, 1200 - imagelocation, SRCCOPY);
	imagelocation += 4;
	if (imagelocation >= GAME_HEIGHT)
		imagelocation = 0;
	pMemDC->SetBkMode(TRANSPARENT);//透明白框
	pMemDC->SetTextAlign(TA_CENTER);//中心对齐
	pMemDC->SetTextColor(RGB(255, 0, 0));//设置颜色

}


void CPlaneGameView::drawMyPlane(CDC* pMemDC) //绘制战机 //398
{
	if (m_pMe != NULL)
	{
		m_pMe->Draw(m_pMemDC, FALSE);
	}
	else
	{   //Game Over
		CString str = _T("Game Over!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	}

}
void CPlaneGameView::drawOthers(CDC* pMemDC)////绘制 导弹、爆炸、敌机、子弹、物品、护盾物品 //416
{
	//依次遍历导弹，比如导弹

	for (int i = 0; i < THINGS_NUM; i++)
	{
		POSITION pos1, pos2;
		//遍历每一个导弹
		for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			//得到第一个导弹，迭代器指向第二个导弹
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE))//如果绘制失败
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
}
void CPlaneGameView::creatThings()//生成敌机 //453
{

	//随机产生敌机
	static int nCreator = rand() % 5 + 10;
	if (nCreator <= 0)
	{
		//nCreator = rand()%5+10;
		nCreator = gameLevel.getEnemyNumCtl();
		int nEnemyHealth = gameLevel.getEnemyHPCtl();
		int nEnemyFireWt = gameLevel.getEnemyFireWt();
		m_ObjList[enEnemy].AddTail(new CEnemy(nEnemyHealth,nEnemyFireWt));
		

	}
	nCreator--;

	//随机产生血包
	static int nBlood = rand() % 5 + 10;
	if (nBlood <= 0)
	{
		
		nBlood = gameLevel.getBloodNumCtl();
		m_ObjList[enBlood].AddTail(new CBlood);
		
	}
	nBlood--;
	//随机产生小Boss
	static int nBossOne_round = rand() % 5 + 10;
	BOOL bossOneNumOk = CBossOne::nBossOneCurNum <= CBossOne::nBossOneMaxNum;
	if (nBossOne_round <= 0 && bossOneNumOk)
	{
		nBossOne_round = gameLevel.getBoss1NumCtl();
		int nBossHealth = gameLevel.getBoss1HPCtl();
		int nBossFireWt = gameLevel.getBoss1FireWt();
		m_ObjList[enBossOne].AddTail(new CBossOne(nBossHealth,nBossFireWt));

	}
	nBossOne_round--;

	//随机产生Boss2
	static int nBossTwo_round = rand() % 5 + 10;
	BOOL boss2NumOk = CBossTwo::nBossTwoCurNum <= CBossTwo::nBossTwoMaxNum;
	if (nBossTwo_round <= 0 && gameLevel.getGameLevel() >= 1)
	{
		nBossTwo_round = gameLevel.getBoss2NumCtl();
		int nBossHealth = gameLevel.getBoss2HPCtl();
		int nBossFireWt = gameLevel.getBoss2FireWt();
		m_ObjList[enBossTwo].AddTail(new CBossTwo(nBossHealth, nBossFireWt));
	}
	nBossTwo_round--;



}
void CPlaneGameView::creatMyPlaneBullet()//生成战机子弹// 513
{
	//自动开火
	if (m_pMe != NULL && m_pMe->Fired())
	{
		CPoint pt = m_pMe->GetPoint();
		for (int i = 0; i < 3; i++)
		{
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30 * i, pt.y + 10,i));
		}
	}
	//手动发射
	//if (m_pMe->GetKey(VK_SPACE) == 1 || m_pMe->GetKey(VK_LBUTTON) == 1)//按下了空格键或鼠标左键
	//{
	//	if (m_pMe != NULL && m_pMe->Fired())
	//	{
	//		CPoint pt = m_pMe->GetPoint();
	//		//m_ObjList[enBomb].AddTail(new CBomb(pt.x, pt.y + 10));
	//		for (int i = 0; i < 3; i++)
	//		{
	//			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30 * i, pt.y + 10,i));
	//		}
	//		//m_ObjList[enBomb].AddTail(new CBomb(pt.x + 60, pt.y + 10));
	//	}
	//}
	//右键发射导弹
	if (m_pMe->GetKey(VK_RBUTTON) == 1)
	{
		if (m_pMe != NULL && m_pMe->FiredMissle())
		{
			CPoint pt = m_pMe->GetPoint();

			m_ObjList[enMyMissle].AddTail(new CMyMissle(pt.x + 30, pt.y - 20,CPoint(100,100)));
			
			/*
			m_ObjList[enBossTwoBall].AddTail(new CBossTwoBall(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 50, 0));
			m_ObjList[enBossTwoBall].AddTail(new CBossTwoBall(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 50, 1));
			m_ObjList[enBossTwoBall].AddTail(new CBossTwoBall(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 50, 2));*/
		}

	}
}
void CPlaneGameView::creatEnemyBullet()//生成敌机子弹 //543
{
	if (m_pMe == NULL) return;
	CPoint PlanePt = m_pMe->GetPoint();

	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();
		BOOL by = FALSE;
		//敌机在战机前面
		if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//满足条件 则敌机发射子弹
		if (by &&ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));
		}
	}
	//Boss1 产生子弹
	for (POSITION ePos = m_ObjList[enBossOne].GetHeadPosition(); ePos != NULL;)
	{
		CBossOne* pBoss = (CBossOne*)m_ObjList[enBossOne].GetNext(ePos);
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();
		BOOL by = FALSE;
		//敌机在战机前面
		if (pBoss->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pBoss->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//无条件发射
		//m_ObjList[enBall].AddTail(new CBall(ePt.x + 72, ePt.y + 100, pBoss->GetMontion()));
		m_ObjList[enBossOneBall].AddTail(new CBossOneBall(ePt.x + 72, ePt.y + 100, m_pMe->GetPoint()));
		//满足条件 则敌机发射子弹
		if (by && ePt.x +72 >= PlanePt.x && ePt.x + 72 < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
		}
	}
	//Boss2 产生子弹
	for (POSITION ePos = m_ObjList[enBossTwo].GetHeadPosition(); ePos != NULL;)
	{
		CBossTwo* pBoss = (CBossTwo*)m_ObjList[enBossTwo].GetNext(ePos);
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();
		BOOL by = FALSE;
		//敌机在战机前面
		if (pBoss->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pBoss->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//无条件发射
		//m_ObjList[enBall].AddTail(new CBall(ePt.x + 72, ePt.y + 100, pBoss->GetMontion()));
		m_ObjList[enBossOneBall].AddTail(new CBossOneBall(ePt.x + 72, ePt.y + 100, m_pMe->GetPoint()));
		for (int i = 0; i < 8; i++)
		{
			m_ObjList[enBossTwoBall].AddTail(new CBossTwoBall(pBoss->GetPoint().x, pBoss->GetPoint().y, i));
		}
		//满足条件 则敌机发射子弹
		if (by && ePt.x + 72 >= PlanePt.x && ePt.x + 72 < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
		}
	}

}
void CPlaneGameView::generateBlood()
{

}
void CPlaneGameView::enemyBulletHitMyPlane()//敌机子弹击中战机 //570
{
	//普通敌机子弹攻击我方
	if (m_pMe == NULL) return;
	else
	{
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))//如果重合
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//删除敌机子弹
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;
				//扣除血量
				m_pMe->takeDamage(0);
				//如果血量为0 删除战机 

				if (!m_pMe->PisAlive())
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}
	//Boss1子弹攻击我方
	if (m_pMe == NULL) return;
	else
	{
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBossOneBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBossOneBall* pBB1 = (CBossOneBall*)m_ObjList[enBossOneBall].GetNext(bPos1);
			//追踪
			pBB1->UpdatePosition(m_pMe->GetPoint());
			//
			CRect bRect = pBB1->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))//如果重合
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				
				//删除敌机子弹
				m_ObjList[enBossOneBall].RemoveAt(bPos2);
				delete pBB1;
				//扣除血量
				m_pMe->takeDamage(1);
				//如果血量为0 删除战机 

				if (!m_pMe->PisAlive())
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}
	//Boss2子弹攻击我方
	if (m_pMe == NULL) return;
	else
	{
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBossTwoBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBossTwoBall* pBB2 = (CBossTwoBall*)m_ObjList[enBossTwoBall].GetNext(bPos1);
			CRect bRect = pBB2->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))//如果重合
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				//删除敌机子弹
				m_ObjList[enBossTwoBall].RemoveAt(bPos2);
				delete pBB2;
				//扣除血量
				m_pMe->takeDamage(2);//被2打到
				//如果血量为0 删除战机 

				if (!m_pMe->PisAlive())
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}
	
}
void CPlaneGameView::crashMyplaneANDEnemy()//战机碰撞敌机// 625
{
	if (m_pMe == NULL) return;
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	if (m_pMe == NULL) return;
	CRect mRect2 = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos1);
		CRect bRect = pEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))//如果重合
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//删除敌机
			pEnemy->takeDamage(1);//-100hp
			if (!pEnemy->enIsAlive())
			{

				m_ObjList[enEnemy].RemoveAt(bPos2);
				delete pEnemy;

			}
			//扣除血量
			m_pMe->takeDamage(0);

			//如果血量为0 删除战机 

			if (!m_pMe->PisAlive())
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}
}
void CPlaneGameView::myPlaneHitEnemyPlane()
{
	if (m_pMe == NULL) return;

	POSITION mPos1 = NULL, mPos2 = NULL;
	for (int i = 0; i < THINGS_NUM; i++)
	{
		if (i == enBomb || i == enMyMissle)
		{
			for (mPos1 = m_ObjList[i].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(mPos1);
				CRect bRect = pObj->GetRect();
				POSITION ePos1 = NULL, ePos2 = NULL;
				//遍历敌机位置
				for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
					CRect mRect = pEnemy->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//如果相交
					{
						//添加爆炸效果
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//删除敌机撞到的东西,不删除Missle
						if(i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Enemy受伤
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pEnemy->takeDamage(hurt);
						else if (i == enMyMissle)
							pEnemy->takeDamage(-hurt);
						//删除敌机
						if (!pEnemy->enIsAlive())
						{
							//得分

							//升级我方战机等级
							m_pMe->AddScore();
							m_pMe->upgrade();
							m_ObjList[enEnemy].RemoveAt(ePos2);
							delete pEnemy;
						}
						break;
						

					}
				}
			}
		}

	}


}
void CPlaneGameView::myPlaneMove()
{
	if (m_pMe == NULL)return;
	CPoint myPlaneMovePoint;
	if (m_pMe->getControlMode() == 6)
	{
		cv::Mat frame;
		cap >> frame;
		myPlaneMovePoint = opencvprocess.getGamePoint(opencvprocess.finalPoint(frame));//核心视觉识别代码
		my_operete_mode = 1;
	}
	if (m_pMe->getControlMode() == 7)
		m_pMe->Move();
	else if (m_pMe->getControlMode() == 6)
		m_pMe->Move(myPlaneMovePoint, 1);
}

void CPlaneGameView::getBlood()
{

	if (m_pMe == NULL) return;
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBlood].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBlood* pBlood = (CBlood*)m_ObjList[enBlood].GetNext(bPos1);
		CRect bRect = pBlood->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))//如果重合
		{
			
			//删除血包
			m_ObjList[enBlood].RemoveAt(bPos2);
			delete pBlood;
			//增加血量
			m_pMe->Heal(0);
			//m_pMe->takeDamage(0);
			//如果血量为0 删除战机 

			if (!m_pMe->PisAlive())
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}
}

void CPlaneGameView::bosshurted()//boss 受伤
{
	//Boss1
	if (m_pMe == NULL) return;
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (int i = 0; i < THINGS_NUM; i++)
	{
		if (i == enBomb || i == enMyMissle)
		{
			for (mPos1 = m_ObjList[i].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(mPos1);
				CRect bRect = pObj->GetRect();
				POSITION ePos1 = NULL, ePos2 = NULL;
				//遍历敌机位置
				for (ePos1 = m_ObjList[enBossOne].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossOne* pBoss = (CBossOne*)m_ObjList[enBossOne].GetNext(ePos1);
					CRect mRect = pBoss->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//如果相交
					{
						//添加爆炸效果
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//删除敌机撞到的东西,不删除Missle
						if (i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Boss1受伤
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pBoss->takeDamage(hurt);
						else if (i == enMyMissle)
							pBoss->takeDamage(-hurt);
						//删除敌机
						if (!pBoss->enIsAlive())
						{
							//得分
							m_pMe->AddScore();
							m_pMe->upgrade();
							//升级我方战机等级
							m_pMe->AddScore();
							m_ObjList[enBossOne].RemoveAt(ePos2);
							delete pBoss;
						}
						break;


					}
				}
			}
		}

	}
	//Boss2
	if (m_pMe == NULL) return;
	mPos1 = NULL;
	mPos2 = NULL;
	for (int i = 0; i < THINGS_NUM; i++)
	{
		if (i == enBomb || i == enMyMissle)
		{
			for (mPos1 = m_ObjList[i].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(mPos1);
				CRect bRect = pObj->GetRect();
				POSITION ePos1 = NULL, ePos2 = NULL;
				//遍历敌机位置
				for (ePos1 = m_ObjList[enBossTwo].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossTwo* pBoss = (CBossTwo*)m_ObjList[enBossTwo].GetNext(ePos1);
					CRect mRect = pBoss->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//如果相交
					{
						//添加爆炸效果
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//删除敌机撞到的东西,不删除Missle
						if (i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Boss2受伤
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pBoss->takeDamage(hurt);
						else if (i == enMyMissle)
							pBoss->takeDamage(-hurt);
						//删除敌机
						if (!pBoss->enIsAlive())
						{
							//得分
							m_pMe->AddScore();
							m_pMe->upgrade();
							//升级我方战机等级
							m_pMe->AddScore();
							m_ObjList[enBossTwo].RemoveAt(ePos2);
							delete pBoss;
						}
						break;


					}
				}
			}
		}

	}

}
void CPlaneGameView::myPlaneHitBossOneBall()//攻击敌方追踪弹
{
	if (m_pMe == NULL) return;

	POSITION mPos1 = NULL, mPos2 = NULL;
	for (int i = 0; i < THINGS_NUM; i++)
	{
		if (i == enBomb || i == enMyMissle)
		{
			for (mPos1 = m_ObjList[i].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(mPos1);
				CRect bRect = pObj->GetRect();
				POSITION ePos1 = NULL, ePos2 = NULL;
				//遍历敌方追踪弹位置
				for (ePos1 = m_ObjList[enBossOneBall].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossOneBall* pBob = (CBossOneBall*)m_ObjList[enBossOneBall].GetNext(ePos1);
					CRect mRect = pBob->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//如果相交
					{
						//添加爆炸效果
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//删除Bomb或Missle
						m_ObjList[i].RemoveAt(mPos2);
						if (pObj != NULL)
							delete pObj;

						m_ObjList[enBossOneBall].RemoveAt(ePos2);
						delete pBob;
						break;

					}
				}
			}
		}

	}


}

int CPlaneGameView::GetKey(int nVirtKey)
{
	return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
}