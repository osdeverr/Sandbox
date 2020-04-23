#include <cstdio>

#include <CXFramework/Interface.h>
#include <CXFramework/Interfaceable.h>

//
// INTERFACES
//

struct IPhysicsObject : CX::Interface<IPhysicsObject>
{
	virtual ~IPhysicsObject() {}

	virtual float GetSpeed() = 0;
	virtual bool IsMoving() = 0;
};

struct IVehicle : CX::Interface<IVehicle>
{
	virtual ~IVehicle() {}

	virtual std::string GetName() = 0;
	virtual bool IsPlayerVehicle() = 0;
};

struct IVisible : CX::Interface<IVisible>
{
	virtual ~IVisible() {}

	virtual float GetDrawDistance() = 0;
	virtual bool IsVisible() = 0;
};

//
// MOCK IMPLEMENTATIONS
//

class MockPhysicsObject : public IPhysicsObject
{
public:
	float GetSpeed() {
		return 12.f;
	}
	bool IsMoving() {
		return true;
	}
};

class MockVehicle : public IVehicle
{
public:
	std::string GetName() {
		return "Lada Vesta";
	}
	bool IsPlayerVehicle() {
		return true;
	}
};

class MockVisible : public IVisible
{
public:
	float GetDrawDistance() {
		return 2500.f;
	}
	bool IsVisible() {
		return true;
	}
};

//
// EXAMPLE USAGE
//

struct MockEntityAttribs
{
	bool isVehicle;
	bool isVisible;
	bool hasPhysics;

	void Construct(CX::Interfaceable& i) {
		if (isVehicle)
			i.Implements(new MockVehicle());
		if (isVisible)
			i.Implements(new MockVisible());
		if (hasPhysics)
			i.Implements(new MockPhysicsObject());
	}
};

class Entity : public CX::Interfaceable
{
public:
	template<typename A>
	Entity(A& attribs) {
		attribs.Construct(*this);
	}
};

int main() {
	MockEntityAttribs attr;
	attr.hasPhysics = true;
	attr.isVisible = true;
	attr.isVehicle = false;

	Entity e(attr);

	// Checking which interfaces are implemented...
	auto pVehicle = e.GetInterface<IVehicle>();
	if (pVehicle)
	{
		std::printf("Entity implements IVehicle:\n");
		std::printf("\tVehicle Name: %s\n", pVehicle->GetName().c_str());
		std::printf("\tOwned by Player: %d\n", (int)pVehicle->IsPlayerVehicle());
		std::printf("\n");
	}

	auto pVisible = e.GetInterface<IVisible>();
	if (pVisible)
	{
		std::printf("Entity implements IVisible:\n");
		std::printf("\tDraw Distance: %f\n", pVisible->GetDrawDistance());
		std::printf("\tIs Visible: %d\n", (int)pVisible->IsVisible());
		std::printf("\n");
	}

	auto pPhysics = e.GetInterface<IPhysicsObject>();
	if (pPhysics)
	{
		std::printf("Entity implements IPhysicsObject:\n");
		std::printf("\tSpeed: %f\n", pPhysics->GetSpeed());
		std::printf("\tIs Moving: %d\n", (int)pPhysics->IsMoving());
		std::printf("\n");
	}
}