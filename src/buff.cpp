#include "main.h"

Buff::Buff()
{

}

Buff::~Buff()
{

}

void Buff::Kill()
{
	dead_ = true;
}

bool Buff::Update(Character& self)
{
	return false;
}