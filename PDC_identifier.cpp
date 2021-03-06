// PDC_identifier.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PDC_identifier.h"

using namespace EuroScopePlugIn;
using namespace std;

PDC_identifier* gpPDC_identifier = NULL;

void __declspec (dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn ** ppPlugInInstance) {
	*ppPlugInInstance = gpPDC_identifier = new PDC_identifier;
}

void __declspec (dllexport) EuroScopePlugInExit(void) {
	delete gpPDC_identifier;
}

const int TAG_ITEM_PDC = 5000;
const int TAG_FUNC_PDC_REQ = 5001;
const int TAG_FUNC_PDC_RESET = 5002;

PDC_identifier::PDC_identifier() : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
	"PDC_identifier",
	"1.2.2",
	"Isaac Zhang",
	"Free to be distributed as source code") {

	RegisterTagItemType("PDC", TAG_ITEM_PDC);
	RegisterTagItemFunction("Grant PDC", TAG_FUNC_PDC_REQ);
	RegisterTagItemFunction("Reset", TAG_FUNC_PDC_RESET);

}

PDC_identifier::~PDC_identifier()
{
}

EuroScopePlugIn::CRadarScreen * PDC_identifier::OnRadarScreenCreated(const char * sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
{
	return nullptr;
}

void PDC_identifier::OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
	EuroScopePlugIn::CRadarTarget RadarTarget,
	int ItemCode,
	int TagData,
	char sItemString[16],
	int* pColorCode,
	COLORREF* pRGB,
	double* pFontSize) {

	if (ItemCode == TAG_ITEM_PDC) {
		if (assignedIdent.count(FlightPlan.GetCallsign())) {
			const char* ID = (assignedIdent[FlightPlan.GetCallsign()].c_str());
			strcpy_s(sItemString, 16, ID);
		}
	}
}

inline void PDC_identifier::OnFunctionCall(int FunctionId, const char * sItemString, POINT Pt, RECT Area)
{
	CFlightPlan fp;
	fp = FlightPlanSelectASEL();
	CFlightPlanData data;
	data = fp.GetFlightPlanData();
	CFlightPlanControllerAssignedData cData;
	cData = fp.GetControllerAssignedData();
	if (FunctionId == TAG_FUNC_PDC_REQ) {
		// Generate Code
		string Code_Given = code_Gen();

		// For syncing purposes
		const char * code = Code_Given.c_str();
		fp.GetControllerAssignedData().SetScratchPadString(code);

		
		if (assignedIdent.count(fp.GetCallsign())) {
			// Assign New Code
			assignedIdent[fp.GetCallsign()].swap(Code_Given);
		}
		else {
			// Assign Code
			assignedIdent.insert({fp.GetCallsign(), Code_Given});
		}
		
		// PDC data
		string Controller = ControllerMyself().GetCallsign();
		string Callsign = fp.GetCallsign();
		string DEP = data.GetOrigin();
		string ARR = data.GetDestination();
		string FALTT = to_string(fp.GetFinalAltitude());
		string SID = data.GetSidName();
		string DRWY = data.GetDepartureRwy();
		string SQWK = cData.GetSquawk();
		
		// PDC message construction
		string message = "PDC - CALLSIGN: " + Callsign + " - DEP: " + DEP + " - ARR: " + ARR + " - FLIGHT PLANNED ROUTE - ALTITUDE: " + FALTT + " - SID: " + SID + " - DEP RWY: " + DRWY + " - SQUAWK: " + SQWK + " - DEP HDG & ALT AS PUBLISHED ON SID - IDENTIFIER: " + assignedIdent[fp.GetCallsign()] + " - READ BACK IDENTIFIER AND SID ON FREQUENCY";
		
		// PDC preview
		PDC_identifier::DisplayUserMessage(Callsign.c_str(), "PDC Preview",
			message.c_str(),
			false,
			true,
			true,
			true,
			false);

		// Clipboard Output
		const char* output = message.c_str();
		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
	if (FunctionId == TAG_FUNC_PDC_RESET) {
		if (assignedIdent.count(fp.GetCallsign())) {
			assignedIdent.erase(fp.GetCallsign());
		}
	}
}

// Random PDC Identifier Generator
string PDC_identifier::code_Gen()
{
	srand(time(NULL));
	string num1 = to_string(rand() % 10);
	string num2 = to_string(rand() % 10);
	string num3 = to_string(rand() % 10);
	char letter = 'A' + rand() % 26;
	string code = num1 + num2 + num3 + letter;
	return code;
}

inline void PDC_identifier::OnFlightPlanControllerAssignedDataUpdate(CFlightPlan FlightPlan, int DataType)
{
	if (assignedIdent.count(FlightPlan.GetCallsign())) {
		string newSratch = FlightPlan.GetControllerAssignedData().GetScratchPadString();
		if (newSratch.length() == 4) {
			assignedIdent[FlightPlan.GetCallsign()].swap(newSratch);
		}
	}
	else {
		assignedIdent.insert({ FlightPlan.GetCallsign(), FlightPlan.GetControllerAssignedData().GetScratchPadString() });
	}
}