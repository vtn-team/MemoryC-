#pragma once

class TaskBase
{
	int _id;

public :
	TaskBase();
	~TaskBase();

	virtual void init() = 0;
	virtual void dispose() = 0;
	virtual void update();
};

class Task
{
	int _id;

public:
	Task();
	~Task();

	virtual void init();
	virtual void dispose();
	virtual void update();
};