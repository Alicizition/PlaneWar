// PlaneGameView.cpp : CPlaneGameView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
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
	/*cv::Mat src = cv::imread("D:\\A����\\��Ƶ��\\ɽ���Ƽ���ѧ.png");
	cv::imshow("ddd", src);*/
	
	
	CRect rc;
	GetClientRect(rc);
	
	//MessageBox(/*TEXT("һ�����̲������������Ҽ��ƶ�ս�������¿ո�������ӵ���ը�ٵл��÷֣�\n\n�����Ե���Ϸ�е�������������������߼���\n\n����ս������ֵ��ʼΪ5��Ѫ����ʼֵΪ100\n\n�ġ���Ϸ�����У�������ʱ����Esc���˳�\n\n�塢��Ϸ֧��ͬʱ����Z��ո�����������ӵ����ڵ������л�ü��ܣ�\n\n������Ϸ�а���X���������޵�ģʽ������C�����˳��޵�ģʽ\n\n�ߡ���Ϸ�а���V�����������������������з����ۻ�����������BOSS��\n\n�ˡ�����Ϸ��������ս��ģʽ���л��Σ�BOSS���Σ���ӭ����"),*/
	//	TEXT("�ɻ���ս������Ϸ˵��"), MB_OK);//��ʼʱ�����Ի��������Ϸ˵��
	int t = MessageBox(TEXT(" ����������вٿ���\n	YES������п���ģʽ, NO�������ģʽ"), TEXT("O(��_��)O~"), MB_YESNO);
	p = 0;
	//��ͣ
	pause = 1;
	//t == 6 yes
	// t == 7 no
	if(t == 6)
	{
		MessageBox(TEXT(" ��ȷ�����Ѵ�����ͷ�������ֱ���һ����ɫ��Ʒ"));
		cap.open(0);
		opencvprocess.ImgProcessInit();
	}
	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
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

	//��������(ս��)
	m_pMe = new CMyPlane;
	m_pMe->setControlMode(t);

	//m_pMyHealth = new CHealth;
	/*cv::VideoCapture cap(0);
	cv::Mat frame;
	cap >> frame;
	imshow("frame", frame);
	cv::waitKey(0);*/
	//������Ϸ
	SetTimer(1,30,NULL);

	return TRUE;
}



void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	
	//������� (����)�������ɫ
	drawBackGround(pMemDC);
	//���� �ҷ�ball����ը���л����ӵ�, Ѫ��
	drawOthers(pMemDC);
	//�����ҷ�ս��
	drawMyPlane(pMemDC);


	//���ƹؿ�
	gameLevel.Draw(pMemDC);
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	if (m_pMe == NULL) return;
	int beforeLevel = m_pMe->getPlaneLevel();

	//�һ��ƶ�
	myPlaneMove();
	//�����л�,Boss1,Boss2������Ѫ��
	creatThings();
	//����ս������
	creatMyPlaneBullet();
	//�л������ӵ�
	creatEnemyBullet();
	//�л��ӵ�ը��ս��
	enemyBulletHitMyPlane();
	//�л���ײ�һ�
	crashMyplaneANDEnemy();
	//ս������ը���л�
	myPlaneHitEnemyPlane();
	myPlaneHitBossOneBall();
	//�ҷ����Ѫ��
	getBlood();
	//boss����
	bosshurted();
	//������һ��
	if (m_pMe == NULL) return;
	if(m_petPlaneLevel() > beforeLevel)
		gameLevel.GameLevelUp();

		//gameLevel.GameLevelUp(m_pMe->getPlaneLevel());
	
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	/*
	UpdateFrame(m_pMemDC);
	AI();
	CView::OnTimer(nIDEvent);
	*/
	if (GetKey('P') == 1)//������p��
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

	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
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
	//���Ʊ���ͼƬ
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
	pMemDC->SetBkMode(TRANSPARENT);//͸���׿�
	pMemDC->SetTextAlign(TA_CENTER);//���Ķ���
	pMemDC->SetTextColor(RGB(255, 0, 0));//������ɫ

}


