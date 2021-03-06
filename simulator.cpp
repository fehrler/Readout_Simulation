/*
    ROME (ReadOut Modelling Environment)
    Copyright © 2017  Rudolf Schimassek (rudolf.schimassek@kit.edu),
                      Felix Ehrler (felix.ehrler@kit.edu),
                      Karlsruhe Institute of Technology (KIT)
                                - ASIC and Detector Laboratory (ADL)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    This file is part of the ROME simulation framework.
*/

#include "simulator.h"

Simulator::Simulator() : detectors(std::vector<DetectorBase*>()), eventgenerator(EventGenerator()),
		events(0), starttime(0), stoptime(-1), stopdelay(0), inputfile(""), logfile("")
{

}

Simulator::Simulator(std::string filename) : detectors(std::vector<DetectorBase*>()), 
		eventgenerator(EventGenerator()), events(0), starttime(0), stoptime(-1), stopdelay(0),
		inputfile(filename), logfile("")
{

}

std::string Simulator::GetLoadFileName()
{
	return inputfile;
}

void Simulator::LoadInputFile(std::string filename)
{
	if(filename == "")
		filename = inputfile;
	else
		inputfile = filename;

	std::cout << "Loading data from \"" << filename << "\" ..." << std::endl;

	detectors.clear();
	eventgenerator.ClearEventQueue();

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile(filename.c_str());

	doc.PrintError();

	TCoord<double> standardpixel{0,0,0};

	tinyxml2::XMLElement* simulation = doc.FirstChildElement();
	tinyxml2::XMLElement* elem = simulation->FirstChildElement();
	while(elem != 0)
	{
		std::string elementname = std::string(elem->Name());

		std::cout << "Element: " << elementname << std::endl;

		if(elementname.compare("Detector") == 0)
			LoadDetector(elem, standardpixel);
		else if(elementname.compare("Standardpixel") == 0)
			standardpixel = LoadTCoord(elem);
		else if(elementname.compare("EventGenerator") == 0)
			LoadEventGenerator(elem);
		else if(elementname.compare("SimulationEnd") == 0)
		{
			//load end time:
			tinyxml2::XMLError error = elem->QueryIntAttribute("t", &stoptime);
			if(error != tinyxml2::XML_NO_ERROR)
				stoptime = -1;
			//load delay for stopping:
			error = elem->QueryIntAttribute("stopdelay", &stopdelay);
			if(error != tinyxml2::XML_NO_ERROR)
				stopdelay = 0;
		}
		else if(elementname.compare("Logging") == 0)
		{
			const char* nam = elem->Value();
			logfile = (nam != 0)?std::string(nam):"";
		}

		if(elem != simulation->LastChildElement())
			elem = elem->NextSiblingElement();
		else
			elem = 0;
	}

	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		(*it)->EnlargeSize();
		eventgenerator.AddDetector(*it);
	}

	if(logfile != "")
	{
		std::fstream logf;
		logf.open(logfile.c_str(), std::ios::out | std::ios::app);
		if(logf.is_open())
		{
			logf << "Loading data from \"" << filename << "\" ..." << std::endl;
			logf.close();
		}
	}
}

std::string Simulator::GetLoggingFile()
{
	return logfile;
}

void Simulator::SetLoggingFile(std::string filename)
{
	logfile = filename;
}


int Simulator::GetNumEventsToGenerate()
{
	return events;
}

void Simulator::SetNumEventsToGenerate(int events)
{
	this->events = events;
}

int Simulator::GetStartTime()
{
	return starttime;
}

void Simulator::SetStartTime(int starttime)
{
	this->starttime = starttime;
}

int Simulator::GetStopTime()
{
	return stoptime;
}

void Simulator::SetStopTime(int stoptime)
{
	this->stoptime = stoptime;
}

void Simulator::RemoveStopTime()
{
	stoptime = -1;
}

int Simulator::GetStopDelay()
{
	return stopdelay;
}

void Simulator::SetStopDelay(int stopdelay)
{
	this->stopdelay = stopdelay;
}


DetectorBase* Simulator::GetDetector(int address)
{
	if(detectors.size() == 0)
		return 0;

	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		if((*it)->GetAddress() == address)
			return *it;
	}

	return 0;
}
	
void Simulator::AddDetector(DetectorBase* detector)
{
	std::cout << "Input:  "
			  << detector->GetPosition() << " size: " << detector->GetSize() << std::endl;

	detectors.push_back(detector->Clone());
	auto it = detectors.end();
	--it;
	eventgenerator.AddDetector(*it);

	//auto it = --detectors.end();
	std::cout << "Output: "
			  << (*it)->GetPosition() << " size: " << (*it)->GetSize() << std::endl;
}

void Simulator::ClearDetectors()
{
	eventgenerator.ClearDetectors();
	for(auto& it : detectors)
		delete it;
	detectors.clear();
}

