#ifndef TERMINAL_MONITOR_H
#define TERMINAL_MONITOR_H
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"
#include "UserHost.class.hpp"
#include "DateTime.class.hpp"
#include "OSInfo.class.hpp"
#include "CPU.class.hpp"
#include "RAM.class.hpp"
#include "Network.class.hpp"
#include <ncurses.h>

class TerminalMonitor : public IMonitorDisplay
{
	public:
		TerminalMonitor(void);
		TerminalMonitor(DateTime &dateTime, UserHost &userHost, OSInfo &OSinfo, CPU &cpu, RAM &ram, Network network);
		~TerminalMonitor();
		TerminalMonitor(const TerminalMonitor &other);
		TerminalMonitor &operator = (const TerminalMonitor &other);
		void displayInfo();
	private:
		DateTime _dateTime;
		UserHost _userHost;
		OSInfo	_OSinfo;
		CPU		_cpu;
		RAM		_ram;
		Network _network;

		void _allUpdate();
		void _allAppear();
		void _timeModule();
		void _userModule();
		void _OSModule();
		void _CPUModule();
		void _RAMModule();
		void _NetworkModule();
		void _CatModule();
		void _printCpuBars(WINDOW* win, int y, int x, float usage);
		void _ColorPairs();
};

#endif
