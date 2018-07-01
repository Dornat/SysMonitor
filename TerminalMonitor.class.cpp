#include "TerminalMonitor.class.hpp"

TerminalMonitor::TerminalMonitor(DateTime &dateTime, UserHost &userHost, OSInfo &OSinfo, CPU &cpu, RAM &ram)
{
	this->_dateTime = dateTime;
	this->_userHost = userHost;
	this->_OSinfo = OSinfo;
	this->_cpu = cpu;
	this->_ram = ram;
}

TerminalMonitor::~TerminalMonitor()
{

}

TerminalMonitor::TerminalMonitor(const TerminalMonitor &other)
{
	static_cast<void>(other);
}

TerminalMonitor &TerminalMonitor::operator = (const TerminalMonitor &other)
{
	static_cast<void>(other);
	return *this;
}

void TerminalMonitor::_allUpdate()
{
	this->_cpu.update();
	this->_dateTime.update();
	this->_userHost.update();
	this->_OSinfo.update();
	this->_ram.update();
}

void TerminalMonitor::_timeModule()
{
	std::string temp;
	WINDOW *win = newwin(8, 20, 0, 0);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 1, 8, "Date");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_dateTime.getDate();
	mvwprintw(win, 2, 5, temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 4, 8, "Time");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_dateTime.getTime();
	mvwprintw(win, 5, 6, temp.c_str());
	wrefresh(win);
}

void TerminalMonitor::_userModule()
{
	std::string temp;
	WINDOW *win = newwin(8, 20, 8, 0);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 1, 6, "Username");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_userHost.getUserName();
	mvwprintw(win, 2, 6, temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 4, 6, "Hostname");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_userHost.getHostName();
	mvwprintw(win, 5, 3, temp.c_str());
	wrefresh(win);
}

void TerminalMonitor::_OSModule()
{
	std::string temp;
	WINDOW *win = newwin(8, 20, 16, 0);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 1, 6, "OS Name");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_OSinfo.getOSName();
	mvwprintw(win, 2, 6, temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 4, 3, "Kernel version");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_OSinfo.getKernelVersion();
	mvwprintw(win, 5, 6, temp.c_str());
	wrefresh(win);
}

void TerminalMonitor::_CPUModule()
{
	std::string temp;
	WINDOW *win = newwin(24, 60, 0, 20);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, 2, 25, "Processor");
	wattroff(win, COLOR_PAIR(3));
	temp = this->_cpu.getBrand();
	mvwprintw(win, 3, 11, temp.c_str());
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, 6, 24, "Average load");
	wattroff(win, COLOR_PAIR(3));
	std::vector<double> avg = this->_cpu.getLoadAVG();
	std::stringstream output;
	std::copy(avg.begin(), avg.end(), std::ostream_iterator<double>(output, "  "));
	mvwprintw(win, 7, 18, output.str().c_str());

	std::vector<float> usage = this->_cpu.getUsage();
	
	int j = 11;
	for (size_t i = 0; i < 4; i++)
	{
		wattron(win, COLOR_PAIR(3));
		mvwprintw(win, j, 4, "core %i:", i);
		wattroff(win, COLOR_PAIR(3));
		this->_printCpuBars(win, j, 12, usage[i]);
		mvwprintw(win, j, 50, "%.1f%%", usage[i]);
		j += 2;
	}
	wrefresh(win);
}

void TerminalMonitor::_printCpuBars(WINDOW* win, int y, int x, float usage) {
	mvwprintw(win, y, x, "[");
	int numOfBars = usage * 0.45;
	for (int i = 0; i < numOfBars; i++) {
		wattron(win, COLOR_PAIR(1));
		mvwprintw(win, y, x + 1 + i, "|");
		wattroff(win, COLOR_PAIR(1));
	}
	mvwprintw(win, y, x + 36, "]");
}

void TerminalMonitor::_RAMModule()
{
	std::string temp;
	WINDOW *win = newwin(12, 30, 0, 80);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 1, 8, "Total memory");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_ram.getTotalMem();
	mvwprintw(win, 2, 11, "%s MB", temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 4, 8, "Used memory");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_ram.getUsedMem();
	mvwprintw(win, 5, 7, temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 7, 8, "Free memory");
	wattroff(win, COLOR_PAIR(2));
	temp = this->_ram.getFreeMem();
	mvwprintw(win, 8, 7, temp.c_str());
	wrefresh(win);
}

void TerminalMonitor::_NetworkModule()
{
	std::string temp;
	WINDOW *win = newwin(12, 30, 12, 80);
	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 1, 11, "Networks");
	wattroff(win, COLOR_PAIR(2));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 3, 10, "Packets in");
	wattroff(win, COLOR_PAIR(2));
	temp = "kaka";
	mvwprintw(win, 5, 8, temp.c_str());
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 7, 10, "Packets out");
	wattroff(win, COLOR_PAIR(2));
	temp = "kaka";
	mvwprintw(win, 9, 8, temp.c_str());
	wrefresh(win);
}

void TerminalMonitor::_allAppear()
{
	this->_timeModule();
	this->_userModule();
	this->_OSModule();
	this->_CPUModule();
	this->_RAMModule();
	this->_NetworkModule();
}

void TerminalMonitor::_ColorPairs()
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
}

void TerminalMonitor::displayInfo()
{
	initscr();
	noecho();
	start_color();
	this->_ColorPairs();
	curs_set(0);
	for(;;)
	{
		nodelay(stdscr, true);
		keypad(stdscr, true);
		this->_allUpdate();
		this->_allAppear();
		if (getch() == 'q')
		{	
			endwin();
			exit(0);
		}
	}
}
