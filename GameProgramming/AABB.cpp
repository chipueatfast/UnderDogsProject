#include "AABB.h"
#include <limits>
//new 02-11 chipu

RECT getSweptBroadphaseRect(const GameObject* MovingObj)
{
	RECT rect;

	rect.left = MovingObj->vx() > 0 ? MovingObj->x() : MovingObj->x() + MovingObj->vx();
	rect.top = MovingObj->vy() > 0 ? MovingObj->y() : MovingObj->y() + MovingObj->vy();
	rect.right = MovingObj->vx()>0 ? MovingObj->vx() + MovingObj->width() + MovingObj->x() : MovingObj->x() + MovingObj->width();
	rect.bottom = MovingObj->vy() > 0 ? MovingObj->y() + MovingObj->height() + MovingObj->vy() : MovingObj->y() + MovingObj->height();
	return rect;
}

float CheckCollision(GameObject* MovingObj, GameObject* StaticObj)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;
	float tEntry, tExit;
	float movingX1 = MovingObj->x();
	float movingX2 = movingX1 + MovingObj->width();
	float movingY1 = MovingObj->y();
	float movingY2 = movingY1 + MovingObj->height();
	float staticX1 = StaticObj->x();
	float staticX2 = staticX1 + StaticObj->width();
	float staticY1 = StaticObj->y();
	float staticY2 = staticY1 + StaticObj->height();

	RECT dst_rect;
	IntersectRect(&dst_rect, &getSweptBroadphaseRect(MovingObj), &StaticObj->bounding_box());
	if (dst_rect.bottom==0 && dst_rect.top==0 &&dst_rect.right==0 && dst_rect.left==0)
	{
		return 1.0f;
	}
	if (MovingObj->vy() == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = -std::numeric_limits<float>::infinity();
		if (staticY1 > movingY2 || staticY2 < movingY1)
		{
			/*movingX1 += MovingObj->vx();*/
			return 1;
		}
	}
	if (MovingObj->vx() == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = -std::numeric_limits<float>::infinity();
		if (staticX1 > movingX2 || staticX2 < movingX1)
		{

			return 1.0f;
		}
	}

	if (MovingObj->vx() > 0)
	{
		//distance of near side with MovingObj->vx() > 0
		dxEntry = staticX1 - movingX2;
		//distance of far side with MovingObj->vx() > 0
		dxExit = staticX2 - movingX1;
		//time moving enter static
		txEntry = dxEntry / MovingObj->vx();
		txExit = dxExit / MovingObj->vx();

	}
	if (MovingObj->vx() < 0)
	{
		dxEntry = movingX1 - staticX2;
		dxExit = movingX2 - staticX1;

		txEntry = dxEntry / MovingObj->vx();
		txExit = dxExit / MovingObj->vx();
	}
	if (MovingObj->vy() > 0)
	{
		//distance of near side with MovingObj->vx() > 0
		dyEntry = staticY1 - movingY2;
		//distance of far side with MovingObj->vx() > 0
		dyExit = staticY2 - movingY1;
		//time moving enter static
		tyEntry = dyEntry / MovingObj->vy();
		tyExit = dyExit / MovingObj->vy();
		if (tyEntry<0)
		{
			tyEntry = 0;

		}
	}
	if (MovingObj->vy() < 0)
	{
		//distance of near side with MovingObj->vx() > 0
		dyEntry = MovingObj->y() - staticY2;
		//distance of far side with MovingObj->vx() > 0
		dyExit = movingY2 - staticY1;
		//time moving enter static
		tyEntry = dyEntry / MovingObj->vy();
		tyExit = dyExit / MovingObj->vy();
		if (tyEntry>0)
		{
			tyEntry = 0;
		}
	}

	if (tyEntry != -std::numeric_limits<float>::infinity() && txEntry != -std::numeric_limits<float>::infinity())
		tEntry = max(fabs(txEntry), fabs(tyEntry));
	else tEntry = (txEntry == -std::numeric_limits<float>::infinity()) ? tyEntry : txEntry;
	if (tyExit != std::numeric_limits<float>::infinity() && txEntry != std::numeric_limits<float>::infinity())
		tExit = min(fabs(tyExit), fabs(txExit));
	else tExit = (txExit == std::numeric_limits<float>::infinity()) ? tyExit : txExit;
	if (fabs(tEntry) <1.0f && fabs(tEntry)<fabs(tExit))
	{
		/*MovingObj->set_x(MovingObj->x() + MovingObj->vx()*tEntry);
		MovingObj->set_y(MovingObj->y() + MovingObj->vy()*tEntry);*/
		return tEntry;
	}
	return 1.0f;


}
