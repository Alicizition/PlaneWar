#include "stdafx.h"
#include "BossTwoBall.h"

CImageList CBossTwoBall::m_Images;

CBossTwoBall::CBossTwoBall(int x, int y, CPoint tgtp) : CGameObject(x, y)
{
    m_speed = 8;
    m_ddirectionX = 0;
    m_ddirectionY = 0;
    img_index = 0;
    m_nMotion = 0;
}

CBossTwoBall::CBossTwoBall(int x, int y, int direction) : CGameObject(x, y)
{
    m_speed = 3;
    m_ddirectionX = 0;
    m_ddirectionY = 0;
    img_index = 0;
    m_nMotion = 0;
    m_direction = direction;
}

CBossTwoBall::~CBossTwoBall(void)
{
}

CRect CBossTwoBall::GetRect()
{
    return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_WIDTH, m_ptPos.y + BALL_HEIGHT));
}


BOOL CBossTwoBall::Draw(CDC* pDC, int bPause)
{

    Move();

    if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
        return FALSE;
    if (m_ptPos.y < -BALL_HEIGHT)
        return FALSE;

    m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

    return TRUE;
}

BOOL CBossTwoBall::LoadImage()
{
    return CGameObject::LoadImage(m_Images, IDB_BALL2, RGB(0, 0, 0), 30, 30, 1);
}

void CBossTwoBall::Move()
{
    switch (m_direction)
    {
    case 0: //上
        m_ptPos.y -= m_speed * 3;

        break;
    case 1://右上
        m_ptPos.x += m_speed * 2;
        m_ptPos.y -= m_speed * 2;
        break;
    case 2://右
        m_ptPos.x += m_speed * 3;
        break;
    case 3://右下
        m_ptPos.x += m_speed * 2;
        m_ptPos.y += m_speed * 2;
        break;
    case 4://下
        m_ptPos.y += m_speed * 3;
        break;
    case 5://左下
        m_ptPos.x -= m_speed * 2;
        m_ptPos.y += m_speed * 2;
        break;
    case 6://左
        m_ptPos.x -= m_speed * 3;
        break;
    case 7://左上
        m_ptPos.x -= m_speed * 2;
        m_ptPos.y -= m_speed * 2;
        break;
    default:
        break;
    }
}