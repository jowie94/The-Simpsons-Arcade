#ifndef NOTIFIABLE_H
#define NOTIFIABLE_H

struct Collider;

class Notifiable
{
public:
	virtual ~Notifiable() {}

	virtual void Notify(Collider* origin, Collider* other) = 0;
};

#endif
