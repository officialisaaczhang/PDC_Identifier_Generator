#pragma once
#include <EuroScopePlugIn.h>
#include <string>
#include <random>
#include <time.h>
#include <map>

using namespace EuroScopePlugIn;
using namespace std;

class PDC_identifier :
	public EuroScopePlugIn::CPlugIn {
public:

	map<string, string> assignedIdent;

	PDC_identifier();
	virtual ~PDC_identifier();
	EuroScopePlugIn::CRadarScreen* OnRadarScreenCreated(const char* sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated);
	
	virtual void OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
		EuroScopePlugIn::CRadarTarget RadarTarget,
		int ItemCode,
		int TagData,
		char sItemString[16],
		int* pColorCode,
		COLORREF* pRGB,
		double* pFontSize);

	inline virtual void OnFunctionCall(int FunctionId,
		const char* sItemString,
		POINT Pt,
		RECT Area);

	virtual string code_Gen();

	//---OnCompileCommand------------------------------------------

	virtual bool OnCompileCommand(const char * sCommandLine);

	//---OnControllerDisconnect------------------------------------------

	virtual void OnControllerDisconnect(CController Controller);

	//---OnFlightPlanDisconnect------------------------------------------

	virtual void OnFlightPlanDisconnect(CFlightPlan FlightPlan);

	//---OnTimer------------------------------------------

	virtual void OnTimer(int Counter);

	//---OnVoiceTransmitStarted----------------------------------------

	inline  virtual void    OnVoiceTransmitStarted(bool OnPrimary);

	//---OnVoiceTransmitEnded------------------------------------------

	inline  virtual void    OnVoiceTransmitEnded(bool OnPrimary);

	//---OnVoiceReceiveStarted-----------------------------------------

	inline  virtual void    OnVoiceReceiveStarted(CGrountToAirChannel Channel);
	
	//---OnVoiceReceiveEnded-------------------------------------------

	inline  virtual void    OnVoiceReceiveEnded(CGrountToAirChannel Channel);

	//---OnAirportRunwayActivityChanged---------------------------------

	inline  virtual void    OnAirportRunwayActivityChanged(void);

	//---OnCompileFrequencyChat-----------------------------------------

	inline  virtual void    OnCompileFrequencyChat(const char * sSenderCallsign,
		double Frequency,
		const char * sChatMessage);

	//---OnCompilePrivateChat-------------------------------------------

	inline  virtual void    OnCompilePrivateChat(const char * sSenderCallsign,
		const char * sReceiverCallsign,
		const char * sChatMessage);

	//---OnControllerPositionUpdate------------------------------------

	inline  virtual void    OnControllerPositionUpdate(CController Controller);

	//---OnFlightPlanControllerAssignedDataUpdate----------------------

	inline  virtual void    OnFlightPlanControllerAssignedDataUpdate(CFlightPlan FlightPlan,
		int DataType);

	//---OnFlightPlanFlightPlanDataUpdate------------------------------

	inline  virtual void    OnFlightPlanFlightPlanDataUpdate(CFlightPlan FlightPlan);

	//---OnFlightPlanFlightStripPushed---------------------------------
	inline  virtual void    OnFlightPlanFlightStripPushed(CFlightPlan FlightPlan,
		const char * sSenderController,
		const char * sTargetController);

	//---OnNewMetarReceived--------------------------------------------

	inline  virtual void    OnNewMetarReceived(const char * sStation,
		const char * sFullMetar);

	//---OnPlaneInformationUpdate--------------------------------------

	inline  virtual void    OnPlaneInformationUpdate(const char * sCallsign,
		const char * sLivery,
		const char * sPlaneType);

	//---OnRadarTargetPositionUpdate--------------------------------------

	inline  virtual void    OnRadarTargetPositionUpdate(CRadarTarget RadarTarget);

	//---OnRefreshFpListContent----------------------------------------

	inline  virtual void    OnRefreshFpListContent(CFlightPlanList AcList);
};