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

#ifndef _HIT
#define _HIT

#include <string>
#include <sstream>
#include <map>
#include <utility>

class Hit
{
public:
	Hit();
	Hit(const Hit& hit);
	/**
	 * @brief generates a hit from a string as generated by GenerateString()
	 * @details
	 * 
	 * @param hitdata   - the string containing the hit information
	 */
	Hit(std::string hitdata);

	/**
	 * @brief checks whether the hit belongs to an existing event
	 * @details 
	 * @return     - true if the event is valid, false if a parameter is not set
	 */
	bool 	is_valid();
	/**
	 * @brief determines whether the hit can be read out or not, does not affect is_valid()
	 * @details 
	 * @param timestamp      - timestamp to test
	 * @return     - true if the availablity delay has passed, false otherwise
	 */
	bool 	is_available(int timestamp  = 0);

	/**
	 * @brief provides the time stamp of the hit
	 * @details 
	 * @return     - the time stamp of the hit
	 */
	double 	GetTimeStamp();
	void 	SetTimeStamp(double timestamp);

	/**
	 * @brief provides the identifying index linking the hit to an event
	 * @details
	 * @return     - the event index
	 */
	int  	GetEventIndex();
	void 	SetEventIndex(int index);

	/**
	 * @brief provides the time when the pixel can again detect a hit after this one
	 * @details
	 * @return     - the point in time when the pixel is "armed" again
	 */
	double 	GetDeadTimeEnd();
	void 	SetDeadTimeEnd(double time);

	/**
	 * @brief provides the charge that generated this hit
	 * @details 
	 * @return     - the charge generating this hit
	 */
	double 	GetCharge();
	void	SetCharge(double charge);

	/**
	 * @brief provides the delay from implanting the hit into a readoutcell until it can be
	 *                  read out again
	 * @details
	 * @return     - the point in time in units of timestamps
	 */
	int 	GetAvailableTime();
	void 	SetAvailableTime(int timestamp);

	/**
	 * @brief adds an address-name - address pair to the hit
	 * @details
	 * 
	 * @param name - the name of this address (e.g. "Column")
	 * @param addr - the address going with this identifier
	 */
	void 	AddAddress(std::string name, int addr);
	/**
	 * @brief returns the address to the given identifier or an invalid address
	 * @details
	 * 
	 * @param name - the identifier to the address to return
	 * @return     - the address to the given identifier or "-1" on an invalid identifier
	 */
	int  	GetAddress(std::string name);
	/**
	 * @brief change an existing address part; to add a new address field, use AddAddress()
	 * @details
	 * 
	 * @param name - the identifier to the address part to change
	 * @param addr - the new value for the address part given by `name`
	 * 
	 * @return     - true on success, false if the identifier `name` was not found
	 */
	bool 	SetAddress(std::string name, int addr);
	/**
	 * @brief provides the number of parts of the address
	 * @details
	 * @return     - the number of parts in the address (e.g. pixel address, column address => 2)
	 */
    int  	AddressSize();
    /**
     * @brief delete all address parts
     * @details
     */
	void 	ClearAddress();

	/**
	 * @brief adds a timestamp for the readout into a higher level buffer
	 * @details
	 * 
	 * @param name - address part identifier where the hit is read out to (e.g. "Column" for 
	 *                 shifting to the column buffer)
	 * @param timestamp - the time stamp when the hit is transferred to the structure
	 */
	void 	AddReadoutTime(std::string name, int timestamp);
	/**
	 * @brief returns the readout time for the structure with the passed address identifier
	 * @details
	 * 
	 * @param name - address part identifier
	 * @return     - the readout time stamp or "-1" on an invalid address part identifier
	 */
	int 	GetReadoutTime(std::string name);
	/**
	 * @brief changes an existing readout time stamp
	 * @details
	 * 
	 * @param name - the address part identifier of the entry to change
	 * @param timestamp - the new time stamp for this readout address part
	 * 
	 * @return     - true on successful change, false if the address part identifier was not found
	 */
	bool 	SetReadoutTime(std::string name, int timestamp);
	/**
	 * @brief returns the number of readout time stamps
	 * @details 
	 * @return     - the number of readout time stamps
	 */
	int 	ReadoutTimeSize();
	/**
	 * @brief deletes all readout time stamps from this hit
	 * @details 
	 */
	void 	ClearReadoutTimes();

	/**
	 * @brief generates a string containing all information of the hit
	 * @details
	 * 
	 * @param compact   - if false, the address part identifier names are included, if false
	 *                       they are skipped
	 * @return     - a string containing the hit information
	 */
	std::string GenerateString(bool compact = false);

	/**
	 * @brief operator for sorting hits chronologically
	 * @details
	 * 
	 * @param second         - the hit object to compare this one to
	 * @return               - true if this hit object has a smaller timestamp than the one passed
	 *                            as a parameter, false if not
	 */
	bool operator<(const Hit& second);
private:
	int 	eventindex;
	double 	timestamp;
	double 	deadtimeend;
	double 	charge;

	int availablefrom;		//timestamp from which on the hit is available for output

	std::map<std::string, int> address;
	std::map<std::string, int> readouttimestamps;
};

#endif //_HIT
