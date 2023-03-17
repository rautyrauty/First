#include <iostream>
#include <fstream>
using namespace std;

#define	MAX_OSPATH		260			// max length of a filesystem pathname

class dhdr
{
	char	demofilestamp[8];				// Should be HL2DEMO
	int	demoprotocol;					// Should be DEMO_PROTOCOL
	int	networkprotocol;				// Should be PROTOCOL_VERSION
	char	servername[MAX_OSPATH];		// Name of server
	char	clientname[MAX_OSPATH];		// Name of client who recorded the game
	char	mapname[MAX_OSPATH];			// Name of map
	char	gamedirectory[MAX_OSPATH];	// Name of game directory (com_gamedir)
	float	playback_time;					// Time of track
	int   playback_ticks;					// # of ticks in track
	int   playback_frames;				// # of frames in track
	int	signonlength;					// length of sigondata in bytes
public:
	void print()
	{
		cout << demofilestamp << '\n' << demoprotocol << '\n' << networkprotocol << '\n' << servername << '\n'
			<< clientname << '\n' << mapname << '\n' << gamedirectory << '\n' << playback_time << '\n'
			<< playback_ticks << '\n' << playback_frames << '\n' << signonlength << '\n';
	}
};

int main()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "g2-vs-natus-vincere-m1-nuke.dem", "rb");
	dhdr m_DemoHeader;
	fread(&m_DemoHeader, 1, sizeof(m_DemoHeader), fp);
	m_DemoHeader.print();
	fclose(fp);
	return 0;
}