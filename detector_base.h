#ifndef _DETECTORBASE
#define _DETECTORBASE

#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "hit.h"
#include "pixel.h"
#include "readoutcell.h"
#include "TCoord.h"

class DetectorBase
{
public:
    DetectorBase(std::string addressname, int address);
	DetectorBase();
	DetectorBase(const DetectorBase& templ);
	~DetectorBase();
	

    std::string GetAddressName();
	void		SetAddressName(std::string addressname);
	
	int 		GetAddress();
	void		SetAddress(int address);
	
    ReadoutCell*    GetROC(int index);
    ReadoutCell*    GetROCAddress(int address);
	void		AddROC(ReadoutCell readoutcell);
	void		ClearROCVector();
	std::vector<ReadoutCell>::iterator GetROCVectorBegin();
	std::vector<ReadoutCell>::iterator GetROCVectorEnd();
	
	
	TCoord<double>	GetPosition();
	void		SetPosition(TCoord<double> position);
	
	TCoord<double>	GetSize();
	void		SetSize(TCoord<double> size);

    bool        SizeOK();
    bool        EnlargeSize();
	
    virtual bool        StateMachineCkUp(int timestamp, bool trigger = true);
    virtual bool 		StateMachineCkDown(int timestamp, bool trigger = true);
    virtual bool		StateMachine(int timestamp, bool trigger = true);

    bool        PlaceHit(Hit hit);
	void 		SaveHit(Hit hit, std::string filename, bool compact);
	bool		SaveHit(Hit hit, bool compact = false);
	bool		SaveBadHit(Hit hit, bool compact = false);
	int 		HitsEnqueued();
	int 		HitsAvailable(std::string addressname);

	std::string	GetOutputFile();
	void 		SetOutputFile(std::string filename);
	void 		CloseOutputFile();

	std::string	GetBadOutputFile();
	void 		SetBadOutputFile(std::string filename);
	void 		CloseBadOutputFile();

	int 		GetHitCounter();
	void		ResetHitCounter();

    std::string PrintDetector();
    
    virtual int 	GetState();
    virtual int 	GetNextState();
    virtual std::string GetCurrentStateName();

    virtual DetectorBase* Clone();

    virtual int GetNumStates();

protected:
	std::string addressname;
	int address;
	std::vector<ReadoutCell> rocvector;
	TCoord<double> position;
    TCoord<double> size;

    bool    SizeOKROC(ReadoutCell* cell);
    bool 	EnlargeSizeROC(ReadoutCell* cell);

    int hitcounter;
    std::string outputfile;
    std::fstream fout;

    int badhitcounter;
    std::string badoutputfile;
    std::fstream fbadout;

};


#endif  //_DETECTORBASE
