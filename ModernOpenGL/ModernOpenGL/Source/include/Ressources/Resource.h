#pragma once

class Resource
{
	Resource() {};

	virtual void Create() = 0;
	virtual void Get() = 0;
	virtual void Delete() = 0;

};