void CPlaneGameView::drawMyPlane(CDC* pMemDC) //����ս�� //398
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
void CPlaneGameView::drawOthers(CDC* pMemDC)////���� ��������ը���л����ӵ�����Ʒ��������Ʒ //416
{
	//���α������������絼��

	for (int i = 0; i < THINGS_NUM; i++)
	{
		POSITION pos1, pos2;
		//����ÿһ������
		for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			//�õ���һ��������������ָ��ڶ�������
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE))//�������ʧ��
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
}
void CPlaneGameView::creatThings()//���ɵл� //453
{

	//��������л�
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

	//�������Ѫ��
	static int nBlood = rand() % 5 + 10;
	if (nBlood <= 0)
	{
		
		nBlood = gameLevel.getBloodNumCtl();
		m_ObjList[enBlood].AddTail(new CBlood);
		
	}
	nBlood--;
	//�������СBoss
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

	//�������Boss2
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
void CPlaneGameView::creatMyPlaneBullet()//����ս���ӵ�// 513
{
	//�Զ�����
	if (m_pMe != NULL && m_pMe->Fired())
	{
		CPoint pt = m_pMe->GetPoint();
		for (int i = 0; i < 3; i++)
		{
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30 * i, pt.y + 10,i));
		}
	}
	//�ֶ�����
	//if (m_pMe->GetKey(VK_SPACE) == 1 || m_pMe->GetKey(VK_LBUTTON) == 1)//�����˿ո����������
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
	//�Ҽ����䵼��
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
void CPlaneGameView::creatEnemyBullet()//���ɵл��ӵ� //543
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
		//�л���ս��ǰ��
		if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//�л���ս������
		if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//�������� ��л������ӵ�
		if (by &&ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));
		}
	}
	//Boss1 �����ӵ�
	for (POSITION ePos = m_ObjList[enBossOne].GetHeadPosition(); ePos != NULL;)
	{
		CBossOne* pBoss = (CBossOne*)m_ObjList[enBossOne].GetNext(ePos);
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();
		BOOL by = FALSE;
		//�л���ս��ǰ��
		if (pBoss->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//�л���ս������
		if (pBoss->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//����������
		//m_ObjList[enBall].AddTail(new CBall(ePt.x + 72, ePt.y + 100, pBoss->GetMontion()));
		m_ObjList[enBossOneBall].AddTail(new CBossOneBall(ePt.x + 72, ePt.y + 100, m_pMe->GetPoint()));
		//�������� ��л������ӵ�
		if (by && ePt.x +72 >= PlanePt.x && ePt.x + 72 < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
		}
	}
	//Boss2 �����ӵ�
	for (POSITION ePos = m_ObjList[enBossTwo].GetHeadPosition(); ePos != NULL;)
	{
		CBossTwo* pBoss = (CBossTwo*)m_ObjList[enBossTwo].GetNext(ePos);
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();
		BOOL by = FALSE;
		//�л���ս��ǰ��
		if (pBoss->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//�л���ս������
		if (pBoss->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;
		//����������
		//m_ObjList[enBall].AddTail(new CBall(ePt.x + 72, ePt.y + 100, pBoss->GetMontion()));
		m_ObjList[enBossOneBall].AddTail(new CBossOneBall(ePt.x + 72, ePt.y + 100, m_pMe->GetPoint()));
		for (int i = 0; i < 8; i++)
		{
			m_ObjList[enBossTwoBall].AddTail(new CBossTwoBall(pBoss->GetPoint().x, pBoss->GetPoint().y, i));
		}
		//�������� ��л������ӵ�
		if (by && ePt.x + 72 >= PlanePt.x && ePt.x + 72 < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
		}
	}

}
void CPlaneGameView::generateBlood()
{

}
void CPlaneGameView::enemyBulletHitMyPlane()//�л��ӵ�����ս�� //570
{
	//��ͨ�л��ӵ������ҷ�
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
			if (tmpRect.IntersectRect(&bRect, mRect))//����غ�
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				//ɾ���л��ӵ�
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;
				//�۳�Ѫ��
				m_pMe->takeDamage(0);
				//���Ѫ��Ϊ0 ɾ��ս�� 

				if (!m_pMe->PisAlive())
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}
	//Boss1�ӵ������ҷ�
	if (m_pMe == NULL) return;
	else
	{
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBossOneBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBossOneBall* pBB1 = (CBossOneBall*)m_ObjList[enBossOneBall].GetNext(bPos1);
			//׷��
			pBB1->UpdatePosition(m_pMe->GetPoint());
			//
			CRect bRect = pBB1->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))//����غ�
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				
				//ɾ���л��ӵ�
				m_ObjList[enBossOneBall].RemoveAt(bPos2);
				delete pBB1;
				//�۳�Ѫ��
				m_pMe->takeDamage(1);
				//���Ѫ��Ϊ0 ɾ��ս�� 

				if (!m_pMe->PisAlive())
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
		}
	}
	//Boss2�ӵ������ҷ�
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
			if (tmpRect.IntersectRect(&bRect, mRect))//����غ�
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				//ɾ���л��ӵ�
				m_ObjList[enBossTwoBall].RemoveAt(bPos2);
				delete pBB2;
				//�۳�Ѫ��
				m_pMe->takeDamage(2);//��2��
				//���Ѫ��Ϊ0 ɾ��ս�� 

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
void CPlaneGameView::crashMyplaneANDEnemy()//ս����ײ�л�// 625
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
		if (tmpRect.IntersectRect(&bRect, mRect))//����غ�
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			//ɾ���л�
			pEnemy->takeDamage(1);//-100hp
			if (!pEnemy->enIsAlive())
			{

				m_ObjList[enEnemy].RemoveAt(bPos2);
				delete pEnemy;

			}
			//�۳�Ѫ��
			m_pMe->takeDamage(0);

			//���Ѫ��Ϊ0 ɾ��ս�� 

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
				//�����л�λ��
				for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
					CRect mRect = pEnemy->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//����ཻ
					{
						//��ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//ɾ���л�ײ���Ķ���,��ɾ��Missle
						if(i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Enemy����
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pEnemy->takeDamage(hurt);
						else if (i == enMyMissle)
							pEnemy->takeDamage(-hurt);
						//ɾ���л�
						if (!pEnemy->enIsAlive())
						{
							//�÷�

							//�����ҷ�ս���ȼ�
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
		myPlaneMovePoint = opencvprocess.getGamePoint(opencvprocess.finalPoint(frame));//�����Ӿ�ʶ�����
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
		if (tmpRect.IntersectRect(&bRect, mRect))//����غ�
		{
			
			//ɾ��Ѫ��
			m_ObjList[enBlood].RemoveAt(bPos2);
			delete pBlood;
			//����Ѫ��
			m_pMe->Heal(0);
			//m_pMe->takeDamage(0);
			//���Ѫ��Ϊ0 ɾ��ս�� 

			if (!m_pMe->PisAlive())
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}
}

void CPlaneGameView::bosshurted()//boss ����
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
				//�����л�λ��
				for (ePos1 = m_ObjList[enBossOne].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossOne* pBoss = (CBossOne*)m_ObjList[enBossOne].GetNext(ePos1);
					CRect mRect = pBoss->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//����ཻ
					{
						//��ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//ɾ���л�ײ���Ķ���,��ɾ��Missle
						if (i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Boss1����
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pBoss->takeDamage(hurt);
						else if (i == enMyMissle)
							pBoss->takeDamage(-hurt);
						//ɾ���л�
						if (!pBoss->enIsAlive())
						{
							//�÷�
							m_pMe->AddScore();
							m_pMe->upgrade();
							//�����ҷ�ս���ȼ�
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
				//�����л�λ��
				for (ePos1 = m_ObjList[enBossTwo].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossTwo* pBoss = (CBossTwo*)m_ObjList[enBossTwo].GetNext(ePos1);
					CRect mRect = pBoss->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//����ཻ
					{
						//��ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//ɾ���л�ײ���Ķ���,��ɾ��Missle
						if (i != enMyMissle)
						{
							m_ObjList[i].RemoveAt(mPos2);
							delete pObj;
						}
						//Boss2����
						int hurt = gameLevel.getDamageCtl();
						if (i == enBomb)
							pBoss->takeDamage(hurt);
						else if (i == enMyMissle)
							pBoss->takeDamage(-hurt);
						//ɾ���л�
						if (!pBoss->enIsAlive())
						{
							//�÷�
							m_pMe->AddScore();
							m_pMe->upgrade();
							//�����ҷ�ս���ȼ�
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
void CPlaneGameView::myPlaneHitBossOneBall()//�����з�׷�ٵ�
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
				//�����з�׷�ٵ�λ��
				for (ePos1 = m_ObjList[enBossOneBall].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CBossOneBall* pBob = (CBossOneBall*)m_ObjList[enBossOneBall].GetNext(ePos1);
					CRect mRect = pBob->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))//����ཻ
					{
						//��ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(
							new CExplosion(mRect.left, mRect.top)
						);
						//ɾ��Bomb��Missle
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