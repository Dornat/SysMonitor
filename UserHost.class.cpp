#include "UserHost.class.hpp"

UserHost::UserHost()
{
	this->update();
}

UserHost::~UserHost()
{
	return;
}

UserHost::UserHost(const UserHost &other)
{
	*this = other;
}

UserHost &UserHost::operator = (const UserHost &other)
{
	this->_UserName = other.getUserName();
	this->_HostName = other.getHostName();
	return *this;
}

std::string UserHost::getUserName() const
{
	return this->_UserName;
}

std::string UserHost::getHostName() const
{
	return this->_HostName;
}

void UserHost::update(void) 
{
	char hostname[_POSIX_HOST_NAME_MAX];
	gethostname(hostname, _POSIX_HOST_NAME_MAX );
	this->_UserName = std::string(getlogin());
	this->_HostName = std::string(hostname);
}
