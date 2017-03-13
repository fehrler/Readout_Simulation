#include "EventGenerator.h"

EventGenerator::EventGenerator() : filename(""), eventindex(0), clustersize(0), eventrate(0), 
					seed(0)
{

}

EventGenerator::EventGenerator(Detector* detector) : filename(""), eventindex(0), clustersize(0),
					eventrate(0), seed(0)
{
	detectors.push_back(detector);
}

EventGenerator::EventGenerator(int seed, double clustersize, double rate) : filename(""), 
					eventindex(0)
{
	this->seed 		  = seed;
	this->clustersize = clustersize;
	this->eventrate   = rate;
}

bool EventGenerator::IsReady()
{
	if(filename != "" && eventrate != 0)
		return true;
	else
		return false;
}

void EventGenerator::AddDetector(Detector* detector)
{
	if(detector != 0)
		detectors.push_back(detector);
}
	
void EventGenerator::ClearDetectors()
{
	detectors.clear();
}

Detector* EventGenerator::GetDetectorByIndex(int index)
{
	if(index >= detectors.size() || index < 0)
		return 0;
	else
		return detectors[index];
}
	
Detector* EventGenerator::GetDetectorByAddress(int address)
{
	for(auto it : detectors)
	{
		if(it->GetAddress() == address)
			return it;
	}

	return 0;
}

std::string EventGenerator::GetOutputFileName()
{
	return filename;
}

void EventGenerator::SetOutputFileName(std::string filename)
{
	this->filename = filename;
}

	/* seed for the random generator */
int EventGenerator::GetSeed()
{
	return seed;
}

void EventGenerator::SetSeed(int seed)
{
	this->seed = seed;
	eventindex = 0;		//reset the event counter on a change of the seed

	//generate a seed from the time on '0':
	if(seed == 0)
		srand(time(0));
	else
		srand(seed);
}

double EventGenerator::GetClusterSize()
{
	return clustersize;
}

void EventGenerator::SetClusterSize(double size)
{
	if(size < 0)
		size = -size;

	clustersize = size;
}

double EventGenerator::GetEventRate()
{
	return eventrate;
}

void EventGenerator::SetEventRate(double rate)
{
	eventrate = rate;
}

double EventGenerator::GetMinSize()
{
	return minsize;
}

void EventGenerator::SetMinSize(double diagonallength)
{
	if(diagonallength < 0)
		diagonallength = -diagonallength;

	minsize = diagonallength;
}

int EventGenerator::GetCutOffFactor()
{
	return numsigmas;
}

void EventGenerator::SetCutOffFactor(int numsigmas)
{
	if(numsigmas < 0)
		numsigmas = -numsigmas;

	this->numsigmas = numsigmas;
}


void EventGenerator::GenerateEvents(double firsttime, int numevents)
{
	if(!IsReady())
		return;

	//calculate the total extent of the detector arrangement:
	TCoord<double> detectorstart = detectors.front()->GetPosition();
	TCoord<double> detectorend   = detectorstart;
	for(auto it : detectors)
	{
		for(int i=0;i<3;++i)
		{
			//one coordinate smaller than the start:
			if(it->GetPosition()[i] < detectorstart[i])
				detectorstart[i] = it->GetPosition()[i];
			if(it->GetPosition()[i] + it->GetSize()[i] < detectorstart[i])
				detectorstart[i] = it->GetPosition()[i] + it->GetSize()[i];

			//one coordinate larger than the end:
			if(it->GetPosition()[i] > detectorend[i])
				detectorend[i] = it->GetPosition()[i];
			if(it->GetPosition()[i] + it->GetSize()[i] > detectorend[i])
				detectorend[i] = it->GetPosition()[i] + it->GetSize()[i];
		}
	}

	double time = firsttime;
	//generate the events:
	for (int i = 0; i < numevents; ++i)
	{
		//get a new random particle track:
		TCoord<double> direction;
		for(int i = 0; i < 3; ++i)
			direction[i] = rand() / double(RAND_MAX);
		TCoord<double> setpoint;
		for(int i = 0; i < 3; ++i)
			setpoint[i] = rand() / double(RAND_MAX) * (detectorend[i]-detectorstart[i]) 
							+ detectorstart[i];

		//generate the next time stamp:
		time += -log(rand()/double(RAND_MAX)) / eventrate;

		//generate the template hit object for this event:
		Hit hittemplate;
		hittemplate.SetTimeStamp(int(time));
		hittemplate.SetEventIndex(eventindex);
		++eventindex;

		//get the hits from the readout cells:
		std::vector<Hit> hits;
		for(auto dit : detectors)
		{
			for(auto it = dit->GetROCVectorBegin(); it != dit->GetROCVectorEnd(); ++it)
			{
				hits = ScanReadoutCell(hittemplate, &(*it), direction, setpoint);

				//copy the hits to the event queue:
				for(auto it2 : hits)
					clusterparts.push_back(it2);
			}
		}
	}
}

