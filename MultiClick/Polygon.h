class CPolygon  
{
public:
	CPolygon();
	virtual ~CPolygon();
	
	int m_nPoints;
	LPPOINT m_pPoints;
	void AddPoint(POINT &point);
	void AddPoint(int x, int y);
	void Free();

};
