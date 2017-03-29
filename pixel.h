#ifndef _PIXEL
#define _PIXEL

#include <string>

#include "hit.h"
#include "TCoord.h"

class Pixel
{
public:
    Pixel(TCoord <double> position, TCoord <double> size,
            std::string addressname, int address, double threshold);
	Pixel();

	
	TCoord<double>	GetPosition();
	void		SetPosition(TCoord<double> position);
	
	TCoord<double>	GetSize();
	void		SetSize(TCoord<double> size);
	
	double 		GetThreshold();
	void		SetThreshold(double threshold);
	
	double 		GetEfficiency();
	void		SetEfficiency(double efficiency);

	double		GetDeadTimeEnd();
	void		SetDeadTimeEnd(double enddeadtime);
	
	bool 		GetHitFlag1();
	void		SetHitFlag1(bool hitflag1);
	
	bool 		GetHitFlag2();
	void		SetHitFlag2(bool hitflag2);
	
	std::string GetAddressName();
	void		SetAddressName(std::string addressname);
	
	int 		GetAddress();
	void		SetAddress(int address);
	
	Hit 		GetHit();
	bool		CreateHit(int timestamp, double deaduntil = 0);
	
	bool		LoadFlag();
	void		ClearFlags();

private:
	TCoord<double> position;
	TCoord<double> size;
	double threshold;
	double efficiency;
	double deaduntil;	//point in time until the current "analouge hit signal" ends
						// preventing new hits 
	Hit hit;
	bool hitflag1;
	bool hitflag2;
	std::string addressname;
	int address;


};


#endif  //_PIXEL