int EventGenerator::GetNumEventsGenerated()
{
	return eventindex;
}

std::vector<Hit> EventGenerator::GetNextEvent()
{
	std::vector<Hit> event;

	int thiseventindex = clusterparts.front().GetEventIndex();

	while(thiseventindex == clusterparts.front().GetEventIndex())
	{
			event.push_back(clusterparts.front());

			clusterparts.pop_front();
	}

	return event;
}

std::vector<Hit> EventGenerator::GetEvent(int eventindex)
{
	std::vector<Hit> event;

	if(eventindex >= this->eventindex || eventindex < clusterparts.front().GetEventIndex())
		return event;

	auto it = clusterparts.begin();
	while(eventindex > it->GetEventIndex())
		++it;
	while(eventindex == it->GetEventIndex())
	{
		event.push_back(*it);
		++it;
	}

	return event;
}

Hit EventGenerator::GetNextHit()
{
	Hit h = clusterparts.front();
	clusterparts.pop_front();

	return h;
}

Hit EventGenerator::GetHit()
{
	return clusterparts.front();
}

double EventGenerator::GetCharge(TCoord<double> x0, TCoord<double> r, TCoord<double> position,
					TCoord<double> size, double minsize, double sigma, int setzero, bool root)
{
	static int counter = 0;

	if(root)
	{
		counter = 0;
	}

	++counter;

	double distance = 0;
	double charge = 0;

	TCoord<double> pixelmiddle = position + 0.5 * size;


	distance = (x0-pixelmiddle-((pixelmiddle-x0)*r)/r.abs()/r.abs()*r).abs();
	distance -= setzero * sigma;


	if(distance >= 0.5 * size.abs())
	{
		if(root)
			std::cout << "Iterations: " << counter << std::endl;
		return 0;
	}
	else if(size.abs() >= 2 * minsize)
	{
		TCoord<double> newsize = 0.5 * size;
		//TCoord<double> newposition = pix.GetPosition();
		TCoord<double> shift = TCoord<double>::Null;
		for (int x = 0; x < 8; ++x)
		{
			if((x&1) != 0)
				shift[0] = newsize[0];
			else
				shift[0] = 0;
			if((x&2) != 0)
				shift[1] = newsize[1];
			else
				shift[1] = 0;
			if((x&4) != 0)
				shift[2] = newsize[2];
			else
				shift[2] = 0;

			charge += GetCharge(x0, r, position + shift, newsize, minsize, sigma, 
								setzero, false);
		}

		if(root)
			std::cout << "Iterations: " << counter << std::endl;
		return charge;
	}
	else
	{

		distance = (x0-pixelmiddle-((pixelmiddle-x0)*r)/r.abs()/r.abs()*r).abs();
		charge = 0.1269873/sigma*exp(-distance*distance/2/sigma/sigma) * size[0]*size[1]*size[2];

		if(root)
			std::cout << "Iterations: " << counter << std::endl;
		return charge;
	}
}


std::vector<Hit> EventGenerator::ScanReadoutCell(Hit hit, ReadoutCell* cell, 
									TCoord<double> direction, TCoord<double> setpoint)
{
	std::vector<Hit> globalhits;

	hit.AddAddress(cell->GetAddressName(), cell->GetAddress());
	if(cell == 0)
		return globalhits;
	else
	{
		//scan Sub-Cells:
		for(auto it = cell->GetROCsBegin(); it != cell->GetROCsEnd(); ++it)
		{
			//test one subdetector for hits:
			std::vector<Hit> localhits = ScanReadoutCell(hit, &(*it), direction, setpoint);

			//add the hits in the subparts of the detector to the hit vector:
			for(auto it2 : localhits)
				globalhits.push_back(it2);
		}

		//scan pixels:
		for(auto it = cell->GetPixelsBegin(); it != cell->GetPixelsEnd(); ++it)
		{
			double charge = GetCharge(setpoint, direction, it->GetPosition(), it->GetSize(), 
										minsize, clustersize, numsigmas, false);
			if(charge >= it->GetThreshold())
			{
				Hit phit = hit;
				phit.AddAddress(it->GetAddressName(),it->GetAddress());
				globalhits.push_back(phit);
			}
		}
	}

	return globalhits;
}