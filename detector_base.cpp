#include "detector_base.h"

DetectorBase::DetectorBase() : 
        addressname(""), address(0), rocvector(std::vector<ReadoutCell>()), currentstate(PullDown)
{
	
}

DetectorBase::DetectorBase(std::string addressname, int address)
{
	this->addressname = addressname;
	this->address = address;
	rocvector = std::vector<ReadoutCell>();
        currentstate = PullDown;
}

std::string DetectorBase::GetAddressName()
{
	return addressname;
}

void DetectorBase::SetAddressName(std::string addressname)
{
	if(addressname != "")
        this->addressname = addressname;
}
	
int DetectorBase::GetAddress()
{
	return address;
}

void DetectorBase::SetAddress(int address)
{
	this->address = address;
}
	
ReadoutCell* DetectorBase::GetROC(int index)
{
	if (index < rocvector.size())
		return &rocvector[index];
	else
		return NULL;
}

ReadoutCell* DetectorBase::GetROCAddress(int address)
{
	for (auto it = rocvector.begin(); it != rocvector.end(); it++)
	{
		if (it->GetAddress() == address)
			return &(*it);
	}
	return NULL;
}

void DetectorBase::AddROC(ReadoutCell readoutcell)
{
	rocvector.push_back(readoutcell);
}

void DetectorBase::ClearROCVector()
{
	rocvector.clear();
}

std::vector<ReadoutCell>::iterator DetectorBase::GetROCVectorBegin()
{
	return rocvector.begin();
}

std::vector<ReadoutCell>::iterator DetectorBase::GetROCVectorEnd()
{
	return rocvector.end();
}

	
void DetectorBase::SaveHit(Hit hit, std::string filename, bool compact)
{
    std::fstream outfile;
    outfile.open(filename.c_str(), std::ios::out);
    if(!outfile.is_open())
    {
        std::cout << "Could not open outputfile \"" << filename << "\"" << std::endl;
        return;
    }

    outfile << hit.GenerateString(compact) << std::endl;
    outfile.close();
}

TCoord<double> DetectorBase::GetPosition()
{
	return position;
}

void DetectorBase::SetPosition(TCoord<double> position)
{
	this->position = position;
}
	
TCoord<double> DetectorBase::GetSize()
{
	return size;
}

void DetectorBase::SetSize(TCoord<double> size)
{
    this->size = size;
}

bool DetectorBase::SizeOKROC(ReadoutCell* cell)
{
    for(auto it = cell->GetROCsBegin(); it != cell->GetROCsEnd(); it++)
    {
        if(!SizeOKROC(&(*it)))
            return false;
    }

    for(auto it = cell->GetPixelsBegin(); it != cell->GetPixelsEnd(); it++)
    {
        for (int i = 0; i < 3; i++)
        {
            if(it->GetPosition()[i] + it->GetSize()[i] > this->GetPosition()[i] + this->GetSize()[i])
                return false;
            if(it->GetPosition()[i] < this->GetPosition()[i])
                return false;
        }

    }
    return true;
}

bool DetectorBase::SizeOK()
{
    for(auto it = rocvector.begin(); it != rocvector.end(); it++)
    {
        if (!SizeOKROC(&(*it)))
            return false;
    }
    return true;
}

bool DetectorBase::EnlargeSizeROC(ReadoutCell *cell)
{
    bool corrected=false;
    for(auto it = cell->GetROCsBegin(); it != cell->GetROCsEnd(); it++)
    {
        if(EnlargeSizeROC(&(*it)))
            corrected = true;
    }

    for(auto it = cell->GetPixelsBegin(); it != cell->GetPixelsEnd(); it++)
    {
        TCoord<double> parentpos = this->GetPosition();
        TCoord<double> childpos = it->GetPosition();
        TCoord<double> parentsize = this->GetSize();
        TCoord<double> childsize = it->GetSize();

        bool correction = false;

        for (int i = 0; i <3; i++)
        {
            if(childpos[i] < parentpos[i])
            {
                correction = true;
                parentsize[i] += parentpos[i] - childpos[i];
                parentpos[i] = childpos[i];
            }
            if(childpos[i] + childsize[i] > parentpos[i] + parentsize[i])
            {
                correction = true;
                parentsize[i]  = childpos[i] + childsize[i] - parentpos[i];
            }
        }
        if (correction)
        {
            this->SetPosition(parentpos);
            this->SetSize(parentsize);
            corrected = true;
        }
    }
    return corrected;
}

bool DetectorBase::EnlargeSize()
{
    bool corrected = false;
    for(auto it = rocvector.begin(); it != rocvector.end(); it++)
    {
        if(EnlargeSizeROC(&(*it)))
            corrected = true;
    }
    return corrected;
}

void DetectorBase::SetState(int nextstate)
{
    this->currentstate = nextstate;
}

int DetectorBase::GetState()
{
    return currentstate;
}

bool DetectorBase::PlaceHit(Hit hit, double deadtimeend)
{
    if (rocvector.size() < 1)
        return false;

    std::string addressname = rocvector.front().GetAddressName();
    for (auto &it : rocvector)
    {
        int address = hit.GetAddress(addressname);
        std::cout << "roc addressname: " << addressname << std::endl;
        std::cout << "hit getaddress: " << address << std::endl;
        if (it.GetAddress() == address)
            return it.PlaceHit(hit, deadtimeend);
    }

    return false;
}

std::string DetectorBase::PrintDetector()
{
	std::stringstream s("");

	s << "Detector " << address << " Contents:\n";
	for(auto it : rocvector)
		s << it.PrintROC(" ");

	return s.str();
}