int Simulator::GetNumDetectors()
{
	return detectors.size();
}

EventGenerator* Simulator::GetEventGenerator()
{
	return &eventgenerator;
}

void Simulator::InitEventGenerator()
{
	if(!eventgenerator.IsReady())
	{
		std::cout << "EventGenerator is not set up properly because of missing parameters" 
				  << std::endl;

		std::cout << "output file: \"" << eventgenerator.GetOutputFileName() << "\"" << std::endl;
		std::cout << "rate: " << eventgenerator.GetEventRate() << std::endl;
		return;
	}

	eventgenerator.GenerateEvents(starttime, events);
	events = 0;
}

void Simulator::GenerateEvents(int events, double starttime)
{
	if(starttime < 0)
		eventgenerator.GenerateEvents(events,this->starttime);
	else
		eventgenerator.GenerateEvents(events, starttime);
}

bool Simulator::ClockUp(int timestamp)
{
	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		if(!(*it)->StateMachineCkUp(timestamp, eventgenerator.GetTriggerState(timestamp)))
			return false;
	}
	return true;
}

bool Simulator::ClockDown(int timestamp)
{
	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		if(!(*it)->StateMachineCkDown(timestamp, eventgenerator.GetTriggerState(timestamp)))
			return false;
	}
	return true;
}

void Simulator::SimulateUntil(int stoptime, int delaystop)
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	if(events > 0)
	{
		eventgenerator.GenerateEvents(starttime, events);
		events = 0;
	}

	eventgenerator.PrintQueue();

	std::chrono::steady_clock::time_point endEventGen = std::chrono::steady_clock::now();

	//eventgenerator.SortTimeStamps();	//sort the trigger turn on timestamps

	int timestamp = 0;
	double nextevent = eventgenerator.GetHit().GetTimeStamp();

	int hitcounter = 0;

	while(timestamp <= stoptime || (stoptime == -1 && stopdelay >= 0))
	{
		while(timestamp >= nextevent && nextevent != -1)
		{
			//load the next event:
			std::vector<Hit> event = eventgenerator.GetNextEvent();
			//update the time stamp for the next event:
			nextevent = eventgenerator.GetHit().GetTimeStamp();

			//insert the hits of the current event into the detector(s):
			for(auto hit : event)
			{
				for(auto it = detectors.begin(); it != detectors.end(); ++it)
				{
					if((*it)->PlaceHit(hit, timestamp))
						break;
				}

				++hitcounter;
			}

			std::cout << "Inserted " << hitcounter << " signals by now..." << std::endl;
		}

		if(!ClockUp(timestamp))
			break;

		if(!ClockDown(timestamp))
			break;

		++timestamp;

		//delay the stopping of the simulation for "stop-on-done" (see while()):
		if(nextevent == -1)
		{
			//count the remaining events:
			int hitcount = 0;
			for(auto& it : detectors)
				hitcount += it->HitsEnqueued();
			if(hitcount == 0)
				--stopdelay;
		}

		std::cout << "        TS: " << timestamp << "; nextEvent: " << nextevent << "; stopdelay: "
				  << stopdelay << std::endl;
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


	//count the signals read out from the detectors:
	int dethitcounter = 0;
	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		(*it)->FlushOutput();
		(*it)->FlushBadOutput();
		dethitcounter += (*it)->GetHitCounter();
	}

	std::cout << "Simulation done." << std::endl << "  injected signals: " << hitcounter
			  << std::endl << "  read out signals: " << dethitcounter << std::endl
			  << "  Efficiency:       " << dethitcounter/double(hitcounter) << std::endl;

	std::cout << "Event Generation Time: " << TimesToInterval(begin, endEventGen) << std::endl
			  << "Simulation Time:       " << TimesToInterval(endEventGen, end) << std::endl;

	if(logfile != "")
	{
		std::fstream logf;
		logf.open(logfile.c_str(), std::ios::out | std::ios::app);
		if(logf.is_open())
		{
			logf << "Simulated " << timestamp << " timestamps" << std::endl;

			logf << "Simulation done." << std::endl 
				 << "  injected signals: " << hitcounter << std::endl 
				 << "  read out signals: " << dethitcounter << std::endl
				 << "  Efficiency:       " << dethitcounter/double(hitcounter) << std::endl;

			logf << "Event Generation Time: " << TimesToInterval(begin, endEventGen) << std::endl
				 << "Simulation Time:       " << TimesToInterval(endEventGen, end) << std::endl;

			logf.close();
		}
	}
}

