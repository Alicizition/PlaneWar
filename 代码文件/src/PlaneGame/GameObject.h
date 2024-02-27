#pragma once
#include<string>
//��Ϸ����ĸ���
class CGameObject : public CObject
{
public:

	CGameObject(int x=0,int y=0);
	virtual ~CGameObject();
	
	//���ƶ���
	virtual BOOL Draw(CDC* pDC,int bPause)=0;

	//��þ�������
	virtual CRect GetRect()=0;

	//������Ͻ�����
	CPoint GetPoint();
protected:
	//����ͼ��
	static BOOL LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial);
protected:
	//�����λ��
	CPoint  m_ptPos;
};


