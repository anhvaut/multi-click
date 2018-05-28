#include "stdafx.h"
#include "Polygon.h"
CPolygon::CPolygon()
{
	m_nPoints = 0;
	m_pPoints = NULL;
}

CPolygon::~CPolygon()
{
	Free();
}

void CPolygon::AddPoint(POINT &point)
{
	m_nPoints = m_nPoints+1;

	m_pPoints = (LPPOINT) realloc(m_pPoints, m_nPoints * sizeof(POINT));

	m_pPoints[m_nPoints-1].x = point.x;
	m_pPoints[m_nPoints-1].y = point.y;
}

void CPolygon::AddPoint(int x, int y)
{
POINT point;

	point.x = x;
	point.y = y;
	AddPoint(point);

}
void CPolygon::Free()
{
	m_nPoints = 0;
	if (m_pPoints != NULL)
		free(m_pPoints);

	m_pPoints = NULL;
}