void Simulator::LoadDetector(tinyxml2::XMLElement* parent, TCoord<double> pixelsize)
{
	std::cout << "  LoadDetector" << std::endl;

	static std::map<std::string, int> latestindex;

	//load address and address identifier from the file:
	std::string addressname;
	int address;
	
	const char* nam = parent->Attribute("addrname");
	addressname = (nam != 0)?std::string(nam):"det";

	tinyxml2::XMLError error = parent->QueryIntAttribute("addr", &address);
	if(error != tinyxml2::XML_NO_ERROR)
		address = 0;

	//check address for consistency and add not provided information:
	if(latestindex.find(addressname) != latestindex.end())
	{
		if(error != tinyxml2::XML_NO_ERROR)
			address = ++latestindex[addressname];
		else if(address > latestindex[addressname])
			latestindex[addressname] = address;
		//else
			//nothing to do
	}
	else
	{
		if(error != tinyxml2::XML_NO_ERROR)
			address = 0;

		latestindex.insert(std::make_pair(addressname,address));
	}

	//check for an output file name for this detector:
	nam = parent->Attribute("outputfile");
	std::string outputfile = (nam != 0)?std::string(nam):"";
	nam = parent->Attribute("losthitfile");
	std::string badoutputfile = (nam != 0)?std::string(nam):"";

	DetectorBase* det = new Detector(addressname, address);
	det->SetOutputFile(outputfile);
	det->SetBadOutputFile(badoutputfile);

	tinyxml2::XMLElement* child = parent->FirstChildElement();
	while(child != 0)
	{
		std::string childname = std::string(child->Value());
		if(childname.compare("ROC") == 0)
			det->AddROC(LoadROC(child, pixelsize));
		else if(childname.compare("Position")== 0)
			det->SetPosition(LoadTCoord(child));
		else if(childname.compare("Size") == 0)
			det->SetSize(LoadTCoord(child));
		else if(childname.compare("StateMachine") == 0)	
		{
			det = LoadStateMachine(det, child);
			//std::cout << "States included: " << det->GetNumStates() << std::endl;

			//std::cout << "State Transitions: " 
			//			<< static_cast<XMLDetector*>(det)->GetState(0)->GetNumStateTransitions()
			//			<< std::endl;
		}

		if(child != parent->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	det->EnlargeSize();

	AddDetector(det);
}

TCoord<double> Simulator::LoadTCoord(tinyxml2::XMLElement* coordinate)
{
	std::cout << "  LoadTCoord" << std::endl;

	TCoord<double> coord;
	tinyxml2::XMLError error;
	const char* axis[] = {"x","y","z"};

	for(int i = 0; i < 3; ++i)
	{
		error = coordinate->QueryDoubleAttribute(axis[i], &coord[i]);
		if(error != tinyxml2::XML_NO_ERROR)
			std::cout << "Error reading " << axis[i] << " axis" << std::endl;
	}

	return coord;
}

void Simulator::LoadEventGenerator(tinyxml2::XMLElement* eventgen)
{
	std::cout << "  LoadEventGenerator" << std::endl;

	eventgenerator = EventGenerator();

	tinyxml2::XMLElement* element = eventgen->FirstChildElement();
	while(element != 0)
	{
		std::string name = std::string(element->Value());

		if(name.compare("Seed") == 0)
		{
			int seed;
			eventgenerator.SetSeed((element->QueryIntAttribute("x0",&seed)
										== tinyxml2::XML_NO_ERROR)?seed:0);
		}
		else if(name.compare("Output") == 0)
		{
			const char* nam = element->Attribute("filename");
			if(nam != 0)
				eventgenerator.SetOutputFileName(std::string(nam));
		}
		else if(name.compare("EventRate") == 0)
		{
			double rate;
			if(element->QueryDoubleAttribute("f",&rate) != tinyxml2::XML_NO_ERROR)
				rate = 0;
			bool totalrate;
			if(element->QueryBoolAttribute("absolute", &totalrate) != tinyxml2::XML_NO_ERROR)
				totalrate = true;
			eventgenerator.SetEventRate(rate, totalrate);

		}
		else if(name.compare("ClusterSize") == 0)
		{
			double size;
			eventgenerator.SetClusterSize((element->QueryDoubleAttribute("sigma",&size)
											== tinyxml2::XML_NO_ERROR)?size:0);
		}
		else if(name.compare("CutOffFactor") == 0)
		{
			int cutoff;
			eventgenerator.SetCutOffFactor((element->QueryIntAttribute("numsigmas",&cutoff)
											== tinyxml2::XML_NO_ERROR)?cutoff:0);			
		}
		else if(name.compare("InclinationSigma") == 0)
		{
			double inclsigma;
			eventgenerator.SetInclinationSigma((element->QueryDoubleAttribute("sigma",&inclsigma)
												== tinyxml2::XML_NO_ERROR)?inclsigma:3);
		}
		else if(name.compare("ChargeScale") == 0)
		{
			double scale;
			eventgenerator.SetChargeScaling((element->QueryDoubleAttribute("scale", &scale)
											== tinyxml2::XML_NO_ERROR)?scale:1);
		}
		else if(name.compare("MinSize") == 0)
		{
			double minsize;
			eventgenerator.SetMinSize((element->QueryDoubleAttribute("diagonal", &minsize)
										== tinyxml2::XML_NO_ERROR)?minsize:1);
		}
		else if(name.compare("NumEvents") == 0)
		{
			if(element->QueryIntAttribute("n", &events) != tinyxml2::XML_NO_ERROR)
				events = 0;
		}
		else if(name.compare("EventStart") == 0)
		{
			if(element->QueryDoubleAttribute("t", &starttime) != tinyxml2::XML_NO_ERROR)
				starttime = 0;	
		}
		else if(name.compare("TriggerProbability") == 0)
		{
			double probability = 0;
			if(element->QueryDoubleAttribute("p", &probability) != tinyxml2::XML_NO_ERROR)
				eventgenerator.SetTriggerProbability(0);
			else
				eventgenerator.SetTriggerProbability(probability);
		}
		else if(name.compare("TriggerDelay") == 0)
		{
			int delay = 0;
			if(element->QueryIntAttribute("delay", &delay) != tinyxml2::XML_NO_ERROR)
				eventgenerator.SetTriggerDelay(0);
			else
				eventgenerator.SetTriggerDelay(delay);
		}
		else if(name.compare("TriggerLength") == 0)
		{
			int length = 0;
			if(element->QueryIntAttribute("length", &length) != tinyxml2::XML_NO_ERROR)
				eventgenerator.SetTriggerLength(0);
			else
				eventgenerator.SetTriggerLength(length);
		}
		else if(name.compare("Threads") == 0)
		{
			int maxthreads = 0;
			if(element->QueryIntAttribute("n",&maxthreads) != tinyxml2::XML_NO_ERROR)
				eventgenerator.SetThreads(0);
			else
				eventgenerator.SetThreads(maxthreads);
		}
		else if(name.compare("InputFile") == 0)
		{
			bool sort = true;
			if(element->QueryBoolAttribute("sort", &sort) != tinyxml2::XML_NO_ERROR)
				sort = true;
			double timeshift = 0.;
			if(element->QueryDoubleAttribute("timeshift", &timeshift) != tinyxml2::XML_NO_ERROR)
				timeshift = 0.;
			const char* nam = element->Attribute("filename");
			if(nam != 0)
				eventgenerator.LoadEventsFromFile(std::string(nam), sort, timeshift);
		}
		else if(name.compare("DeadTimeCurve") == 0 || name.compare("TimeWalkCurve") == 0)
		{
			LoadSpline(&eventgenerator, element);
		}


		if(element != eventgen->LastChildElement())
			element = element->NextSiblingElement();
		else
			element = 0;
	}
}

void Simulator::LoadSpline(EventGenerator* eventgen, tinyxml2::XMLElement* element)
{
	bool deadtime = (std::string(element->Value()).compare("DeadTimeCurve") == 0);
	tinyxml2::XMLElement* child = element->FirstChildElement();

	while(child != 0)
	{
		if(std::string(child->Value()).compare("Point") == 0)
		{
			double x, y;
			if(child->QueryDoubleAttribute("charge", &x) == tinyxml2::XML_NO_ERROR
				&& child->QueryDoubleAttribute("time", &y) == tinyxml2::XML_NO_ERROR)
			{
				if(deadtime)
					eventgen->AddDeadTimePoint(x, y);
				else
					eventgen->AddTimeWalkPoint(x, y);
			}
		}

		if(child != element->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	//save the shape of the spline to a log file if a filename is provided:
	const char* nam = element->Attribute("filename");
	std::string filename = (nam != 0)?std::string(nam):"";
	double resolution = 0.1;
	if(element->QueryDoubleAttribute("resolution", &resolution) != tinyxml2::XML_NO_ERROR)
		resolution = 0.1;

	if(filename != "")
	{
		if(deadtime)
			eventgen->SaveDeadTimeSpline(filename, resolution);
		else
			eventgen->SaveTimeWalkSpline(filename, resolution);
	}
}

std::string Simulator::PrintDetectors()
{
	std::stringstream s("");
	for(auto it = detectors.begin(); it != detectors.end(); ++it)
	{
		if(it != detectors.begin())
			s << std::endl;
		s << (*it)->PrintDetector();
	}

	return s.str();
}

ReadoutCell Simulator::LoadROC(tinyxml2::XMLElement* parent, TCoord<double> pixelsize,
								std::string defaultaddressname)
{
	std::cout << "    LoadROC" << std::endl;

	static std::map<std::string, int> latestindex;

	const char* nam = parent->Attribute("addrname");
	std::string addressname = (nam != 0)?std::string(nam):defaultaddressname;
	//if(addressname == "")
	//	addressname = defaultaddressname;

	int address;
	tinyxml2::XMLError error = parent->QueryIntAttribute("addr", &address);
	if(latestindex.find(addressname) != latestindex.end())
	{
		if(error != tinyxml2::XML_NO_ERROR)
			address = ++latestindex[addressname];
		else if(address > latestindex[addressname])
			latestindex[addressname] = address;
		//else
			//nothing to do
	}
	else
	{
		if(error != tinyxml2::XML_NO_ERROR)
			address = 0;

		latestindex.insert(std::make_pair(addressname,address));
	}

	//check whether a name for child ROCs is given:
	nam = parent->Attribute("childaddrname");
	std::string childaddressname = (nam != 0)?std::string(nam):("c" + defaultaddressname);
	//if(childaddressname == "")
	//	childaddressname = "c" + defaultaddressname;

	int queuelength;
	error = parent->QueryIntAttribute("queuelength", & queuelength);
	if(error != tinyxml2::XML_NO_ERROR)
		queuelength = 1;

	//Configuration of the ROC:
	int configuration = 0;
	
	//PPtB Readout (without alternative at the moment):
	bool pptb = true;
	error = parent->QueryBoolAttribute("pptb", &pptb);
	if(error != tinyxml2::XML_NO_ERROR)
		pptb = true;
	if(pptb)
		configuration |= ReadoutCell::PPTB;
	
	//zero suppression:
	bool zerosuppr = true;
	error = parent->QueryBoolAttribute("zerosuppression", &zerosuppr);
	if(error != tinyxml2::XML_NO_ERROR)
		zerosuppr = true;
	if(zerosuppr)
		configuration |= ReadoutCell::ZEROSUPPRESSION;

	//buffer type:
	nam = parent->Attribute("buffertype");
	std::string buffertype = (nam != 0)?std::string(nam):"FIFOBuffer";
	if(buffertype.compare("PrioBuffer") == 0)
		configuration |= ReadoutCell::PRIOBUFFER;
	else //if(buffertype.compare("FIFOBuffer") == 0)
		configuration |= ReadoutCell::FIFOBUFFER;

	//readout mechanism:
	nam = parent->Attribute("readoutmechanism");
	std::string readouttype = (nam != 0)?std::string(nam):"NoReadOnFull";
	if(readouttype.compare("OverWrite") == 0)
		configuration |= ReadoutCell::OVERWRITEONFULL;
	else if(readouttype.compare("NoOverWrite") == 0)
		configuration |= ReadoutCell::NOOVERWRITE;
	else if(readouttype.compare("OneByOne") == 0)
		configuration |= ReadoutCell::ONEBYONEREADOUT;
	else //if(readouttype.compare("NoReadOnFull") == 0)
		configuration |= ReadoutCell::NOREADONFULL;

	//Readout Delay:
	int readoutdelay = 0;
	if(parent->QueryIntAttribute("ReadoutDelay", &readoutdelay) != tinyxml2::XML_NO_ERROR)
		readoutdelay = 0;

	//Triggered ROC:
	bool triggeredroc = false;
	if(parent->QueryBoolAttribute("Triggered", & triggeredroc) != tinyxml2::XML_NO_ERROR)
		triggeredroc = false;

	ReadoutCell roc(addressname, address, queuelength, configuration);

	roc.SetReadoutDelay(readoutdelay);
	roc.SetTriggered(triggeredroc);

	tinyxml2::XMLElement* child = parent->FirstChildElement();
	while(child != 0)
	{
		std::string childname = std::string(child->Value());
		if(childname.compare("ROC") == 0)
			roc.AddROC(LoadROC(child, pixelsize, childaddressname));
		else if(childname.compare("Pixel") == 0)
			roc.AddPixel(LoadPixel(child, pixelsize));
		else if(childname.compare("NTimes") == 0)
			LoadNPixels(&roc, child, pixelsize);
		else if(childname.compare("PixelLogic") == 0)
		{
			PixelLogic* logic = LoadPixelLogic(child);
			ComplexReadout* cro = new ComplexReadout(&roc);
			cro->SetPixelLogic(logic);
			roc.SetComplexPPtBReadout(cro);
		}

		if(child != parent->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	return roc;
}

Pixel Simulator::LoadPixel(tinyxml2::XMLElement* parent, TCoord<double> pixelsize)
{
	std::cout << "    LoadPixel" << std::endl;

	TCoord<double> position;
	TCoord<double> size = pixelsize;
	double threshold = 0.;
	double efficiency = 1.;
	double deadtimescaling = 1.;

	static int lastaddress = -1;
	int address;

	tinyxml2::XMLError error = parent->QueryIntAttribute("addr", &address);
	if(error != tinyxml2::XML_NO_ERROR)
		address = ++lastaddress;
	else
		lastaddress = address;

	const char* nam = parent->Attribute("addrname");
	std::string addrname = (nam != 0)?std::string(nam):"pix";


	tinyxml2::XMLElement* properties = parent->FirstChildElement();
	while(properties != 0)
	{
		std::string name = std::string(properties->Value());
		if(name.compare("Position") == 0)
			position = LoadTCoord(properties);
		else if(name.compare("Size") == 0)
			size = LoadTCoord(properties);
		else if(name.compare("Threshold") == 0)
		{
			tinyxml2::XMLError error = properties->QueryDoubleAttribute("thr", &threshold);
			if(error != tinyxml2::XML_NO_ERROR)
				threshold = 0.;
		}
		else if(name.compare("Efficiency") == 0)
		{
			tinyxml2::XMLError error = properties->QueryDoubleAttribute("n", &efficiency);
			if(error != tinyxml2::XML_NO_ERROR)
				efficiency = 1.;
		}
		else if(name.compare("DeadTimeScaling") == 0)
		{
			tinyxml2::XMLError error = properties->QueryDoubleAttribute("factor", 
														&deadtimescaling);
			if(error != tinyxml2::XML_NO_ERROR)
				deadtimescaling = 1.;
		}

		if(properties != parent->LastChildElement())
			properties = properties->NextSiblingElement();
		else
			properties = 0;
	}

	Pixel pix(position, size, addrname, address, threshold);
	pix.SetEfficiency(efficiency);
	pix.SetDeadTimeScaling(deadtimescaling);

	return pix;
}

PixelLogic* Simulator::LoadPixelLogic(tinyxml2::XMLElement* parent)
{
	if(parent == 0)
		return 0;

	PixelLogic* logic = new PixelLogic();

	const char* nam = parent->Attribute("operator");
	std::string operation = (nam != 0)?std::string(nam):"";

	//load the relation between the pixels:
	if(operation.compare("Or") == 0)
		logic->SetRelation(PixelLogic::Or);
	else if(operation.compare("Nor") == 0)
		logic->SetRelation(PixelLogic::Nor);
	else if(operation.compare("And") == 0)
		logic->SetRelation(PixelLogic::And);
	else if(operation.compare("Nand") == 0)
		logic->SetRelation(PixelLogic::Nand);
	else if(operation.compare("Xor") == 0)
		logic->SetRelation(PixelLogic::Xor);
	else if(operation.compare("Xnor") == 0)
		logic->SetRelation(PixelLogic::Xnor);
	else if(operation.compare("Not") == 0)
		logic->SetRelation(PixelLogic::Not);
	//else	//with this line a missing operation results in an error, without it an OR is assumed
	//	return 0;

	tinyxml2::XMLElement* child = parent->FirstChildElement();
	while(child != 0)
	{
		std::string name = child->Value();

		if(name.compare("Pixel") == 0)
		{
			int address;
			if(child->QueryIntAttribute("addr", &address) != tinyxml2::XML_NO_ERROR)
				address = -1;
			bool ownaddress;
			if(child->QueryBoolAttribute("own", &ownaddress) != tinyxml2::XML_NO_ERROR)
				ownaddress = false;

			logic->AddPixelAddress(address, ownaddress);
		}
		else if(name.compare("PixelLogic") == 0)
			logic->AddPixelLogic(LoadPixelLogic(child));

		if(child != parent->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	std::cout << "Logic Sizes: all " << logic->GetNumPixelAddresses() << "; own "
				<< logic->GetNumOwnPixelAddresses() << std::endl;

	return logic;
}

void Simulator::LoadNPixels(ReadoutCell* parentcell, tinyxml2::XMLElement* parentnode, 
							TCoord<double> pixelsize, TCoord<double> globalshift)
{
	std::cout << "    LoadNPixels" << std::endl;

	//for a PPtB ROC, the pixel addresses have to be provided:
	if(parentcell == 0)
		return;

	int numelements;
	TCoord<double> shift;
	tinyxml2::XMLError error;

	error = parentnode->QueryIntAttribute("n", &numelements);
	if(error != tinyxml2::XML_NO_ERROR)
		numelements = 0;
	shift = LoadTCoord(parentnode);

	Pixel pix;
	ReadoutCell roc;
	tinyxml2::XMLElement* elem = parentnode->FirstChildElement();
	while(elem != 0)
	{
		std::string name = std::string(elem->Value());
		if(name.compare("Pixel") == 0)
		{
			pix = LoadPixel(elem, pixelsize);

			if(pix.GetAddress() < parentcell->GetNumPixels())
				pix.SetAddress(parentcell->GetNumPixels());
			if(globalshift != TCoord<double>::Null)
				pix.SetPosition(pix.GetPosition() + globalshift);
			for(int i = 0; i < numelements; ++i)
			{
				parentcell->AddPixel(pix);
				pix.SetPosition(pix.GetPosition() + shift);
				pix.SetAddress(pix.GetAddress() + 1);
			}
		}
		else if(name.compare("ROC") == 0)
		{
			roc = LoadROC(elem, pixelsize, "c" + parentcell->GetAddressName());

			if(roc.GetAddress() < parentcell->GetNumROCs())
				roc.SetAddress(parentcell->GetNumROCs());
			if(globalshift != TCoord<double>::Null)
				roc.ShiftCell(globalshift);
			for(int i = 0; i< numelements; ++i)
			{
				parentcell->AddROC(roc);
				roc.ShiftCell(shift);
				roc.SetAddress(roc.GetAddress() + 1);
			}
		}
		else if(name.compare("NTimes") == 0)
		{
			TCoord<double> thisshift = globalshift;

			for(int i = 0; i < numelements; ++i)
			{
				LoadNPixels(parentcell, elem, pixelsize, thisshift);
				thisshift += shift;
			}
		}

		if(elem != parentnode->LastChildElement())
			elem = elem->NextSiblingElement();
		else
			elem = 0;
	}

	return;
}

XMLDetector* Simulator::LoadStateMachine(DetectorBase* detector, 
				tinyxml2::XMLElement* statemachine)
{
	std::cout << "  LoadStateMachine" << std::endl;

	if(detector == 0 || statemachine == 0)
		return 0;

	tinyxml2::XMLError error;

	//transform the detector to an XMLDetector:
	XMLDetector* det = new XMLDetector(detector->GetAddressName(), detector->GetAddress());

	det->SetPosition(detector->GetPosition());
	det->SetSize(detector->GetSize());

	for(auto it = detector->GetROCVectorBegin(); it != detector->GetROCVectorEnd(); ++it)
		det->AddROC(*it);

	det->SetBadOutputFile(detector->GetBadOutputFile());
	det->SetOutputFile(detector->GetOutputFile());



	tinyxml2::XMLElement* child = statemachine->FirstChildElement();

	while(child != 0)
	{
		std::string value = std::string(child->Value());
		if(value.compare("Counter") == 0)
		{
			const char* nam = child->Attribute("name");
			std::string countername = (nam != 0)?std::string(nam):"";
			if(countername != "")
			{
				double cvalue;
				error = child->QueryDoubleAttribute("value", &cvalue);
				det->AddCounter(countername, cvalue);
			}
		}
		else if(value.compare("State") == 0)
					det->AddState(LoadState(child));

		if(child != statemachine->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	while(det->GetState(det->GetState())->GetStateName().compare("synchronisation") == 0 
		&& det->GetState() < det->GetNumStates())
		det->SetState(det->GetState()+1);

	return det;
}

StateMachineState* Simulator::LoadState(tinyxml2::XMLElement* stateelement)
{
	std::cout << "    LoadState: "; // << std::endl;

	StateMachineState* state = new StateMachineState();

	if(stateelement == 0)
		return state;

	const char* nam;
	nam = stateelement->Attribute("name");
	std::string statename = (nam != 0)?std::string(nam):"";
	static int statecounter = 0;
	if(statename == "")
	{
		std::stringstream s("");
		s << "State_" << statecounter++;
		statename = s.str();
	}

	state->SetStateName(statename);

	std::cout << statename << std::endl;

	tinyxml2::XMLElement* child = stateelement->FirstChildElement();
	while(child != 0)
	{
		std::string value = std::string(child->Value());
		if(value.compare("Action") == 0)
			state->AddRegisterChange(LoadRegisterChange(child));
		else if(value.compare("StateTransition") == 0)
		{
			state->AddStateTransition(LoadStateTransition(child));
		}

		if(child != stateelement->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	return state;
}

RegisterAccess Simulator::LoadRegisterChange(tinyxml2::XMLElement* registerchange)
{
	std::cout << "      LoadRegisterChange: "; // << std::endl;

	RegisterAccess regacc;

	if(registerchange == 0)
		return regacc;

	const char* nam = registerchange->Attribute("what");
	regacc.what = (nam != 0)?std::string(nam):"";

	std::cout << regacc.what << std::endl;

	nam = registerchange->Attribute("parameter");
	regacc.parameter = (nam != 0)?std::string(nam):"";

	tinyxml2::XMLError error = registerchange->QueryDoubleAttribute("value", &regacc.value);
	if(error != tinyxml2::XML_NO_ERROR)
		regacc.value = 0;

	return regacc;
}

StateTransition* Simulator::LoadStateTransition(tinyxml2::XMLElement* transition)
{
	std::cout << "      LoadStateTransition to "; // << std::endl;

	StateTransition* trans = new StateTransition();

	if(transition == 0)
		return trans;

	//name of the next state:
	const char* nam = transition->Attribute("nextstate");
	trans->SetNextState((nam != 0)?std::string(nam):"");

	std::cout << trans->GetNextState() << std::endl;

	//transition delay:
	int delay;
	tinyxml2::XMLError error = transition->QueryIntAttribute("delay", &delay);
	if(error != tinyxml2::XML_NO_ERROR)
		delay = 0;
	trans->SetDelay(delay);

	tinyxml2::XMLElement* child = transition->FirstChildElement();
	while(child != 0)
	{
		std::string value = std::string(child->Value());
		if(value.compare("Action") == 0)
			trans->AddRegisterChange(LoadRegisterChange(child));
		else if(value.compare("Condition") == 0)
			trans->SetComparison(LoadComparison(child));

		if(child != transition->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	return trans;
}

Comparison* Simulator::LoadComparison(tinyxml2::XMLElement* comparison)
{
	std::cout << "      LoadComparison" << std::endl;

	Comparison* comp = new Comparison();
	if(comparison == 0)
		return comp;

	const char* nam = comparison->Attribute("relation");
	std::string rel = (nam != 0)?std::string(nam):"";
	if(rel.compare("Smaller") == 0)
		comp->SetRelation(Comparison::Smaller);
	else if(rel.compare("SmallerEqual") == 0)
		comp->SetRelation(Comparison::SmallerEqual);
	else if(rel.compare("Larger") == 0)
		comp->SetRelation(Comparison::Larger);
	else if(rel.compare("LargerEqual") == 0)
		comp->SetRelation(Comparison::LargerEqual);
	else if(rel.compare("Equal") == 0)
		comp->SetRelation(Comparison::Equal);
	else if(rel.compare("NotEqual") == 0)
		comp->SetRelation(Comparison::NotEqual);
	else if(rel.compare("Or") == 0)
		comp->SetRelation(Comparison::Or);
	else if(rel.compare("And") == 0)
		comp->SetRelation(Comparison::And);
	else if(rel.compare("Xor") == 0)
		comp->SetRelation(Comparison::Xor);
	else
	{
		std::cout << "Error: Missing relation" << std::endl;
		comp->SetRelation(-1);
	}

	tinyxml2::XMLElement* child = comparison->FirstChildElement();
	while(child != 0)
	{
		std::string value = std::string(child->Value());
		if(value.compare("Lvalue") == 0)
		{
			double lval;
			if(child->QueryDoubleAttribute("value", &lval) == tinyxml2::XML_NO_ERROR)
				comp->SetFirstValue(lval);
			else
			{
				tinyxml2::XMLElement* grandchild = child->FirstChildElement();
				if(grandchild != 0)
				{
					std::string val = std::string(grandchild->Value());
					if(val.compare("Action") == 0)
						comp->SetFirstRegisterAccess(LoadRegisterChange(grandchild));
					else if(val.compare("Condition") == 0)
						comp->SetFirstComparison(LoadComparison(grandchild));
					else
						std::cout << "Error: Missing LValue" << std::endl;
				}
			}
		}
		else if(value.compare("Rvalue") == 0)
		{
			double rval;
			if(child->QueryDoubleAttribute("value", &rval) == tinyxml2::XML_NO_ERROR)
				comp->SetSecondValue(rval);
			else
			{
				tinyxml2::XMLElement* grandchild = child->FirstChildElement();
				if(grandchild != 0)
				{
					std::string val = std::string(grandchild->Value());
					if(val.compare("Action") == 0)
						comp->SetSecondRegisterAccess(LoadRegisterChange(grandchild));
					else if(val.compare("Condition") == 0)
						comp->SetSecondComparison(LoadComparison(grandchild));
					else
						std::cout << "Error: Missing RValue" << std::endl;
				}
			}
		}


		if(child != comparison->LastChildElement())
			child = child->NextSiblingElement();
		else
			child = 0;
	}

	std::cout << "       Create Relation: " << comp->GetRelation() << std::endl;

	std::cout << "comparisonLoader:" << std::endl << comp->PrintComparison(" ");

	return comp;
}

std::string Simulator::TimesToInterval(TimePoint start, TimePoint end)
{
	long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::stringstream timetext("");
	bool started = false;

	if(duration > 86400000)	//1 day
	{
		timetext << duration/86400000 << " days";
		duration %= 86400000;
		started = true;
	}
	if(duration > 3600000)	//1 hour
	{
		if(started)
			timetext << " ";
		else
			started = true;
		timetext << duration/3600000 << " hours";
		duration %= 3600000;
	}
	if(duration > 60000)	//1 minute
	{
		if(started)
			timetext << " ";
		else
			started = true;
		timetext << duration/60000 << " minutes";
		duration %= 60000;
	}
	if(duration > 1000)
	{
		if(started)
			timetext << " ";
		else
			started = true;
		timetext << duration/1000 << " seconds";
		duration %= 1000;
	}

	if(started)
		timetext << " ";
	if(duration != 0)
		timetext << duration << " milliseconds";

	if(!started && duration == 0)
		return "0 milliseconds";

	return timetext.str();
}